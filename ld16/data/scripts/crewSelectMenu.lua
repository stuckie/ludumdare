-- Crew Select

local crewSelectComplete = false;
local currentlyDisplaying = CLASS_ENGINEER;

-- typedefs for all!

CLASS_ENGINEER = 10;	CLASS_CYBORG = 20;			CLASS_TURRET = 30;
CLASS_MEDIC = 11;		CLASS_VIRUS = 21;			CLASS_DOOR = 31;
CLASS_SOLDIER = 12;		CLASS_GRUNT = 22;			CLASS_LOCKER = 32;
CLASS_COMMS = 13;		CLASS_SIREN = 23;
CLASS_SCOUT = 14;		CLASS_GHOST = 24;
CLASS_HEAVY = 15;		CLASS_BLITZER = 25;
						CLASS_ALIEN_QUEEN = 26;
						CLASS_ALIEN_BROOD = 27;

UNIT_HUMAN = 0;
UNIT_AI = 1;

PLAYER_HUMAN = 0;
PLAYER_AI = 1;

FACTION_HUMAN = 0;
FACTION_ALIEN = 1;

dofile("data/scripts/units/human/engineer.lua");
dofile("data/scripts/units/human/medic.lua");
dofile("data/scripts/units/human/soldier.lua");
dofile("data/scripts/units/human/comms.lua");
dofile("data/scripts/units/human/scout.lua");
dofile("data/scripts/units/human/heavy.lua");

dofile("data/scripts/units/alien/cyborg.lua");
dofile("data/scripts/units/alien/virus.lua");
dofile("data/scripts/units/alien/grunt.lua");
dofile("data/scripts/units/alien/siren.lua");
dofile("data/scripts/units/alien/ghost.lua");
dofile("data/scripts/units/alien/blitzer.lua");
dofile("data/scripts/units/alien/queen.lua");
dofile("data/scripts/units/alien/brood.lua");

dofile("data/scripts/units/turret.lua");
dofile("data/scripts/units/door.lua");
dofile("data/scripts/units/locker.lua");

function initialiseCrewSelect()
	addTextWriter("Crew Select", 240, 50, "defaultFont16", "Crew Select", 0, 16);
	currentlyDisplaying = CLASS_ENGINEER;

	TextureMan:addTexture("tileData", "data/gfx/derelict_1.png");
	TextureMan:setColourKey("tileData", 255, 0, 255);

end

local debounce = false;

function crewSelectChangeFaction()
	if GAME_MODE == GAMEMODE_SINGLEPLAYER then
		return; -- Marines only for Player, Aliens for AI
	else
		local player = getPlayer("Player"..ACTIVE_PLAYER);
		if player.unitList:len() > 0 then
			return;
		end
		if player.faction == FACTION_ALIEN then
			player.faction = FACTION_HUMAN;
			currentlyDisplaying = CLASS_ENGINEER;
		else
			player.faction = FACTION_ALIEN;
			currentlyDisplaying = CLASS_CYBORG;
		end
	end
end

function updateCrewSelect()
	renderStarfield();
	updateTextWriters();
	crewSelectDisplayStats(currentlyDisplaying);
 	displayCurrentCrew("Player"..ACTIVE_PLAYER);
	if getPlayer("Player"..ACTIVE_PLAYER).type == PLAYER_AI then
		crewSelectNextPlayer();
		return;
	end

	if ControlMan:getLeft() == true and debounce == true then
		debounce = false;
		crewSelectPageLeft();
	elseif ControlMan:getRight() == true and debounce == true then
		debounce = false;
		crewSelectPageRight();
	elseif ControlMan:getSTART() == true and debounce == true then
		debounce = false;
		crewSelectAddUnit(currentlyDisplaying);
	elseif (ControlMan:getUp() == true or ControlMan:getDown() == true) and debounce == true then
		debounce = false;
		crewSelectChangeFaction();
	elseif ControlMan:getBackspace() == true and debounce == true then
		debounce = false;
		getPlayer("Player"..ACTIVE_PLAYER).unitList:pop();
	elseif ControlMan:getSTART() == false and debounce == false
	and ControlMan:getLeft() == false and ControlMan:getRight() == false 
	and ControlMan:getUp() == false and ControlMan:getDown() == false 
	and ControlMan:getBackspace() == false then
		debounce = true;
	end
