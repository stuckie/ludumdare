-- derelict_ help screens

local currentScreen = 0;
local maxScreens = 5;
local helpString = 1;
local maxHelpstrings = 9;
local debounce = false;

function initialiseHelp( )
	addTextWriter("derelict_", 240, 50, "defaultFont16", "derelict_", 1, 16);
	addTextWriter("Help1_1", 50, 150, "defaultFont16", "Controls: Arrow Keys - move.", 0.5, 16);
	addTextWriter("Help1_2", 50, 170, "defaultFont16", "A - activate Movement mode", 0.5, 16);
	addTextWriter("Help1_3", 50, 190, "defaultFont16", "S - activate Firing mode", 0.5, 16);
	addTextWriter("Help1_4", 50, 210, "defaultFont16", "D - activate Door mode", 0.5, 16);
	addTextWriter("Help1_5", 50, 230, "defaultFont16", "Q - activate Skill 1", 0.5, 16);
	addTextWriter("Help1_6", 50, 250, "defaultFont16", "E - activate Skill 2", 0.5, 16);
	addTextWriter("Help1_7", 50, 270, "defaultFont16", "1 - 4 - display unit stats", 0.5, 16);
	addTextWriter("Help1_8", 50, 290, "defaultFont16", "Return - Confirm", 0.5, 16);
	addTextWriter("Help1_9", 50, 310, "defaultFont16", "Backspace - Cancel", 0.5, 16);

	getTextWriter("Help1_2").isActive = false;
	getTextWriter("Help1_3").isActive = false;
	getTextWriter("Help1_4").isActive = false;
	getTextWriter("Help1_5").isActive = false;
	getTextWriter("Help1_6").isActive = false;
	getTextWriter("Help1_7").isActive = false;
	getTextWriter("Help1_8").isActive = false;
	getTextWriter("Help1_9").isActive = false;

	helpString = 1;
	currentScreen = 0;

end

function renderHelp( )
	-- My God It's Full of Stars!
	renderStarfield();
	updateTextWriters();
	updateHelpControls();
end

function updateHelpControls ()
	if ControlMan:getUp() == true and debounce == true then
		debounce = false;
		if currentScreen > 0 then
			currentScreen = currentScreen - 1;
		end
	elseif ControlMan:getDown() == true and debounce == true then
		debounce = false;
		if currentScreen < maxScreens then
			currentScreen = currentScreen + 1;
		end
	elseif ControlMan:getSTART() == true and debounce == true then
		debounce = false;
		cleanHelpScreens();
		setMenu(MAIN_MENU);
		initialiseMenus();
		return;
	elseif ControlMan:getUp() == false and ControlMan:getDown() == false and ControlMan:getSTART() == false then
		debounce = true;
	end

	if getTextWriter("Help1_" .. helpString).isActive == false then
		if helpString < maxHelpstrings then
			helpString = helpString + 1;
		end
		getTextWriter("Help1_" .. helpString).isActive = true
	end
end

function cleanHelpScreens()
	removeTextWriter("derelict_");
	removeTextWriter("Help1_1");
	removeTextWriter("Help1_2");
	removeTextWriter("Help1_3");
	removeTextWriter("Help1_4");
	removeTextWriter("Help1_5");
	removeTextWriter("Help1_6");
	removeTextWriter("Help1_7");
	removeTextWriter("Help1_8");
	removeTextWriter("Help1_9");
end
