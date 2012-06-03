-- YARGH! graphic routines - some pinched from derelict_

dofile("data/scripts/hud.lua");

local textWriterStrings = List:new();
local pirateAttackClouds = List:new();
local cannonBalls = List:new();
local shipAttackClouds = List:new();

fireCannonBall = function(x, y, targetX, targetY, enemy)
	cannonBalls:append({x = x, y = y, u = 240, v= 128, w=16, h=16, sheet="BlockTerrain", targetX = targetX, targetY = targetY, speed = 50, enemy = enemy});
	shipAttackClouds:append({x=x-8, y=y-8, u=0, v=128, w=32, h=32, sheet="BlockTerrain", anim=0, animChange=0.2, animTime = 0.2});
end

addPirateAttackCloud = function(x, y)
	pirateAttackClouds:append({x=x, y=y, u=0, v=192, w=64, h=64, sheet="BlockTerrain", anim=0, animChange=0.1, animTime = 0.1, ttl=10});
end

updateMiscGraphics = function()
	for i,cannonBall in ipairs(cannonBalls) do
		local x = cannonBall.targetX - cannonBall.x;
		local y = cannonBall.targetY - cannonBall.y;

		local speed = cannonBall.speed * DeltaTime;
		local radAngle = math.atan2(y, x);
		local angle = (math.deg(radAngle) + 180);

		cannonBall.x = cannonBall.x + ( math.cos(radAngle) * speed );
		cannonBall.y = cannonBall.y + ( math.sin(radAngle) * speed );

		if calcDistanceXY(cannonBall.x, cannonBall.y, cannonBall.targetX, cannonBall.targetY) < 1.0 then
			shipAttackClouds:append({x=cannonBall.x-8, y=cannonBall.y-8, u=0, v=128, w=32, h=32, sheet="BlockTerrain", anim=0, animChange=0.2, animTime = 0.2});
			if calcDistanceXY(cannonBall.x, cannonBall.y, cannonBall.enemy.x, cannonBall.enemy.y) < 64.0 then
				cannonBall.enemy:damage(10);
			end
			cannonBalls:remove(cannonBall);
		end

		if (calcDistanceX((gameCamera.x*64) + 64, cannonBall.x*64) < WindowWidth + 64
		and calcDistanceY((gameCamera.y*64) + 64, cannonBall.y*64) < WindowHeight + 64) then
			TextureMan:blitTexture(cannonBall.sheet, cannonBall.x - gameCamera.x * 64, cannonBall.y - gameCamera.y * 64, 0, cannonBall.u, cannonBall.v, cannonBall.w, cannonBall.h);
		end
	end

	for i,cloud in ipairs(shipAttackClouds) do
		cloud.animTime = cloud.animTime - DeltaTime;
		if cloud.animTime < 0 then
			cloud.anim = cloud.anim + 1;
			if cloud.anim == 4 then
				shipAttackClouds:remove(cloud);
				break
			end
			cloud.u = cloud.u + (cloud.w * cloud.anim);
			cloud.animTime = cloud.animChange;
		end

		if (calcDistanceX((gameCamera.x*64) + 64, cloud.x*64) < WindowWidth + 64
		and calcDistanceY((gameCamera.y*64) + 64, cloud.y*64) < WindowHeight + 64) then
			TextureMan:blitTexture(cloud.sheet, cloud.x - gameCamera.x * 64, cloud.y - gameCamera.y * 64, 0, cloud.u, cloud.v, cloud.w, cloud.h);
		end
	end

	for i,pirateCloud in ipairs(pirateAttackClouds) do
		pirateCloud.animTime = pirateCloud.animTime - DeltaTime;
		pirateCloud.ttl = pirateCloud.ttl - DeltaTime;
		if pirateCloud.animTime < 0 then
			pirateCloud.anim = pirateCloud.anim + 1;
			if pirateCloud.anim == 4 then pirateCloud.anim = 0 end
			pirateCloud.u = pirateCloud.w * pirateCloud.anim;
			pirateCloud.animTime = pirateCloud.animChange;
		end

		if (calcDistanceX((gameCamera.x*64) + 64, pirateCloud.x*64) < WindowWidth + 64
		and calcDistanceY((gameCamera.y*64) + 64, pirateCloud.y*64) < WindowHeight + 64) then
			TextureMan:blitTexture(pirateCloud.sheet, pirateCloud.x - gameCamera.x * 64, pirateCloud.y - gameCamera.y * 64, 0, pirateCloud.u, pirateCloud.v, pirateCloud.w, pirateCloud.h);
		end

		if pirateCloud.ttl < 0 then
			pirateAttackClouds:remove(pirateCloud);
		end
	end
end

initialiseFonts = function()
	TextureMan:addTexture("defaultFont16", "data/gfx/font16x16.bmp");
	TextureMan:setColourKey("defaultFont16", 255, 0, 255);
	TextureMan:addTexture("defaultFont8", "data/gfx/font8x8.png");
	TextureMan:setColourKey("defaultFont8", 255, 0, 255);
