-- derelict_ options code

local currentChoice = 0;
local maxChoice = 1;
local offset = 150;
local fullscreen = false;

function initialiseOptionsMenu( )
	addTextWriter("derelict_", 240, 50, "defaultFont16", "derelict_", 1, 16);
	addTextWriter("Fullscreen", 218, 150, "defaultFont16", "Fullscreen", 2, 16);
	addTextWriter("Main Menu", 218, 200, "defaultFont16", "Main Menu", 2, 16);
	addTextWriter("Credits", 32, 420, "defaultFont16", "A game by Steven Campbell for LD16", 1, 16);
	addTextWriter("Links", 190, 440, "defaultFont16", "www.ludumdare.com", 1, 16);
	addTextWriter("Links2", 150, 460, "defaultFont16", "www.stuckiegamez.co.uk", 1, 16);
end

function renderOptionsMenu( )
	-- My God It's Full of Stars!
	renderStarfield();
	updateTextWriters();
	displayText(200, offset + currentChoice * 50, "defaultFont16", 16, ">");
	if fullscreen == false then
		displayText(400, 150, "defaultFont16", 16, "FALSE");
	else
		displayText(400, 150, "defaultFont16", 16, "TRUE");
	end
	updateOptionMenuControls();
end

local debounce = false;
function updateOptionMenuControls ()
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
		doOptionMenuChoice();
	elseif ControlMan:getUp() == false and ControlMan:getDown() == false and ControlMan:getSTART() == false then
		debounce = true;
	end
end

function doOptionMenuChoice()
	if currentChoice == 0 then	-- fullscreen
		if fullscreen == false then
			fullscreen = true;
		else
			fullscreen = false;
		end

		Renderer:setFullscreen(fullscreen);
	elseif currentChoice == 1 then -- back to menu
		cleanOptionsMenu();
		initialiseMainMenu();
		setMenu(MAIN_MENU);
	end
end

function cleanOptionsMenu()
	removeTextWriter("derelict_");
	removeTextWriter("Fullscreen");
	removeTextWriter("Main Menu");
	removeTextWriter("Credits");
	removeTextWriter("Links");
	removeTextWriter("Links2");
end
