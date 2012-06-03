
currentMoon = "Chronos";
currentLevel = "01";
currentRoom = "00";
currentTime = 999;

local moonData = {};
local levelData = {};

function unloadMoon()
	TextureMan:delTexture("LevelData");

	levelData = {};
	moonData = {};
end

function loadMoon( moonToLoad )
	currentMoon = moonToLoad;
	TextureMan:addTexture("LevelData", "data/gfx/" .. currentMoon .. ".bmp");
	dofile("data/levels/" .. currentMoon .. ".lua");

	currentLevel = "01";
	loadLevel( currentLevel );
	renderRoom( 0, 0 );
end

function loadLevel( levelToLoad )
	local inputFile = assert(io.open("data/levels/" .. currentMoon .. "/" .. levelToLoad .. ".moon" , "r"))
	currentTime = inputFile:read("*number");
	local fileData = inputFile:read("*all");
	inputFile:close();

	moonData = {};
	for y=0,moonHeight do
		moonData[y] = {};
		for x=0,moonWidth do
			moonData[y][x] = 0;
		end
	end

	levelData = {};
	for y=0,moonHeight do
		levelData[y] = {};
		for x=0,moonWidth do
			levelData[y][x] = 0;
		end
	end

	local y = 0;
	local x = 0;

	for roomNumber in fileData:gmatch"%d%d" do
		moonData[y][x] = roomNumber;
		levelData[y][x] = loadRoom(moonData[y][x]);
		x = x + 1;
		if x == moonWidth then
			x = 0;
			y = y + 1;
		end
		if y > moonHeight then
			-- file is too big!
			print("OOPS!");
			assert();
		end
	end

end

function loadRoom( roomToLoad )
	local inputFile = assert(io.open("data/levels/" .. currentMoon .. "/" .. roomToLoad .. ".cave" , "r"))
	local fileData = inputFile:read("*all")
	inputFile:close()

	local roomData = {};
	for y=0,roomHeight - 1 do
		roomData[y] = {};
		for x=0,roomWidth - 1 do
			roomData[y][x] = 0;
		end
	end

	local y = 0;
	local x = 0;

	for roomNumber in fileData:gmatch"%w" do
		createTile("CavernBack", x, y, 0);
		roomData[y][x] = roomNumber;
		x = x + 1;
		if x == roomWidth then
			x = 0;
			y = y + 1;
		end
		if y > roomHeight then
			-- file is too big!
			print("OOPS!");
			assert();
		end
	end

	return roomData;
end

function renderRoom( roomX, roomY )
	for y=0,roomHeight -1 do
		for x=0,roomWidth -1 do
			if levelData[roomY][roomX][y][x] == "1" then
				createTile("Solid", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "T" then
				createTile("ResearchLand", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "F" then
				createTile("ResearchLeft", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "H" then
				createTile("ResearchRight", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "G" then
				createTile("ResearchMid", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "8" then
				createTile("CavernBack", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "X" then
				createTile("Sky", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "x" then
				createTile("LeaveSky", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "R" then
				createTile("LeaveRight", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "L" then
				createTile("LeaveLeft", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "U" then
				createTile("LeaveUp", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "D" then
				createTile("LeaveDown", x, y, 1);
			end
		end
	end
end

local WallNum = 0;

function createTile ( WallType, x, y, z )
	WallNum = WallNum + 1;
	local WallTex = 0;
	local CurrentEntity = "Wall." .. WallType .. "." .. WallNum;

	if WallType == "Solid" then WallTex = 0; end
	if WallType == "ResearchLand" then WallTex = 16; end
	if WallType == "ResearchLeft" then WallTex = 32; end
	if WallType == "ResearchMid" then WallTex = 48; end
	if WallType == "ResearchRight" then WallTex = 64; end
	if WallType == "CavernBack" then WallTex = 80; end
	if WallType == "Sky" then WallTex = 96; end
	
	if WallType == "LeaveSky" then WallTex = 96; end
	if WallType == "LeaveUp" then WallTex = 80; end
	if WallType == "LeaveLeft" then WallTex = 80; end
	if WallType == "LeaveRight" then WallTex = 80; end
	if WallType == "LeaveDown" then WallTex = 80; end
	
	LevelMan:addTile(CurrentEntity, WallType, x, y, z);
	LevelMan:texTile(CurrentEntity, "LevelData", "LevelData", 240, WallTex, 16, 16, 255, 0, 255);
	
end