end

initialiseGraphics = function()
	TextureMan:addTexture("BlockTerrain", "data/gfx/BlockTiles.png");
	TextureMan:setColourKey("BlockTerrain", 255, 0, 255);
	TextureMan:addTexture("BlendTerrain", "data/gfx/BlendTiles.png");
	TextureMan:addTexture("InsideBlendTerrain", "data/gfx/InsideBlendTiles.png");

	TextureMan:addTexture("Hud", "data/gfx/Hud.png");
	TextureMan:setColourKey("Hud", 255, 0, 255);

	TextureMan:addTexture("RedBeard", "data/gfx/RedBeard.png");
	TextureMan:setColourKey("RedBeard", 255, 0, 255);
	TextureMan:addTexture("BlackBeard", "data/gfx/BlackBeard.png");
	TextureMan:setColourKey("BlackBeard", 255, 0, 255);
	TextureMan:addTexture("BlueBeard", "data/gfx/BlueBeard.png");
	TextureMan:setColourKey("BlueBeard", 255, 0, 255);
	TextureMan:addTexture("PinkBeard", "data/gfx/PinkBeard.png");
	TextureMan:setColourKey("PinkBeard", 255, 0, 255);
	TextureMan:addTexture("GreenBeard", "data/gfx/GreenBeard.png");
	TextureMan:setColourKey("GreenBeard", 255, 0, 255);
	TextureMan:addTexture("GreyBeard", "data/gfx/GreyBeard.png");
	TextureMan:setColourKey("GreyBeard", 255, 0, 255);

	TextureMan:addTexture("Neutral", "data/gfx/Neutral.png");
	TextureMan:setColourKey("Neutral", 255, 0, 255);
end

addTextWriter = function ( name, x, y, fontName, text, delay, fontSize, timeToLive )
	textWriterStrings:append({name = name, x = x, y = y, fontName = fontName, fontSize = fontSize, string = text, delay = delay, writerPosition = 0, timeToPrint = delay, isActive = true, timeToLive = timeToLive});
end

removeTextWriter = function( name )
	for i,text in ipairs(textWriterStrings) do
		if text.name == name then
			textWriterStrings:remove(text);
			return;
		end
	end
end

getTextWriter = function( name )
	for i,text in ipairs(textWriterStrings) do
		if text.name == name then
			return text;
		end
	end
	return nil;
end

updateTextWriters = function()
	for i,text in ipairs(textWriterStrings) do
		if text.isActive == true then
			text.timeToPrint = text.timeToPrint - 0.1;
			if text.timeToPrint < 0.0 then
				text.timeToPrint = text.delay;
				if text.writerPosition < text.string:len() then
					text.writerPosition = text.writerPosition + 1;
				end
			end
			if text.writerPosition == text.string:len() then
				text.isActive = false;
			end
		end

		if text.timeToLive > 0 then
			text.timeToLive = text.timeToLive - DeltaTime;
		end

		local textString = string.sub(text.string, 1, text.writerPosition);
		displayText( text.x, text.y, text.fontName, text.fontSize, textString );
		if text.timeToLive < 0 then
			textWriterStrings:remove(text);
		end
	end
end

displayText = function( x, y, fontName, fontSize, text )
	local textPos = {};
	textPos.x = x;
	textPos.y = y;
	for c in text:gmatch"." do
		TextureMan:blitTexture(fontName, textPos.x, textPos.y, 0, 0, (string.byte(c) - 33) * fontSize, fontSize, fontSize);
		textPos.x = textPos.x + fontSize;
	end
end

