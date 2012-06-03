-- Moons of Subterrene
-- Made for LudumDare 15
-- 29-30th August 2009
-- Steven "Stuckie" Campbell

dofile ("data/scripts/config.sgz");
dofile ("data/scripts/level.lua");
dofile ("data/scripts/list.lua");
dofile ("data/scripts/player.lua");
dofile ("data/scripts/bullets.lua");

Interpret = SGZInterpreter();
Renderer = SGZRenderer();
AudioMan = SGZAudioMan();
TextureMan = SGZTextureManager();
EntityMan = SGZEntityManager();
LevelMan = SGZLevelManager();
ControlMan = SGZControlManager();

EntityMan:setMaxEntities(260);

MaxTilesX = 20;
MaxTilesY = 12;

LevelMan:setSize(MaxTilesX,MaxTilesY,2);

local entityList = List:new();

function main ( )
	startup();
	mainLoop();
	quit();
end

function startup( )
	Renderer:createWindow(WindowName,WindowWidth,WindowHeight,WindowBPP);
	loadMoon("Chronos");
	Player = PlayerClass.create(150, 100, 0);
	addEntity( 320, 50, "SinLeft", 32, 16, 0.2, os.clock() );
	addEntity( -16, 50, "SinRight", 48, 16, 0.2, os.clock() );

end

function mainLoop( )
	local running = true;
	local counter = 100;
	while running == true do
		running = Interpret:isRunning();

		LevelMan:render(0, 0, 0, 20, 12, -16, -16);
		LevelMan:render(1, 0, 0, 20, 12, -16, -16);
		updateBullets();
		updateEntities();
		Player:update();
		Interpret:update();
		counter = counter - 0.5;

		if counter < 0 then
			counter = 50;
			addEntity( 300, 150, "DropUpLeft", 48, 16, 0.2, os.clock() );
		end
	end
end

function addEntity( pX, pY, pPath, pU, pV, pSpeed, pTime )
	entityList:append({x = pX, y = pY, path = pPath, u = pU, v = pV, w = 16, h = 16, speed = pSpeed, time = pTime });
end

function updateEntities()
	for i,entity in ipairs(entityList) do
		TextureMan:blitTexture("LevelData", entity.x, entity.y, 0, entity.u, entity.v, entity.w, entity.h);
		if entity.path == "Left" then
			entity.x = entity.x - entity.speed;
		elseif entity.path == "Right" then
			entity.x = entity.x + entity.speed;
		elseif entity.path == "SinLeft" then
			entity.x = entity.x - entity.speed;
			entity.y = entity.y + math.sin(entity.speed * entity.time);
			entity.time = entity.time + 0.1;
		elseif entity.path == "SinRight" then
			entity.x = entity.x + entity.speed;
			entity.y = entity.y + math.sin(entity.speed * entity.time);
			entity.time = entity.time + 0.1;
		elseif entity.path == "DropDownLeft" then
			entity.x = entity.x - (entity.speed * entity.time);
			entity.y = entity.y + (math.atan2(entity.x, entity.y) * entity.speed);
			entity.time = entity.time + 0.001;
		elseif entity.path == "DropDownRight" then
			entity.x = entity.x + (entity.speed * entity.time);
			entity.y = entity.y + (math.atan2(entity.x, entity.y) * entity.speed);
			entity.time = entity.time + 0.001;
		elseif entity.path == "DropUpLeft" then
			entity.x = entity.x - (entity.speed * entity.time);
			entity.y = entity.y - (math.atan2(entity.x, entity.y) * entity.speed);
			entity.time = entity.time + 0.001;
		elseif entity.path == "DropUpRight" then
			entity.x = entity.x + (entity.speed * entity.time);
			entity.y = entity.y - (math.atan2(entity.x, entity.y) * entity.speed);
			entity.time = entity.time + 0.001;
		elseif entity.path == "Explosion" then
			entity.time = entity.time - 1.0;
			if entity.time < 0 then
				entityList:remove(entity);
			end
		end

		if entity.x < -32 or entity.x > 336 then
			entityList:remove(entity);
		end

		if checkAgainstBullets( entity.x, entity.y ) == true then
			entityList:remove(entity);
		end
	end
end


function quit ( )
	Renderer:createWindow("Shutting Down...",WindowWidth,WindowHeight,WindowBPP);
	Interpret:quit();
end
