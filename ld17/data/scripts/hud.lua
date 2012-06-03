-- HUD like stuff

local math = math;

local displayTroopPic = function(player, x, y)

end

local displayCaptainPic = function(player,x, y)
end

local displayUnitStats = function(unit)
end

local displayOverallStats = function(player)
end

local hudList = List:new();

addHudElement = function(x, y, timeToLive, text)
	hudList:append({x=x, y=y, timeToLive=timeToLive, text = text});
end

drawHud = function(player)
	if player.currentUnit ~= nil then
		local unit = player.currentUnit;
		TextureMan:blitTexture("Hud", WindowWidth - 300, 20, 0, 0, 0, 256, 256);
		TextureMan:blitTexture(player.beard, WindowWidth - 120, 70, 0, player.pirate.u, player.pirate.v, 64, 64);
		displayText( WindowWidth - 265, 15, "defaultFont16", 16, unit.type );
		displayText( WindowWidth - 280, 50, "defaultFont16", 16, "Morale: " .. unit.morale );
		displayText( WindowWidth - 280, 65, "defaultFont16", 16, "Gold  : " .. unit.gold );
		displayText( WindowWidth - 280, 80, "defaultFont16", 16, "Men   : " .. unit.men );
		displayText( WindowWidth - 280, 120, "defaultFont16", 16, unit.state );
		if unit.type == "Pirate Ship" then
			displayText( WindowWidth - 280, 35, "defaultFont16", 16, "Damage: " .. unit.health );
		end
	end

	for i,hud in ipairs(hudList) do
		if hud.timeToLive > 0 then
			hud.timeToLive = hud.timeToLive - DeltaTime;
		end

		TextureMan:blitTexture("Hud", hud.x, hud.y, 0, 0, 0, 256, 128);
		TextureMan:blitTexture(player.beard, hud.x + 182, hud.y + 10, 0, player.captain.u, player.captain.v, 64, 64);
		local text = hud.text;
		for i,textString in ipairs(text) do
			displayText( hud.x + textString.x, hud.y + textString.y, "defaultFont16", 16, textString.text );
		end
		if hud.timeToLive < 0 then
			hudList:remove(hud);
		end
	end
end