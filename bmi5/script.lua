-- Start
-- Script: script.lua
function move(x,y)
	print("I am using Lua from within C")
	c = 1.0
	while c > 0.0 do
		c,x,y = coroutine.yield(y*math.sin(x*3.141592), y*math.cos(x*3.141592))
	end
	return x,y
end

-- End