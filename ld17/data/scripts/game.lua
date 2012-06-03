dofile("data/scripts/loadMap.lua");
dofile("data/scripts/player.lua");
dofile("data/scripts/gameCamera.lua");

globalUnitList = List:new();
local playerList = List:new();
local cloudList = List:new();
local math = math;

-- These will need changed if changing the resolution from 640x480
local camBotX = 0;
local camBotY = 0;
local camTopX = 10;
local camTopY = 10;

gameCamera = CameraClass.create(0, camBotX, camBotY, camTopX, camTopY);

GAMEMODE_SINGLEPLAYER = 0;
GAMEMODE_MULTIPLAYER = 1;

GAME_MODE = GAMEMODE_SINGLEPLAYER; -- forcing single player just now, sorry!

WindX = 0;
WindY = 0;
local windUpdate = 0;
local windUpdateDelay = 10;

NextUnitId = 0;

local ATTACK_KEY_DEBOUNCE = false;
local PILLAGE_KEY_DEBOUNCE = false;
local BOARD_KEY_DEBOUNCE = false;

local randomUnits = function(player)
	for i=0, math.random(5, 50) do
		local x = math.random(1, 97);
		local y = math.random(1, 98);
		local tile = layer0Map[y][x];
		if tile.tileCode == "0" then
			local ship = player:addUnit(UNIT_PIRATESHIP, x*64, y*64);
			ship.gold = 1000;
		else
			local pirates = player:addUnit(UNIT_PIRATEMEN, x*64, y*64);
			pirates.gold = 1000;
		end
	end
	local x = math.random(1, 97);
	local y = math.random(1, 98);
	local tile = layer0Map[y][x];
	while tile.tileCode == "0" do
		x = math.random(1, 97);
		y = math.random(1, 98);
		tile = layer0Map[y][x];
	end
	local fort = player:addUnit(UNIT_FORT, x*64, y*64);
	fort.gold = 1000;
end

initialiseGame = function()
	local neutralPlayer = addPlayer("Neutral", "AI", "Neutral");
	loadMap("Margera");
	ThisPlayer = "RedBeard";

	randomUnits(neutralPlayer);
	randomUnits(addPlayer("PinkBeard", "AI", "PinkBeard"));
	randomUnits(addPlayer("BlueBeard", "AI", "BlueBeard"));
	randomUnits(addPlayer("BlackBeard", "AI", "BlackBeard"));
	randomUnits(addPlayer("GreenBeard", "AI", "GreenBeard"));
	randomUnits(addPlayer("GreyBeard", "AI", "GreyBeard"));

	local thisPlayer = addPlayer(ThisPlayer, "LOCAL", "RedBeard");
	for cloud=0,500 do
		cloudList:append({x = math.random(0, 100*64), y = math.random(0, 100*64), u = 128, v = 128, w = 64, h = 64, sheet = "BlockTerrain"});
	end

	-- give player one a ship and a boat load of gold
	local playerShip = thisPlayer:addUnit(UNIT_PIRATESHIP, 64, 64);
	playerShip.gold = 1000;

	local welcomeText = List:new();
	welcomeText:append({x=10, y=15, text="Welcome to "});
	welcomeText:append({x=10, y=30, text="YARGH!!!! "});
	welcomeText:append({x=10, y=45, text="Shake"});
	welcomeText:append({x=10, y=60, text="   Yer"});
	welcomeText:append({x=10, y=75, text="     Booty!"});
	addHudElement(10, WindowHeight - 140, 60, welcomeText);
end

local updateWind = function()
	windUpdate = windUpdate - DeltaTime;
	if windUpdate < 0 then
		windUpdate = windUpdateDelay;

		local windAngle = math.rad(math.random(0, 360));
		local windStrength = math.random(1, 20);

		WindX = math.cos(windAngle) * windStrength;
		WindY = math.sin(windAngle) * windStrength;
	end
end

