-- Start
-- Script: script.lua
function move(x,y)
	print("I am using Lua from within C")
	c = 1.0
	while c > 0.0 do
		c,x,y = coroutine.yield(math.sin(x), math.cos(x))
	end
	return x,y
end

-- End