end

function crewSelectAddUnit(class)
	local player = getPlayer("Player"..ACTIVE_PLAYER);
	if player == nil then
		print ("Failed.. quit.. bugger it all...");
		quit();
	else
		if player:getUnitAmount() < 4 then
			player:addUnit(class);
		else
			crewSelectNextPlayer();
		end
	end
end

function crewSelectNextPlayer()
	print(ACTIVE_PLAYER .. ", " .. MAX_PLAYERS);
	if ACTIVE_PLAYER < MAX_PLAYERS - 1 then
		ACTIVE_PLAYER = ACTIVE_PLAYER + 1;
	else
		cleanupCrewSelect();
		ACTIVE_PLAYER = 0;
		setMenu(MISSION_MENU);
		initialiseMenus();
	end
end

function crewSelectPageRight()
	local player = getPlayer("Player"..ACTIVE_PLAYER);
	if player == nil then
		print ("Failed.. quit.. bugger it all...");
		quit();
	else
		if player.faction == FACTION_HUMAN then
			if currentlyDisplaying == CLASS_ENGINEER then
				currentlyDisplaying = CLASS_SOLDIER;
			elseif currentlyDisplaying == CLASS_MEDIC then
				currentlyDisplaying = CLASS_ENGINEER;
			elseif currentlyDisplaying == CLASS_SCOUT then
				currentlyDisplaying = CLASS_MEDIC;
			elseif currentlyDisplaying == CLASS_HEAVY then
				currentlyDisplaying = CLASS_SCOUT;
			elseif currentlyDisplaying == CLASS_COMMS then
				currentlyDisplaying = CLASS_HEAVY;
			elseif currentlyDisplaying == CLASS_SOLDIER then
				currentlyDisplaying = CLASS_COMMS;
			end
		elseif player.faction == FACTION_ALIEN then
			if currentlyDisplaying == CLASS_GHOST then
				currentlyDisplaying = CLASS_ALIEN_QUEEN;
			elseif currentlyDisplaying == CLASS_VIRUS then
				currentlyDisplaying = CLASS_GHOST;
			elseif currentlyDisplaying == CLASS_CYBORG then
				currentlyDisplaying = CLASS_VIRUS;
			elseif currentlyDisplaying == CLASS_GRUNT then
				currentlyDisplaying = CLASS_CYBORG;
			elseif currentlyDisplaying == CLASS_SIREN then
				currentlyDisplaying = CLASS_GRUNT;
			elseif currentlyDisplaying == CLASS_BLITZER then
				currentlyDisplaying = CLASS_SIREN;
			elseif currentlyDisplaying == CLASS_ALIEN_QUEEN then
				currentlyDisplaying = CLASS_BLITZER;
			end
		end
	end
end

function crewSelectPageLeft()
	local player = getPlayer("Player"..ACTIVE_PLAYER);
	if player == nil then
		print ("Failed.. quit.. bugger it all...");
		quit();
	else
		if player.faction == FACTION_HUMAN then
			if currentlyDisplaying == CLASS_ENGINEER then
				currentlyDisplaying = CLASS_MEDIC;
			elseif currentlyDisplaying == CLASS_MEDIC then
				currentlyDisplaying = CLASS_SCOUT;
			elseif currentlyDisplaying == CLASS_SCOUT then
				currentlyDisplaying = CLASS_HEAVY;
			elseif currentlyDisplaying == CLASS_HEAVY then
				currentlyDisplaying = CLASS_COMMS;
			elseif currentlyDisplaying == CLASS_COMMS then
				currentlyDisplaying = CLASS_SOLDIER;
			elseif currentlyDisplaying == CLASS_SOLDIER then
				currentlyDisplaying = CLASS_ENGINEER;
			end
		elseif player.faction == FACTION_ALIEN then
			if currentlyDisplaying == CLASS_GHOST then
				currentlyDisplaying = CLASS_VIRUS;
			elseif currentlyDisplaying == CLASS_VIRUS then
				currentlyDisplaying = CLASS_CYBORG;
			elseif currentlyDisplaying == CLASS_CYBORG then
				currentlyDisplaying = CLASS_GRUNT;
			elseif currentlyDisplaying == CLASS_GRUNT then
				currentlyDisplaying = CLASS_SIREN;
			elseif currentlyDisplaying == CLASS_SIREN then
				currentlyDisplaying = CLASS_BLITZER;
			elseif currentlyDisplaying == CLASS_BLITZER then
				currentlyDisplaying = CLASS_ALIEN_QUEEN;
			elseif currentlyDisplaying == CLASS_ALIEN_QUEEN then
				currentlyDisplaying = CLASS_GHOST;
			end
		end
	end
