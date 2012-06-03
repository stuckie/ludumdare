-- derelict_ new game menu code

local currentChoice = 0;
local maxChoice = 2;
local offset = 200;
local currentPlayerCount = 2;
local minPlayerCount = 2;
local maxPlayerCount = 10; -- why not?

function initialiseNewGameMenu( )
	addTextWriter("derelict_", 240, 50, "defaultFont16", "derelict_", 0, 16);
	addTextWriter("New Game", 218, 150, "defaultFont16", "New Game", 0, 16);
	addTextWriter("SinglePlayer", 218, 200, "defaultFont16", "Single Player", 0, 16);
	addTextWriter("MultiPlayer", 218, 250, "defaultFont16", "Multi Player - ", 0, 16);
	addTextWriter("Main Menu", 218, 300, "defaultFont16", "Main Menu", 0, 16);
	addTextWriter("Credits", 32, 420, "defaultFont16", "A game by Steven Campbell for LD16", 0, 16);
	addTextWriter("Links", 190, 440, "defaultFont16", "www.ludumdare.com", 0, 16);
	addTextWriter("Links2", 150, 460, "defaultFont16", "www.stuckiegamez.co.uk", 0, 16);
end

function renderNewGameMenu( )
	-- My God It's Still Full of Stars!
	renderStarfield();
	updateTextWriters();
	displayText(200, offset + currentChoice * 50, "defaultFont16", 16, ">");
	displayText(500, 250, "defaultFont16", 16, "" .. currentPlayerCount);
	updateNewGameMenuControls();
end

local debounce = false;

function updateNewGameMenuControls ()
	if ControlMan:getUp() == true and debounce == true then
		debounce = false;
		if currentChoice > 0 then
			currentChoice = currentChoice - 1;
		end
	elseif ControlMan:getDown() == true and debounce == true then
		debounce = false;
		if currentChoice < maxChoice then
			currentChoice = currentChoice + 1;
		end
	elseif ControlMan:getLeft() == true and debounce == true then
		debounce = false;
		if currentPlayerCount > minPlayerCount then
			currentPlayerCount = currentPlayerCount - 1;
		end
	elseif ControlMan:getRight() == true and debounce == true then
		debounce = false;
		if currentPlayerCount < maxPlayerCount then
			currentPlayerCount = currentPlayerCount + 1;
		end
	elseif ControlMan:getSTART() == true and debounce == true then
		debounce = false;
		doNewGameMenuChoice();
	elseif ControlMan:getUp() == false and ControlMan:getDown() == false 
		and ControlMan:getLeft() == false and ControlMan:getRight() == false
		and ControlMan:getSTART() == false then
			debounce = true;
	end
end

function doNewGameMenuChoice()
	if currentChoice == 0 then	-- single player
		GAME_MODE = GAMEMODE_SINGLEPLAYER
		addPlayer("Player0", PLAYER_HUMAN, FACTION_HUMAN);
		addPlayer("Player1", PLAYER_AI, FACTION_ALIEN);
		MAX_PLAYERS = 1;
		cleanNewGameMenu();
		setMenu(CREW_MENU);
		initialiseMenus();
	elseif currentChoice == 1 then -- multi player
		GAME_MODE = GAMEMODE_MULTIPLAYER
		for i=0,currentPlayerCount do
			addPlayer("Player" .. i, PLAYER_HUMAN, FACTION_HUMAN);
		end
		addPlayer("Player"..currentPlayerCount+1, PLAYER_AI, FACTION_ALIEN);
		MAX_PLAYERS = currentPlayerCount;
		cleanNewGameMenu();
		setMenu(CREW_MENU);
		initialiseMenus();
	elseif currentChoice == 2 then -- back to Main Menu
		cleanNewGameMenu();
		setMenu(MAIN_MENU);
		initialiseMenus();
	end
end


function cleanNewGameMenu()
	removeTextWriter("derelict_");
	removeTextWriter("New Game");
	removeTextWriter("SinglePlayer");
	removeTextWriter("MultiPlayer");
	removeTextWriter("Main Menu");
	removeTextWriter("Credits");
	removeTextWriter("Links");
	removeTextWriter("Links2");
end
