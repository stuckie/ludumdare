-- HUD stuff

local hudElements = List:new();
local localCommand;

function addHudElement( name, entity, x, y )
	hudElements:append({name = name, entity = entity, x = x, y = y});
end

function clearHudElements()
	hudElements:clear();
end

function removeHudElement( name )
	hudElements:pop();
end

function hudElementExists( name )
	for i=1,hudElements:len() do
		local hud = hudElements[i];
		if hud.name == name then
			return true;
		end
	end
	return false;
end

function renderHudElements()
	displayText( 0, 0, "defaultFont8", 8, "derelict_ 0.01" );
	if localCommand == COMMAND_MOVE then
		displayText( 300, 464, "defaultFont16", 16, "COMMAND_MOVE" );
	elseif localCommand == COMMAND_FIRE then
		displayText( 300, 464, "defaultFont16", 16, "COMMAND_FIRE" );
	elseif localCommand == COMMAND_DOOR then
		displayText( 300, 464, "defaultFont16", 16, "COMMAND_DOOR" );
	elseif localCommand == COMMAND_SKILL1 then
		displayText( 300, 464, "defaultFont16", 16, "COMMAND_SKILL1" );
	elseif localCommand == COMMAND_SKILL2 then
		displayText( 300, 464, "defaultFont16", 16, "COMMAND_SKILL2" );
	end

	for i = 1, hudElements:len() do
		local hud = hudElements[i];
		if hud ~= nil then
			TextureMan:blitTexture("tileData", hud.x, hud.y, 0, 96, 96, 96, 96);
			displayText(hud.x + 24, hud.y + 78, "defaultFont8", 8, hud.name);
			displayText(hud.x + 12, hud.y + 16, "defaultFont8", 8, "HP: " .. hud.entity.hp .. "/" .. hud.entity.hpMax);
			displayText(hud.x + 12, hud.y + 32, "defaultFont8", 8, "SP: " .. hud.entity.sp .. "/" .. hud.entity.spMax);
			displayText(hud.x + 12, hud.y + 64, "defaultFont8", 8, "AP: " .. hud.entity.ap .. "/" .. hud.entity.apMax);
		end
	end

end

function hudDisplayCommand( command )
	localCommand = command;

end
