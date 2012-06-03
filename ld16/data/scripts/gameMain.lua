-- derelict_ game logic
-- FINALLY most of the sodding day has been writing foundation code and crap
-- The loader system and camreas were demon spawn

local playerList = List:new();

-- These will need changed if changing the resolution from 640x480
local camBotX = 0;
local camBotY = 0;
local camTopX = 20;
local camTopY = 15;

gameCamera = CameraClass.create(1, camBotX, camBotY, camTopX, camTopY);

GAMEMODE_SINGLEPLAYER = 0;
GAMEMODE_MULTIPLAYER = 1;

GAME_MODE = GAMEMODE_SINGLEPLAYER; -- forcing single player just now, sorry!

function initialiseGame()
	loadLevel(1);
end

function updateGame()
	local player = playerList[ACTIVE_PLAYER+1];

	calculateLOS();
	if player.type == PLAYER_HUMAN then
		gameCamera:render();
	else
		renderStarfield();
		displayText(240, 200, "defaultFont16", 16, "AI Turn");
		
	end

end

function addPlayer( name, type, faction )
	local newPlayer = PlayerClass.create(name, type, faction);
	playerList:append(newPlayer);
end

function getPlayer(name)
	for i,player in ipairs(playerList) do
		if player.name == name then
			return player;
		end
	end

	return nil;
end

