-- derelict_ loader

derelictNumber = 1;
local maxDerelicts = 1;

--- hack.. these should be in the file itself
derelictRoomHeight = 15;
derelictRoomWidth = 20;
derelictFloorDepth = 2;
derelictFloorWidth = 6;
derelictFloorHeight = 2;

function loadLevel ( derelictNum )
	if derelictNum < maxDerelicts then
		derelictNumber = derelictNum;
	else
		derelictNumber = 1;
	end

	TextureMan:addTexture("tileData", "data/gfx/derelict_" .. derelictNumber .. ".png");
	TextureMan:setColourKey("tileData", 255, 0, 255);
	dofile("data/levels/derelict_" .. derelictNumber .. "/loadDerelict.lua");
	loadDerelict();

end
