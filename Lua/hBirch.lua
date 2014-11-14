--goes forward, digging if necessary
function goF()
	while not turtle.forward() do
		turtle.dig()
	end
end

--goes up, digging if necessary
function goU()
	while not turtle.up() do
		turtle.digUp()
	end
end

--goes down, digging if necessary
function goD()
	while not turtle.down() do
		turtle.digDown()
	end
end

--digs out the leaf blocks
function unLeaf()
	turtle.dig()
	goF()
	turtle.digUp()
	turtle.digDown()
end

-- clears a tree by digging to the top, spiraling the leaves, then digging down the trunk, finally replacing the sappling
function unTree()
	goF()
	turtle.digDown()
	local rise = 0
	while turtle.detectUp() do
		goU()
		rise = rise + 1
	end
	rise = rise-2
	goD()
	goD()
	unLeaf()
	turtle.turnRight()
	unLeaf()
	turtle.turnRight()
	unLeaf()
	unLeaf()
	turtle.turnRight()
	unLeaf()
	unLeaf()
	turtle.turnRight()
	for i=1,2 do
		for j=1,3 do unLeaf() end
		turtle.turnRight()
	end
	for i=1,3 do
		for j=1,4 do unLeaf() end
		turtle.turnRight()
	end
	goF()
	goF()
	turtle.turnRight()
	goF()
	goF()
	turtle.turnRight()
	turtle.turnRight()
	for lwr = 1, rise do
		goD()
	end
end

for t=1,7 do
	unTree()
	for d=1,4 do
		goF()
	end
end
unTree()