function calculateLOS()
	local player = playerList[ACTIVE_PLAYER+1];
	player:controlUnit();
	player:resetLOS();
	for unitNum = 1, player:getUnitAmount() do
		local unit = player:getUnit(unitNum);
		-- right
		for offset = 0, 10 do
			local x = unit.x + offset;
			if x > derelictRoomWidth * derelictFloorWidth then
				x = derelictRoomWidth * derelictFloorWidth;
			end
			if derelictShipTiles[unit.z][unit.y][x].tileCode ~= "0" and derelictShipTiles[unit.z][unit.y][x].tileCode ~= "G"
			and derelictShipTiles[unit.z][unit.y][x].tileCode ~= "8" and derelictShipTiles[unit.z][unit.y][x].tileCode ~= "9" then
				player.lineOfSight[unit.z][unit.y][x] = LOS_VISIBLE;
				break;
			end
			if derelictDoorTiles[unit.z][unit.y][x] ~= nil and derelictDoorTiles[unit.z][unit.y][x].isOpen == false then
				player.lineOfSight[unit.z][unit.y][x] = LOS_VISIBLE;
				break;
			end
			player.lineOfSight[unit.z][unit.y][x] = LOS_VISIBLE;
		end
		-- left
		for offset = 0, 10 do
			local x = unit.x - offset;
			if x < 0 then
				x = 0;
			end
			if derelictShipTiles[unit.z][unit.y][x].tileCode ~= "0" and derelictShipTiles[unit.z][unit.y][x].tileCode ~= "G"
			and derelictShipTiles[unit.z][unit.y][x].tileCode ~= "8" and derelictShipTiles[unit.z][unit.y][x].tileCode ~= "9" then
				player.lineOfSight[unit.z][unit.y][x] = LOS_VISIBLE;
				break;
			end
			if derelictDoorTiles[unit.z][unit.y][x] ~= nil and derelictDoorTiles[unit.z][unit.y][x].isOpen == false then
				player.lineOfSight[unit.z][unit.y][x] = LOS_VISIBLE;
				break;
			end
			player.lineOfSight[unit.z][unit.y][x] = LOS_VISIBLE;
		end
		-- down
		for offset = 0, 10 do
			local y = unit.y + offset;
			if y > derelictRoomHeight * derelictFloorHeight then
				y = derelictRoomHeight * derelictFloorHeight;
			end
			if derelictShipTiles[unit.z][y][unit.x].tileCode ~= "0" and derelictShipTiles[unit.z][y][unit.x].tileCode ~= "G"
			and derelictShipTiles[unit.z][y][unit.x].tileCode ~= "8" and derelictShipTiles[unit.z][y][unit.x].tileCode ~= "9" then
				player.lineOfSight[unit.z][y][unit.x] = LOS_VISIBLE;
				break;
			end
			if derelictDoorTiles[unit.z][y][unit.x] ~= nil and derelictDoorTiles[unit.z][y][unit.x].isOpen == false then
				player.lineOfSight[unit.z][y][unit.x] = LOS_VISIBLE;
				break;
			end
			player.lineOfSight[unit.z][y][unit.x] = LOS_VISIBLE;
		end
		-- up
		for offset = 0, 10 do
			local y = unit.y - offset;
			if y < 0 then
				y = 0
			end
			if derelictShipTiles[unit.z][y][unit.x].tileCode ~= "0" and derelictShipTiles[unit.z][y][unit.x].tileCode ~= "G"
			and derelictShipTiles[unit.z][y][unit.x].tileCode ~= "8" and derelictShipTiles[unit.z][y][unit.x].tileCode ~= "9" then
				player.lineOfSight[unit.z][y][unit.x] = LOS_VISIBLE;
				break;
			end
			if derelictDoorTiles[unit.z][y][unit.x] ~= nil and derelictDoorTiles[unit.z][y][unit.x].isOpen == false then
				player.lineOfSight[unit.z][y][unit.x] = LOS_VISIBLE;
				break;
			end
			player.lineOfSight[unit.z][y][unit.x] = LOS_VISIBLE;
		end
		-- downright
		for offset = 0, 10 do
			local x = unit.x + offset;
			local y = unit.y + offset
			if x > derelictRoomWidth * derelictFloorWidth then
				x = derelictRoomWidth * derelictFloorWidth;
			end
			if y > derelictRoomHeight * derelictFloorHeight then
				y = derelictRoomHeight * derelictFloorHeight;
			end
			if derelictShipTiles[unit.z][y][x].tileCode ~= "0" and derelictShipTiles[unit.z][y][x].tileCode ~= "G"
			and derelictShipTiles[unit.z][y][x].tileCode ~= "8" and derelictShipTiles[unit.z][y][x].tileCode ~= "9" then
				player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
				break;
			end
			if derelictDoorTiles[unit.z][y][x] ~= nil and derelictDoorTiles[unit.z][y][x].isOpen == false then
				player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
				break;
			end
			player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
		end
		-- downleft
		for offset = 0, 10 do
			local x = unit.x - offset;
			local y = unit.y + offset
			if x < 0 then
				x = 0;
			end
			if y > derelictRoomHeight * derelictFloorHeight then
				y = derelictRoomHeight * derelictFloorHeight;
			end
			if derelictShipTiles[unit.z][y][x].tileCode ~= "0" and derelictShipTiles[unit.z][y][x].tileCode ~= "G"
			and derelictShipTiles[unit.z][y][x].tileCode ~= "8" and derelictShipTiles[unit.z][y][x].tileCode ~= "9" then
				player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
				break;
			end
			if derelictDoorTiles[unit.z][y][x] ~= nil and derelictDoorTiles[unit.z][y][x].isOpen == false then
				player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
				break;
			end
			player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
		end
		-- upright
		for offset = 0, 10 do
			local x = unit.x + offset;
			local y = unit.y - offset
			if x > derelictRoomWidth * derelictFloorWidth then
				x = derelictRoomWidth * derelictFloorWidth;
			end
			if y < 0 then
				y = 0;
			end
			if derelictShipTiles[unit.z][y][x].tileCode ~= "0" and derelictShipTiles[unit.z][y][x].tileCode ~= "G"
			and derelictShipTiles[unit.z][y][x].tileCode ~= "8" and derelictShipTiles[unit.z][y][x].tileCode ~= "9" then
				player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
				break;
			end
			if derelictDoorTiles[unit.z][y][x] ~= nil and derelictDoorTiles[unit.z][y][x].isOpen == false then
				player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
				break;
			end
			player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
		end
		-- upleft
		for offset = 0, 10 do
			local x = unit.x - offset;
			local y = unit.y - offset
			if x < 0 then
				x = 0;
			end
			if y < 0 then
				y = 0;
			end
			if derelictShipTiles[unit.z][y][x].tileCode ~= "0" and derelictShipTiles[unit.z][y][x].tileCode ~= "G" 
			and derelictShipTiles[unit.z][y][x].tileCode ~= "8" and derelictShipTiles[unit.z][y][x].tileCode ~= "9" then
				player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
				break;
			end
			if derelictDoorTiles[unit.z][y][x] ~= nil and derelictDoorTiles[unit.z][y][x].isOpen == false then
				player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
				break;
			end
			player.lineOfSight[unit.z][y][x] = LOS_VISIBLE;
		end
	end
end

function calcDistance( x1, y1, z1, x2, y2, z2 )
	local distance = 0;
	if z2 > z1 then z2 = z2 * -1 end;
	if y2 > y1 then y2 = y2 * -1 end;
	if x2 > x1 then x2 = x2 * -1 end;

	distance = distance + ( z1 - z2 ) + ( y1 - y2 ) + ( x1 - x2 );

	return distance;
end


