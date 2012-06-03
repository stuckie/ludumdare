-- derelict_ change mission screen

function initialiseMissionMenu( )
	addTextWriter("derelict_", 240, 50, "defaultFont16", "derelict_", 0, 16);
	addTextWriter("Missions", 240, 150, "defaultFont16", "Missions", 1, 16);
	addTextWriter("Press Return", 210, 350, "defaultFont16", "Press Return", 2, 16);

	initialiseGame();

	if GAME_MODE == GAMEMODE_SINGLEPLAYER then
		local player = getPlayer("Player0");
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i, 23, 1);
		end
		player = getPlayer("Player1");
		player:addUnit(CLASS_ALIEN_QUEEN);
		local alien = player:getUnit(1);
		alien:setPosition(50, 5, 1);
		player:addUnit(CLASS_ALIEN_QUEEN);
		alien = player:getUnit(2);
		alien:setPosition(50, 5, 0);
		player:addUnit(CLASS_ALIEN_QUEEN);
		alien = player:getUnit(3);
		alien:setPosition(50, 5, 2);
		player:addUnit(CLASS_ALIEN_QUEEN);
		alien = player:getUnit(4);
		alien:setPosition(6, 10, 1);

		addTextWriter("Mission1", 50, 200, "defaultFont16", "We have detected the presence", 1, 16);
		addTextWriter("Mission2", 50, 220, "defaultFont16", "of four Alien Queens within.", 1, 16);
		addTextWriter("Mission3", 50, 240, "defaultFont16", "You must wipe them out before", 1, 16);
		addTextWriter("Mission4", 50, 260, "defaultFont16", "their Brood take control!", 1, 16);
	elseif GAME_MODE == GAMEMODE_MULTIPLAYER then
		addTextWriter("Mission1", 50, 200, "defaultFont16", "Humans: Destroy the Aliens!", 1, 16);
		addTextWriter("Mission2", 50, 240, "defaultFont16", "Aliens: Destroy the Humans!", 1, 16);
	end
end

local debounce = false;
function updateMissionMenu( )
	-- My God It's Full of Stars!
	renderStarfield();
	updateTextWriters();

	if ControlMan:getSTART() == true and debounce == true then
		debounce = false;
		cleanMissionMenu();
		setMenu(LOADOUT_MENU);
		initialiseMenus();
	elseif ControlMan:getSTART() == false and debounce == false then
		debounce = true;
	end
end


function cleanMissionMenu()
	removeTextWriter("derelict_");
	removeTextWriter("Missions");
	removeTextWriter("Mission1");
	removeTextWriter("Mission2");
	removeTextWriter("Mission3");
	removeTextWriter("Mission4");
	removeTextWriter("Press Return");
end
