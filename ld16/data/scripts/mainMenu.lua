-- derelict_ menu code

local currentChoice = 0;
local maxChoice = 3;
local offset = 150;
function initialiseMainMenu( )
	addTextWriter("derelict_", 240, 50, "defaultFont16", "derelict_", 1, 16);
	addTextWriter("New Game", 218, 150, "defaultFont16", "New Game", 2, 16);
	addTextWriter("Options", 218, 200, "defaultFont16", "Options", 2, 16);
	addTextWriter("Help", 218, 250, "defaultFont16", "Help", 2, 16);
	addTextWriter("Quit Game", 218, 300, "defaultFont16", "Quit Game", 2, 16);
	addTextWriter("Credits", 32, 420, "defaultFont16", "A game by Steven Campbell for LD16", 1, 16);
	addTextWriter("Links", 190, 440, "defaultFont16", "www.ludumdare.com", 1, 16);
	addTextWriter("Links2", 150, 460, "defaultFont16", "www.stuckiegamez.co.uk", 1, 16);
end

function renderMainMenu( )
	-- My God It's Full of Stars!
	renderStarfield();
	updateTextWriters();
	displayText(200, offset + currentChoice * 50, "defaultFont16", 16, ">");
	updateMenuControls();
end

local debounce = false;

function updateMenuControls ()
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
	elseif ControlMan:getSTART() == true and debounce == true then
		debounce = false;
		doMenuChoice();
	elseif ControlMan:getUp() == false and ControlMan:getDown() == false and ControlMan:getSTART() == false then
		debounce = true;
	end
end

function doMenuChoice()
	if currentChoice == 0 then	-- new game
		cleanMainMenu();
		setMenu(NEWGAME_MENU);
		initialiseMenus();
	elseif currentChoice == 1 then -- options
		-- move to options menu
		cleanMainMenu();
		setMenu(OPTIONS_MENU);
		initialiseMenus();
	elseif currentChoice == 2 then -- help
		-- move to help screens
		cleanMainMenu();
		setMenu(HELP_MENU);
		initialiseMenus();
	elseif currentChoice == 3 then -- quit
		quit();
	end
end


function cleanMainMenu()
	removeTextWriter("derelict_");
	removeTextWriter("New Game");
	removeTextWriter("Options");
	removeTextWriter("Help");
	removeTextWriter("Quit Game");
	removeTextWriter("Credits");
	removeTextWriter("Links");
	removeTextWriter("Links2");
end
