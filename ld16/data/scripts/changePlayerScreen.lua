-- derelict_ change player screen

function initialiseChangePlayer( )
	addTextWriter("derelict_", 240, 50, "defaultFont16", "derelict_", 0, 16);
	addTextWriter("Player", 240, 150, "defaultFont16", "Player " .. ACTIVE_PLAYER, 1, 16);
	addTextWriter("Press Return", 210, 350, "defaultFont16", "Press Return", 2, 16);
	clearHudElements();
end

local debounce = false;
function updateChangePlayer( )
	-- My God It's Full of Stars!
	renderStarfield();
	updateTextWriters()

	if getPlayer("Player" .. ACTIVE_PLAYER).type == PLAYER_AI then
		displayText(240, 200, "defaultFont16", 16, "AI Turn");
	else
		displayText(240, 200, "defaultFont16", 16, "Human Turn");
	end

	if ControlMan:getSTART() == true and debounce == true then
		debounce = false;
		getPlayer("Player" .. ACTIVE_PLAYER):resetUnits();
		clearHudElements();
		cleanChangePlayer();
		changeState(GAME_STATE);
	elseif ControlMan:getSTART() == false and debounce == false then
		debounce = true;
	end
end


function cleanChangePlayer()
	removeTextWriter("derelict_");
	removeTextWriter("Player");
	removeTextWriter("Press Return");
end
