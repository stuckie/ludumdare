-- derelict_ graphic routines

local starField = List:new();
local textWriterStrings = List:new();
local maxStars = 100;

function initialiseFonts()
	TextureMan:addTexture("defaultFont16", "data/gfx/font16x16.bmp");
	TextureMan:setColourKey("defaultFont16", 255, 0, 255);
	TextureMan:addTexture("defaultFont8", "data/gfx/font8x8.png");
	TextureMan:setColourKey("defaultFont8", 255, 0, 255);
end

function initialiseStarfield()
	for star = 0, maxStars do
		starField:append({x = math.random() * 640, y = math.random() * 480, speed = 1 + math.random() * 9});
	end
end

function renderStarfield()
	for i,star in ipairs(starField) do
		displayText( star.x, star.y, "defaultFont8", 8, "." );
		star.x = star.x - star.speed;

		if star.x < -16 then
			star.x = 650;
		end
	end
end

function addTextWriter( name, x, y, fontName, text, delay, fontSize )
	textWriterStrings:append({name = name, x = x, y = y, fontName = fontName, fontSize = fontSize, string = text, delay = delay, writerPosition = 0, timeToPrint = delay, isActive = true});
end

function removeTextWriter( name )
	for i,text in ipairs(textWriterStrings) do
		if text.name == name then
			textWriterStrings:remove(text);
		end
	end
end

function getTextWriter( name )
	for i,text in ipairs(textWriterStrings) do
		if text.name == name then
			return text;
		end
	end
	return nil;
end

function updateTextWriters()
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
		
		local textString = string.sub(text.string, 1, text.writerPosition);
		displayText( text.x, text.y, text.fontName, text.fontSize, textString );
	end
end


function displayText( x, y, fontName, fontSize, text )
	local textPos = {};
	textPos.x = x;
	textPos.y = y;
	for c in text:gmatch"." do
		TextureMan:blitTexture(fontName, textPos.x, textPos.y, 0, 0, (string.byte(c) - 33) * fontSize, fontSize, fontSize);
		textPos.x = textPos.x + fontSize;
	end
end

function displayTile ( wallCode, textureSheet, x, y )
	local wallTex = { u = 0, v = 0, w = 0, h = 0 };

	if wallCode == "0" then 
		wallTex.x = 0; 
		wallTex.y = 0;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "1" then 
		wallTex.x = 0; 
		wallTex.y = 32;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "2" then 
		wallTex.x = 0; 
		wallTex.y = 64;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "3" then  
		wallTex.x = 0; 
		wallTex.y = 96;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "4" then 
		wallTex.x = 0; 
		wallTex.y = 128;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "5" then 
		wallTex.x = 0; 
		wallTex.y = 160;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "6" then 
		wallTex.x = 0; 
		wallTex.y = 192;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "7" then 
		wallTex.x = 0; 
		wallTex.y = 224;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "8" then 
		wallTex.x = 32; 
		wallTex.y = 0;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "9" then  
		wallTex.x = 32; 
		wallTex.y = 32;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "A" then  
		wallTex.x = 32; 
		wallTex.y = 64;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "B" then  
		wallTex.x = 32; 
		wallTex.y = 96;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "C" then 
		wallTex.x = 32; 
		wallTex.y = 128;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "D" then 
		wallTex.x = 32; 
		wallTex.y = 160;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "E" then 
		wallTex.x = 32; 
		wallTex.y = 192;
		wallTex.w = 32;
		wallTex.h = 32;
	end


	if wallCode == "F" then  
		wallTex.x = 32; 
		wallTex.y = 224;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "G" then  
		wallTex.x = 64; 
		wallTex.y = 0;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "H" then 
		wallTex.x = 64; 
		wallTex.y = 32;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "blip" then
		wallTex.x = 192;
		wallTex.y = 192;
		wallTex.w = 32;
		wallTex.h = 32;
	end

	if wallCode == "fade" then
		wallTex.x = 64;
		wallTex.y = 64;
		wallTex.w = 32;
		wallTex.h = 32;
	end
  
	TextureMan:blitTexture(textureSheet, x, y, 0, wallTex.x, wallTex.y, wallTex.w, wallTex.h);
  
end