-- Start
-- Script: script.lua
local require = require --??
local ffi = require("ffi")
require "numlua"
require "numlua.matrix"
require "persistence"

ffi.cdef[[
	void getPolhemus(float* res); 
	void setShapeLoc(int shp, float x, float y); 
	void setShapeColor(int shp, float r, float g, float b); 
	void setShapeAlpha(int shp, float a); 
	double gettime(); 
	]]

function getPolhemus()
	local xyz = ffi.new("float[?]", 4); --4 because FFI indexing in C is also 1-based. 
	ffi.C.getPolhemus(xyz); 
	return xyz[1], xyz[2], xyz[3]
end
function gettime()
	return ffi.C.gettime()
end
function wait(sec)
	--waits with a granularity of the current frame rate.
	local live = 1.0
	local start = gettime() 
	local time = start
	while live > 0.0 and time - start < sec do
		live,time = coroutine.yield()
	end
end
function setShapeLoc(shp, x, y)
 	ffi.C.setShapeLoc(shp, x, y)
end
function setShapeColor(shp, r, g, b)
 	ffi.C.setShapeColor(shp, r, g, b)
end
function setShapeAlpha(shp, a)
 	ffi.C.setShapeAlpha(shp, a)
end

-- i guess we need to do a calibration, polhemus to screen. 
function calibrate()
	-- 4 x 4 grid of target locations.
	local a = matrix.ones(16, 4)
	local b = matrix.ones(16, 2)
	for ix = 1,4 do --iterate horizontal first.
		for iy = 1,4 do
			local x = (ix - 2.5)/2
			local y = (iy - 2.5)/2
			local i = (iy-1)*4+ix
			-- move the cursor. 
			setShapeLoc(0, x, y)
			setShapeColor(0, 1, 0, 0)
			wait(1)
			setShapeColor(0,0,1,0); 
			wait(0.5)
			px,py,pz = getPolhemus()
			a[i][2] = px
			a[i][3] = py
			a[i][4] = pz
			b[i][1] = x
			b[i][2] = y
		end
	end
	print(matrix.pretty(a))
	print(matrix.pretty(b))
	--alrighty, perform the linear regression ax=b
	-- where x translates polhemus to screen coordinates.
	calibrate = matrix.ls(a,b,1); --use svd. 
	fil = io.output("calibrate.lua")
	persistence.store(fil, matrix.totable(calibrate))
	return
end

function move(live, time)
	print("I am using Lua from within C")
	local px, py, pz
	local x = 0
	local y = 0
	calibrate = matrix.fromtable(persistence.load("calibrate.lua"))
	while live > 0.0 do
		-- print polhemus?  to test?!
		px,py,pz = getPolhemus()
		local a = matrix.ones(1,4)
		a[1][2] = px
		a[1][3] = py
		a[1][4] = pz
		local b = a * calibrate
		--print(matrix.shape(b))
		--print(b[1][1] .. " " .. b[1][2])
		setShapeLoc(0, b[1][1], b[1][2])
		setShapeColor(0, px, pz, 1, 1)
		--print(string.format("x %4.2f y %4.2f z %4.2f t %f", px, py, pz, time))
		live,time = coroutine.yield()
	end
	return
end

-- End