updateGame = function()
	gameCamera:render();
	updateWind();

	local offsetX = (WindowWidth * 0.1);
	local offsetY = (WindowHeight * 0.1);
	local localPlayer = getPlayer(ThisPlayer);

	if (MOUSE_X > (WindowWidth - offsetX)) or ControlMan:getRight() == true then gameCamera:panRight(); end
	if (MOUSE_X < offsetX) or ControlMan:getLeft() == true then gameCamera:panLeft(); end
	if (MOUSE_Y < offsetY) or ControlMan:getUp() == true then gameCamera:panUp(); end
	if (MOUSE_Y > (WindowHeight - offsetY)) or ControlMan:getDown() == true then gameCamera:panDown(); end

	if MOUSE_LEFT == true and MOUSE_LEFT_DEBOUNCE == false then
		print("X:" .. math.modf(((MOUSE_X) + (gameCamera.x * 64) + 32)/64) .. ", Y:" .. math.modf(((MOUSE_Y) + 32 + (gameCamera.y * 64))/64));
		if localPlayer.currentUnit == nil then
			localPlayer:selectUnit();
			MOUSE_LEFT_DEBOUNCE = true;
		end

		if localPlayer.currentUnit ~= nil and MOUSE_LEFT_DEBOUNCE == false then
			localPlayer.currentUnit.selected = false;
			localPlayer.currentUnit = nil;
		end
		
	elseif MOUSE_LEFT == false and MOUSE_LEFT_DEBOUNCE == true then
		MOUSE_LEFT_DEBOUNCE = false;
	end

	if localPlayer.currentUnit ~= nil then
		TextureMan:blitTexture(localPlayer.beard, localPlayer.currentUnit.x - gameCamera.x * 64, localPlayer.currentUnit.y - gameCamera.y * 64, 0, localPlayer.selected.u, localPlayer.selected.v, 64, 64);
		if MOUSE_RIGHT == true and MOUSE_RIGHT_DEBOUNCE == false and (ControlMan:getLCtrl() == false) and ControlMan:getLShift() == false then
			localPlayer.currentUnit:moveTo((MOUSE_X - 32) + (gameCamera.x * 64), (MOUSE_Y - 32) + (gameCamera.y * 64));
			MOUSE_RIGHT_DEBOUNCE = true
		elseif MOUSE_RIGHT == true and ControlMan:getRCtrl() == false and ControlMan:getLCtrl() == true and ControlMan:getLShift()==false and MOUSE_RIGHT_DEBOUNCE == false and ATTACK_KEY_DEBOUNCE == false then
			MOUSE_RIGHT_DEBOUNCE = true;
			ATTACK_KEY_DEBOUNCE = true;
			local clickPosX = (MOUSE_X) + (gameCamera.x * 64);
			local clickPosY = (MOUSE_Y) + (gameCamera.y * 64);
			local target = nil;
			for i,unit in ipairs(globalUnitList) do
				if unit.owner ~= localPlayer then
					if calcDistanceXY(unit.x + 32, unit.y + 32, clickPosX, clickPosY) < 32 then
						target = unit;
						break;
					end
				end
			end
			if target ~= nil then
				localPlayer.currentUnit:attack(target);
				local text = List:new();
				text:append({x=10, y=30, text="Yarrr!!!"});
				text:append({x=10, y=75, text="Ye need more"});
				text:append({x=10, y=90, text="iron in ye!"});
				addHudElement(3, WindowHeight - 140, 60, text);
			end
		elseif MOUSE_RIGHT == false and MOUSE_RIGHT_DEBOUNCE == true then
			MOUSE_RIGHT_DEBOUNCE = false;
		elseif ControlMan:getLCtrl() == false and ATTACK_KEY_DEBOUNCE == true then
			ATTACK_KEY_DEBOUNCE = false;
		elseif ControlMan:getLShift() == false and BOARD_KEY_DEBOUNCE == true then
			BOARD_KEY_DEBOUNCE = false;
		elseif ControlMan:getRCtrl() == false and PILLAGE_KEY_DEBOUNCE == true then
			PILLAGE_KEY_DEBOUNCE = false;
		elseif ControlMan:getLShift() == true and MOUSE_RIGHT == true and MOUSE_RIGHT_DEBOUNCE == false and BOARD_KEY_DEBOUNCE == false then
			MOUSE_RIGHT_DEBOUNCE = true;
			BOARD_KEY_DEBOUNCE = true;
			local clickPosX = (MOUSE_X) + (gameCamera.x * 64);
			local clickPosY = (MOUSE_Y) + (gameCamera.y * 64);

			local unit = localPlayer.currentUnit;
			if calcDistanceXY(unit.x + 32, unit.y + 32, clickPosX, clickPosY) < 128 then
				if unit.type == "Pirate Ship" then
					if unit:checkCollision(clickPosX, clickPosY) == true then
						if unit.men > 0 then
							local text = List:new();
							text:append({x=10, y=30, text="Walk"});
							text:append({x=10, y=45, text="  The"});
							text:append({x=10, y=60, text="    Plank!"});
							addHudElement(3, WindowHeight - 140, 60, text);
							unit.men = unit.men - 1;
							local newMan = localPlayer:addUnit(UNIT_PIRATEMEN, clickPosX, clickPosY);
							unit.gold = unit.gold - 100;
							newMan.gold = 100;
						end
					end
				else
					for i,ship in ipairs(localPlayer.unitList) do
						if ship.type == "Pirate Ship" then
							local text = List:new();
							text:append({x=10, y=45, text="Get Aboard"});
							text:append({x=10, y=70, text="Ye Filthy"});
							text:append({x=10, y=75, text="Landlubbers!"});
							addHudElement(3, WindowHeight - 140, 60, text);
							if calcDistanceXY(ship.x + 32, ship.y + 32, clickPosX, clickPosY) < 128 then
								ship.gold = ship.gold + unit.gold;
								ship.men = ship.men + 1;
								localPlayer:removeUnit(unit);
								globalUnitList:remove(unit);
								break;
							end
						end
					end
				end
			end
		elseif ControlMan:getRCtrl() == true and MOUSE_RIGHT == true and MOUSE_RIGHT_DEBOUNCE == false and PILLAGE_KEY_DEBOUNCE == false then
			MOUSE_RIGHT_DEBOUNCE = true;
			PILLAGE_KEY_DEBOUNCE = true;
			local clickPosX = (MOUSE_X) + (gameCamera.x * 64);
			local clickPosY = (MOUSE_Y) + (gameCamera.y * 64);
			local unit = localPlayer.currentUnit;

			print("pillage!");
			if unit.type == "Pirate Men!" then
				if calcDistanceXY(unit.x + 32, unit.y + 32, clickPosX, clickPosY) < 64 then
					for i,fort in ipairs(globalUnitList) do
						if fort.type == "Pirate Fort" then
							local text = List:new();
							text:append({x=10, y=45, text="YARRR!!!"});
							text:append({x=10, y=70, text="Pillage Yer"});
							text:append({x=10, y=75, text="    Guts Out!"});
							addHudElement(3, WindowHeight - 140, 60, text);
							fort.owner:removeUnit(fort);
							unit.owner:takeUnit(fort);
							fort.owner = unit.owner;
						end
					end
				end
			end
		end

		if ControlMan:getSpace() == true then
			gameCamera.x = (localPlayer.currentUnit.x - WindowWidth/2)/64;
			gameCamera.y = (localPlayer.currentUnit.y - WindowHeight/2)/64;
		end
	end

	for i,cloud in ipairs(cloudList) do
		cloud.x = cloud.x + WindX * DeltaTime;
		cloud.y = cloud.y + WindY * DeltaTime;
		if cloud.x < 0 then cloud.x = 100 * 64 end
		if cloud.y < 0 then cloud.y = 100 * 64 end
		if cloud.x > 100*64 then cloud.x = 0 end
		if cloud.y > 100*64 then cloud.y = 0 end
		if (calcDistanceX((gameCamera.x*64) + 64, cloud.x*64) < WindowWidth + 64
		and calcDistanceY((gameCamera.y*64) + 64, cloud.y*64) < WindowHeight + 64) then
			TextureMan:blitTexture(cloud.sheet, cloud.x - gameCamera.x * 64, cloud.y - gameCamera.y * 64, 0, cloud.u, cloud.v, cloud.w, cloud.h);
		end
	end

	for i,player in ipairs(playerList) do
		player:update();
	end

	updateMiscGraphics();
	updateTextWriters();

	for i,player in ipairs(playerList) do
		drawHud(player);
	end