displayLayer0 = function( tileCode, x, y )
	local tileTex = { sheet = "BlockTerrain", x = 0, y = 0, w = 64, h = 64 };

	if tileCode == "0" then -- sea
		tileTex.x = 0;
		tileTex.y = 0;
	end

	if tileCode == "1" then -- sand
		tileTex.x = 128;
		tileTex.y = 0;
	end

	if tileCode == "2" then -- grass
		tileTex.x = 64;
		tileTex.y = 0;
	end

	if tileCode == "a" then -- Sea To Sand, Top Left
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 0;
		tileTex.y = 128;
	end

	if tileCode == "b" then -- Sea To Sand, Top Right
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 64;
		tileTex.y = 128;
	end

	if tileCode == "c" then -- Sea To Sand, Bottom Left
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 128;
		tileTex.y = 128;
	end

	if tileCode == "d" then -- Sea To Sand, Bottom Right
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 192;
		tileTex.y = 128;
	end

	if tileCode == "e" then -- Sea To Sand, Left Vert
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 0;
		tileTex.y = 192;
	end

	if tileCode == "f" then -- Sea To Sand, Bottom Horiz
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 192;
		tileTex.y = 192;
	end

	if tileCode == "g" then -- Sea To Sand, Right Vert
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 64;
		tileTex.y = 192;
	end

	if tileCode == "h" then -- Sea To Sand, Top Horiz
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 128;
		tileTex.y = 192;
	end

	if tileCode == "i" then -- Sand To Grass, Top Left
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 64;
		tileTex.y = 64;
	end

	if tileCode == "j" then -- Sea To Sand, Top Right
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 128;
		tileTex.y = 64;
	end

	if tileCode == "k" then -- Sea To Sand, Bottom Left
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 0;
		tileTex.y = 64;
	end

	if tileCode == "l" then -- Sea To Sand, Bottom Right
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 192;
		tileTex.y = 64;
	end

	if tileCode == "m" then -- Sea To Sand, Left Vert
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 192;
		tileTex.y = 0;
	end

	if tileCode == "n" then -- Sea To Sand, Bottom Horiz
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 128;
		tileTex.y = 0;
	end

	if tileCode == "o" then -- Sea To Sand, Right Vert
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 64;
		tileTex.y = 0;
	end

	if tileCode == "p" then -- Sea To Sand, Top Horiz
		tileTex.sheet = "BlendTerrain"
		tileTex.x = 0;
		tileTex.y = 0;
	end

	if tileCode == "q" then -- Sea To Sand Inside, Bottom Right
		tileTex.sheet = "InsideBlendTerrain"
		tileTex.x = 0;
		tileTex.y = 0;
	end

	if tileCode == "r" then -- Sea To Sand Inside, Bottom Left
		tileTex.sheet = "InsideBlendTerrain"
		tileTex.x = 64;
		tileTex.y = 0;
	end

	if tileCode == "s" then -- Sea To Sand Inside, Top Left
		tileTex.sheet = "InsideBlendTerrain"
		tileTex.x = 128;
		tileTex.y = 0;
	end

	if tileCode == "t" then -- Sea To Sand Inside, Top Right
		tileTex.sheet = "InsideBlendTerrain"
		tileTex.x = 192;
		tileTex.y = 0;
	end

	if tileCode == "u" then -- Grass To Sand Inside, Bottom Right
		tileTex.sheet = "InsideBlendTerrain"
		tileTex.x = 0;
		tileTex.y = 64;
	end

	if tileCode == "v" then -- Grass To Sand, Bottom Left
		tileTex.sheet = "InsideBlendTerrain"
		tileTex.x = 64;
		tileTex.y = 64;
	end

	if tileCode == "w" then -- Grass To Sand, Top Right
		tileTex.sheet = "InsideBlendTerrain"
		tileTex.x = 128;
		tileTex.y = 64;
	end

	if tileCode == "x" then -- Grass To Sand, Top Left
		tileTex.sheet = "InsideBlendTerrain"
		tileTex.x = 192;
		tileTex.y = 64;
	end

	TextureMan:blitTexture(tileTex.sheet, x, y, 0, tileTex.x, tileTex.y, tileTex.w, tileTex.h);
end

displayLayer1 = function( tileCode, x, y )
	local tileTex = { sheet = "BlockTerrain", x = 0, y = 0, w = 64, h = 64 };

	if tileCode == "0" then return end

	if tileCode == "1" then -- rock
		tileTex.x = 192;
		tileTex.y = 0;
	end

	if tileCode == "2" then -- tree
		tileTex.x = 64;
		tileTex.y = 64;
	end

	if tileCode == "3" then -- chest
		tileTex.x = 0;
		tileTex.y = 64;
	end

	if tileCode == "4" then -- neutral fort
		tileTex.x = 128;
		tileTex.y = 64;
	end

	if tileCode == "5" then -- mine
		tileTex.x = 192;
		tileTex.y = 64;
	end

	if tileCode == "a" then -- BlackBeard Fort
		tileTex.sheet = "BlackBeard";
		tileTex.x = 192;
		tileTex.y = 192;
	end

	if tileCode == "b" then -- BlueBeard Fort
		tileTex.sheet = "BlueBeard";
		tileTex.x = 192;
		tileTex.y = 192;
	end

	if tileCode == "c" then -- RedBeard Fort
		tileTex.sheet = "RedBeard";
		tileTex.x = 192;
		tileTex.y = 192;
	end

	if tileCode == "d" then -- PinkBeard Fort
		tileTex.sheet = "PinkBeard";
		tileTex.x = 192;
		tileTex.y = 192;
	end

	if tileCode == "e" then -- GreenBeard Fort
		tileTex.sheet = "GreenBeard";
		tileTex.x = 192;
		tileTex.y = 192;
	end

	if tileCode == "f" then -- GreyBeard Fort
		tileTex.sheet = "GreyBeard";
		tileTex.x = 192;
		tileTex.y = 192;
	end

	TextureMan:blitTexture(tileTex.sheet, x, y, 0, tileTex.x, tileTex.y, tileTex.w, tileTex.h);
end