end

function cleanupCrewSelect()
	removeTextWriter("Crew Select");
end

function displayCurrentCrew( playerName )
	displayText(50, 400, "defaultFont16", 16, "Current Crew : Player " .. ACTIVE_PLAYER);

	local player = getPlayer(playerName);
	if player == nil then
		print("Failed Grabbing Player " .. playerName);
	else
		local unitTotal = player:getUnitAmount();
		if unitTotal > 0 then
			for unitNum = 1, unitTotal do
				local unit = player:getUnit(unitNum);
				crewSelectShowUnitPic(unit.class, 50 + (unitNum * 32), 420);
			end
		end
		if unitTotal == 4 then
			displayText(500, 400, "defaultFont16", 16, "Ready...");
		end
	end	

end

function crewSelectShowUnitPic( class, x, y )
	if class == CLASS_ENGINEER then
		TextureMan:blitTexture("tileData", x, y, 0, 192, 0, 32, 32);

	elseif class == CLASS_MEDIC then
		TextureMan:blitTexture("tileData", x, y, 0, 192, 96, 32, 32);

	elseif class == CLASS_SOLDIER then
		TextureMan:blitTexture("tileData", x, y, 0, 192, 32, 32, 32);

	elseif class == CLASS_COMMS then
		TextureMan:blitTexture("tileData", x, y, 0, 192, 128, 32, 32);

	elseif class == CLASS_SCOUT then
		TextureMan:blitTexture("tileData", x, y, 0, 192, 160, 32, 32);

	elseif class == CLASS_HEAVY then
		TextureMan:blitTexture("tileData", x, y, 0, 192, 64, 32, 32);

	elseif class == CLASS_CYBORG then
		TextureMan:blitTexture("tileData", x, y, 0, 224, 0, 32, 32);

	elseif class == CLASS_VIRUS then
		TextureMan:blitTexture("tileData", x, y, 0, 224, 96, 32, 32);

	elseif class == CLASS_GHOST then
		TextureMan:blitTexture("tileData", x, y, 0, 224, 160, 32, 32);

	elseif class == CLASS_GRUNT then
		TextureMan:blitTexture("tileData", x, y, 0, 224, 32, 32, 32);

	elseif class == CLASS_SIREN then
		TextureMan:blitTexture("tileData", x, y, 0, 224, 128, 32, 32);

	elseif class == CLASS_BLITZER then
		TextureMan:blitTexture("tileData", x, y, 0, 224, 64, 32, 32);

	elseif class == CLASS_ALIEN_QUEEN then
		TextureMan:blitTexture("tileData", x, y, 0, 192, 224, 32, 32);

	elseif class == CLASS_ALIEN_BROOD then
		TextureMan:blitTexture("tileData", x, y, 0, 224, 192, 32, 32);

	elseif class == CLASS_TURRET then
		TextureMan:blitTexture("tileData", x, y, 0, 192, 0, 32, 32);

	else
		if class ~= nil then
			print("Bugger Knows - " .. class);
		else
			print("BAD CLASS! TIS NIL!");
		end
	end
end

