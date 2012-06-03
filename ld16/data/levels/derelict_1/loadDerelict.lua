-- derelict_1

derelictShipTiles = {};
derelictDoorTiles = {};
derelictEntities = {};

function loadDerelict()
	-- clean out any data we may still have...
	for z=0,derelictFloorDepth do
		derelictShipTiles[z] = {};
		derelictDoorTiles[z] = {};
		derelictEntities[z] = {};
		for y=0,derelictRoomHeight * derelictFloorHeight do
			derelictShipTiles[z][y] = {};
			derelictDoorTiles[z][y] = {};
			derelictEntities[z][y] = {};
			for x=0,derelictRoomWidth * derelictFloorWidth do
				derelictShipTiles[z][y][x] = nil;
				derelictDoorTiles[z][y][x] = nil;
				derelictEntities[z][y][x] = nil;
			end
		end
	end
	
	-- load in new data!
	for floor=0,derelictFloorDepth do
	-- we need to load each floor in one BIG chunk as the room loader didn't work... bleh
		local inputFile = assert(io.open("data/levels/derelict_" .. derelictNumber .. "/0" .. floor .. ".map" , "r"))
		local fileData = inputFile:read("*all");
		inputFile:close();

		local y = 0;
		local x = 0;

		-- load in the derelict floor details
		for roomNumber in fileData:gmatch"%w" do
			local pushTile = checkTile(roomNumber, floor, y, x);
			local tile = { tileCode = pushTile, textureSheet = "tileData", tileX = x, tileY = y };
			derelictShipTiles[floor][y][x] = tile;

			x = x + 1;
			if x == derelictFloorWidth * derelictRoomWidth then
				x = 0;
				y = y + 1;
			end
			if y == derelictFloorHeight * derelictRoomHeight then
				break;
			end
		end
	end

	GAME_IN_PROGRESS = true;
end

function checkTile( tileType, z, y, x )
	if tileType == "A" then
		local tile = { tileCode = "A", textureSheet = "tileData", tileX = x, tileY = y };
		local newDoor = DoorClass.create(false);
		newDoor.tileType = "A";
		derelictDoorTiles[z][y][x] = newDoor;
		return "0";
	elseif tileType == "B" then
		local tile = { tileCode = "B", textureSheet = "tileData", tileX = x, tileY = y };
		local newDoor = DoorClass.create(false);
		newDoor.tileType = "B";
		derelictDoorTiles[z][y][x] = newDoor;
		return "0";
	elseif tileType == "T" then
		local tile = { tileCode = "T", textureSheet = "tileData", tileX = x, tileY = y };
		local newLocker = LockerClass.create(true);
		newLocker.tileType = "T";
		derelictEntities[z][y][x] = newLocker;
		return "0";
	end

	return tileType;
end
