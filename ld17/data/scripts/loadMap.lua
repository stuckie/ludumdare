-- Load A MAP!

layer0Map = {};
layer1Map = {};

local math = math;

-- hardcoded values for teh win!!!
local fortPositions = { {x=19, y=7}, {x=41, y=14}, {x=55, y=15}, {x=88, y=14}, {x=54, y= 21}, {x=68, y=24}, {x=45, y=14}, {x=34, y=12}, {x=21, y=61}, {x=28, y=65}, {x=42, y=69}, {x=12, y=75}, {x=24, y=74}, {x=30, y=84}, {x=42, y=88}, {x=86, y=80}, {x=83, y=76}, {x=73, y=82}, {x=85, y=54} };
local chestPositions = { {x=23, y=9}, {x=48, y=12}, {x=82, y=4}, {x=91, y=18}, {x=29, y=30}, {x=18, y=39}, {x=25, y=35}, {x=40, y=59}, {x=87, y=44} };
local minePositions = { {x=41, y=12}, {x=63, y=22}, {x=61, y=21}, {x=25, y=26}, {x=28, y=78}, {x=79, y=92}, {x=88, y=58}, {x=71, y=65} };
local treePositions = {};
local rockPositions = {};

local randomiseForts = function()
	local fortAmount = math.random(5, 100);
	for fort=1, fortAmount do
		local x = math.random(1, 97);
		local y = math.random(1, 98);
		while layer0Map[y][x].tileCode == "0" do
			x = math.random(1, 97);
			y = math.random(1, 98);
		end
		local unclaimedPlayer = getPlayer("Neutral");
		local fort = unclaimedPlayer:addUnit(UNIT_FORT, x*64, y*64);
		fort.gold = 1000;
	end
end

local randomiseTreasure = function()
	local chestAmount = math.random(2, 9);
	for chest=1, chestAmount do
		local x = chestPositions[chest].x;
		local y = chestPositions[chest].y;
		local tile = { tileCode = "3", tileX = x, tileY = y };
		layer1Map[y][x] = tile;
	end
end

local randomiseTrees = function()
	local treeAmount = math.random(20, 100);
	for tree=1, treeAmount do
		local x = math.random(1, 97);
		local y = math.random(1, 98);
		while layer1Map[y][x] ~= nil and layer0Map[y][x].tileCode == "0" do
			x = math.random(1, 97);
			y = math.random(1, 98);
		end
		local tile = { tileCode = "2", tileX = x, tileY = y };
		layer1Map[y][x] = tile;
	end
end

local randomiseMines = function()
	local mineAmount = math.random(4, 8);
	for mine=1, 8 do
		local x = minePositions[mine].x;
		local y = minePositions[mine].y;
		local tile = { tileCode = "5", tileX = x, tileY = y };
		layer1Map[y][x] = tile;
	end
end

local randomiseRocks = function()
	local rockAmount = math.random(40, 80);
	for rock=1, rockAmount do
		local x = math.random(1, 97);
		local y = math.random(1, 98);
		while layer1Map[y][x] ~= nil do
			x = math.random(1, 97);
			y = math.random(1, 98);
		end
		local tile = { tileCode = "1", tileX = x, tileY = y };
		layer1Map[y][x] = tile;
	end

	for y=0,99 do
		if y == 0 or y == 99 then
			for x=0,98 do
				local tile = { tileCode = "1", tileX = x, tileY = y};
				layer1Map[y][x] = tile;
			end
		else
			local tile0 = { tileCode = "1", tileX = 0, tileY = y};
			local tile100 = { tileCode = "1", tileX = 98, tileY = y};
			layer1Map[y][0] = tile0;
			layer1Map[y][98] = tile100;
		end
	end
end

loadMap = function (mapName)
	-- clean out any data we may still have...
	for y=0,100 do
		layer0Map[y] = {};
		layer1Map[y] = {};
		for x=0,100 do
			layer0Map[y][x] = nil;
			layer1Map[y][x] = nil;
		end
	end

	math.randomseed(os.time());

	-- load in new background data!
	local inputFile = assert(io.open("data/maps/" .. mapName .. ".map" , "r"));
	local fileData = inputFile:read("*all");
	inputFile:close();

	local y = 0;
	local x = 0;

	-- load in the map details
	for tileType in fileData:gmatch"%w" do
		local tile = { tileCode = tileType, tileX = x, tileY = y };
		layer0Map[y][x] = tile;

		x = x + 1;
		if x == 99 then
			x = 0;
			y = y + 1;
		end
		if y == 100 then
			break;
		end
	end

	randomiseForts();
	randomiseTreasure();
	randomiseTrees();
	randomiseMines();
	randomiseRocks();

	GAME_IN_PROGRESS = true;
end