function crewSelectDisplayStats( class )
	crewSelectShowUnitPic(class, 60, 130);

	if class == CLASS_ENGINEER then
		displayText( 50, 100, "defaultFont16", 16, "Engineer" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 30" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 30" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 10" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Hack/Lock Door - 4AP");
		displayText( 100, 240, "defaultFont16", 16, "Build Turret - 8AP");

	elseif class == CLASS_MEDIC then
		displayText( 50, 100, "defaultFont16", 16, "Medic" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 20" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 20" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 30" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Heal - 1AP per HP");
		displayText( 100, 240, "defaultFont16", 16, "Cure - 10AP");

	elseif class == CLASS_SOLDIER then
		displayText( 50, 100, "defaultFont16", 16, "Soldier" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 40" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 20" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 10" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Aimed Shot - 5AP +25% Accuracy");
		displayText( 100, 240, "defaultFont16", 16, "Sniper Shot - 10AP +50% Accuracy");

	elseif class == CLASS_COMMS then
		displayText( 50, 100, "defaultFont16", 16, "Comms" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 25" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 20" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 25" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Detect - 2AP per Tile");
		displayText( 100, 240, "defaultFont16", 16, "Lure - 2AP per Tile");

	elseif class == CLASS_SCOUT then
		displayText( 50, 100, "defaultFont16", 16, "Scout" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 15" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 15" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 40" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Dodge - 5AP per Tile +5% Evade");
		displayText( 100, 240, "defaultFont16", 16, "Hide - 40AP");

	elseif class == CLASS_HEAVY then
		displayText( 50, 100, "defaultFont16", 16, "Heavy" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 10" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 40" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 20" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Kneel - 10AP");
		displayText( 100, 240, "defaultFont16", 16, "Stand - 10AP");

	elseif class == CLASS_CYBORG then
		displayText( 50, 100, "defaultFont16", 16, "Cyborg" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 30" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 30" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 10" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Hack/Lock Door - 4AP");
		displayText( 100, 240, "defaultFont16", 16, "Hack Turret - 8AP");

	elseif class == CLASS_VIRUS then
		displayText( 50, 100, "defaultFont16", 16, "Virus" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 20" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 20" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 30" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Heal - 1AP per HP");
		displayText( 100, 240, "defaultFont16", 16, "Infect - 20AP");

	elseif class == CLASS_GHOST then
		displayText( 50, 100, "defaultFont16", 16, "Ghost" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 15" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 15" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 40" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Dodge - 5AP per Tile +5% Evade");
		displayText( 100, 240, "defaultFont16", 16, "Hide - 40AP");

	elseif class == CLASS_GRUNT then
		displayText( 50, 100, "defaultFont16", 16, "Grunt" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 30" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 30" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 10" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Hack/Lock Door - 4AP");
		displayText( 100, 240, "defaultFont16", 16, "Build Turret - 8AP");

	elseif class == CLASS_SIREN then
		displayText( 50, 100, "defaultFont16", 16, "Siren" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 30" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 30" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 10" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Hack/Lock Door - 4AP");
		displayText( 100, 240, "defaultFont16", 16, "Build Turret - 8AP");

	elseif class == CLASS_BLITZER then
		displayText( 50, 100, "defaultFont16", 16, "Blitzer" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 10" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 40" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 20" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Kneel - 10AP");
		displayText( 100, 240, "defaultFont16", 16, "Stand - 10AP");

	elseif class == CLASS_ALIEN_QUEEN then
		displayText( 50, 100, "defaultFont16", 16, "Queen" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 50" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 10" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 10" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Lay Brood Egg - 2AP");
		displayText( 100, 240, "defaultFont16", 16, "Devour - 5AP");
		displayText( 150, 260, "defaultFont16", 16, "50% chance instant death");

	elseif class == CLASS_ALIEN_BROOD then
		displayText( 50, 100, "defaultFont16", 16, "Brood" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 10" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 0" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 10" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Hatch - 10AP");
		displayText( 100, 240, "defaultFont16", 16, "Spit - 5AP");

	elseif class == CLASS_TURRET then
		displayText( 50, 100, "defaultFont16", 16, "Turret" );
		displayText( 100, 120, "defaultFont16", 16, "Hit Points: 10" );
		displayText( 100, 140, "defaultFont16", 16, "Shield: 10" );
		displayText( 100, 160, "defaultFont16", 16, "Action Points: 5" );
		displayText( 50, 200, "defaultFont16", 16, "Skills");
		displayText( 100, 220, "defaultFont16", 16, "Self Destruct - 5AP +5DMG to adj. units");
		displayText( 100, 240, "defaultFont16", 16, "Aimed Shot - 5AP +25% Accuracy");

	else
		if class ~= nil then
			print("Bugger Knows - " .. class);
		else
			print("BAD CLASS! TIS NIL!");
		end
	end

end
