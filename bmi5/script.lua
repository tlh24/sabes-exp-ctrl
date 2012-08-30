-- Start
-- Script: script.lua
local ffi = require("ffi")
require "numlua"
require "numlua.matrix"

ffi.cdef[[
	void getPolgemus(float* res); 
	]]

function getCurs()
	local xyz = ffi.new("float", 3); 
	ff.get
end

function move(x,y)
	print("I am using Lua from within C")
	c = 1.0
	while c > 0.0 do
		c,x,y = coroutine.yield(y*math.sin(x*3.141592), y*math.cos(x*3.141592))
	end
	return x,y
end

-- End