end

addPlayer = function( name, type, beard )
	local newPlayer = PlayerClass.create(name, type, beard);
	playerList:append(newPlayer);
	return newPlayer;
end

getPlayer = function(name)
	for i,player in ipairs(playerList) do
		if player.name == name then
			return player;
		end
	end

	return nil;
end

addUnit = function( player, type )
	local newUnit;
	if type == UNIT_PIRATEMEN then
		newUnit = PirateMenClass.create(NextUnitId, player);
	elseif type == UNIT_PIRATESHIP then
		newUnit = PirateShipClass.create(NextUnitId, player);
	elseif type == UNIT_FORT then
		newUnit = FortClass.create(NextUnitId, player);
	end

	NextUnitId = NextUnitId + 1;
	globalUnitList:append(newUnit);

	return newUnit;
end

getUnit = function(id)
	return globalUnitList[id];
end

removeUnit = function( unit )
	globalUnitList:remove(unit)
end

calcDistance = function( x1, y1, z1, x2, y2, z2 )
	local distance = 0;
	distance = distance + math.sqrt((( z1 - z2 ) * ( z1 - z2 )) + (( y1 - y2 ) * ( y1 - y2 )) + (( x1 - x2 ) * ( x1 - x2 )));

	return distance;
end

calcDistanceX = function (x1, x2)
	local distance = 0
	distance = distance + (x1 - x2);

	return distance;
end

calcDistanceY = function (y1, y2)
	local distance = 0;
	distance = distance + (y1 - y2);

	return distance;
end

calcDistanceXY = function (x1, y1, x2, y2)
	local distance = 0;
	distance = distance + math.sqrt((( y1 - y2 ) * ( y1 - y2 )) + (( x1 - x2 ) * ( x1 - x2)));

	return distance;
end
