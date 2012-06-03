-- Menu Loader

dofile ("data/scripts/mainMenu.lua");
dofile ("data/scripts/helpScreens.lua");
dofile ("data/scripts/crewSelectMenu.lua");
dofile ("data/scripts/optionsMenus.lua");
dofile ("data/scripts/newGameMenu.lua");
dofile ("data/scripts/changePlayerScreen.lua");
dofile ("data/scripts/missionMenus.lua");
dofile ("data/scripts/loadoutMenus.lua");

MAIN_MENU = 0;
HELP_MENU = 1;
CREW_MENU = 2;
OPTIONS_MENU = 3;
NEWGAME_MENU = 4;
LOADOUT_MENU = 5;
MISSION_MENU = 6;
CHANGE_PLAYER = 7;

local currentMenu = MAIN_MENU;

function initialiseMenus()
	if currentMenu == MAIN_MENU then
		initialiseMainMenu();
	elseif currentMenu == HELP_MENU then
		initialiseHelp();
	elseif currentMenu == OPTIONS_MENU then
		initialiseOptionsMenu();
	elseif currentMenu == CREW_MENU then
		initialiseCrewSelect();
	elseif currentMenu == NEWGAME_MENU then
		initialiseNewGameMenu();
	elseif currentMenu == LOADOUT_MENU then
		initialiseLoadoutMenu();
	elseif currentMenu == MISSION_MENU then
		initialiseMissionMenu();
	elseif currentMenu == CHANGE_PLAYER then
		initialiseChangePlayer();
	end

end

function updateMenuScreens()
	if currentMenu == MAIN_MENU then
		renderMainMenu();
	elseif currentMenu == HELP_MENU then
		renderHelp();
	elseif currentMenu == OPTIONS_MENU then
		renderOptionsMenu();
	elseif currentMenu == CREW_MENU then
		updateCrewSelect();
	elseif currentMenu == NEWGAME_MENU then
		renderNewGameMenu();
	elseif currentMenu == LOADOUT_MENU then
		updateLoadoutMenu();
	elseif currentMenu == MISSION_MENU then
		updateMissionMenu();
	elseif currentMenu == CHANGE_PLAYER then
		updateChangePlayer();
	end
end

function setMenu( menu )
	currentMenu = menu;
end
