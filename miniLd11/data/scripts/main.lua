dofile ("data/scripts/config.sgz");
dofile ("data/scripts/quirk.lua");

Interpret = SGZInterpreter();
Renderer = SGZRenderer();
AudioMan = SGZAudioMan();
TextureMan = SGZTextureManager();
EntityMan = SGZEntityManager();
LevelMan = SGZLevelManager();

EntityMan:setMaxEntities(100);
LevelMan:setSize(100,100,2);

local littleQuirk = nil;

function main ( )
	startup();
	mainLoop();
	quit();
end

function startup( )
	Renderer:createWindow(WindowName,WindowWidth,WindowHeight,WindowBPP);
	TextureMan:addTexture("Sprites", "data/gfx/sprites.bmp");
	TextureMan:addTexMask("Sprites", "data/gfx/spritemask.bmp");

	-- create outer walls.
	for y=1,13 do
		for x=1,18 do
			if x == 1 or y == 1 or x == 18 or y == 13 then
				createWall("Solid", x, y, 0);
			end
		end
	end

	-- create bits of maze.
	createWall("UpRight", 17,12, 0);
	createWall("UpLeft", 2,12, 0);
	createWall("DownRight", 17,2, 0);
	createWall("DownLeft", 2,2, 0);
	createWall("Solid", 10, 12);
	createWall("Solid", 9, 12);
	createWall("Solid", 11, 6);
	createWall("Solid", 10, 6);
	createWall("DownRight", 10, 2);
	createWall("DownLeft", 11, 2);
	createWall("UpLeft", 11,12);
	createWall("UpLeft", 10,11);

	
	littleQuirk1 = QuirkClass.create(0, 255, 0, 200, 108, 0);
	littleQuirk2 = QuirkClass.create(255, 0, 0, 160, 108, 0);
	littleQuirk3 = QuirkClass.create(0, 0, 255, 100, 108, 0);
	littleQuirk4 = QuirkClass.create(0, 255, 255, 80, 108, 0);
	littleQuirk5 = QuirkClass.create(255, 255, 0, 220, 108, 0);
	littleQuirk6 = QuirkClass.create(255, 0, 255, 120, 108, 0);
end

function mainLoop( )
	local running = true;
	while running == true do
		running = Interpret:isRunning();	-- Ensure the Engine's still running
		littleQuirk1:update();
		littleQuirk2:update();
		littleQuirk3:update();
		littleQuirk4:update();
		littleQuirk5:update();
		littleQuirk6:update();
		LevelMan:render();
		Interpret:update();					-- Update the System
	end
end

function quit ( )
	Renderer:createWindow("Shutting Down...",WindowWidth,WindowHeight,WindowBPP);
	Interpret:quit();
end

local WallNum = 0;

function createWall ( WallType, x, y, z )
	WallNum = WallNum + 1;
	local WallTex = 0;
	local CurrentEntity = "Wall." .. WallType .. "." .. WallNum;

	if WallType == "Solid" then WallTex = 0; end
	if WallType == "UpLeft" then WallTex = 16; end
	if WallType == "DownLeft" then WallTex = 32; end
	if WallType == "DownRight" then WallTex = 48; end
	if WallType == "UpRight" then WallTex = 64; end
	
	LevelMan:addTile(CurrentEntity, WallType, x, y, z);
	LevelMan:texTile(CurrentEntity, "Sprites", "Sprites", 240, WallTex, 16, 16, 255, 0, 255);
	
end

function createTile( colR, colG, colB, x, y, z )
	WallNum = WallNum + 1;
	local WallTex = 0;
	local CurrentEntity = "Tile.1";
	
	EntityMan:add2DEntity(CurrentEntity);
	EntityMan:setDimensions(CurrentEntity, 20, 20, 0);
	EntityMan:setColour(CurrentEntity, colR, colG, colB );
	EntityMan:moveTo(CurrentEntity, x, y, z);
end
