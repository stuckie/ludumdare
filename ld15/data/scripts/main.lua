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

entityList = List:new();

shakiness = 1;
gamePaused = false;

function main ( )
	startup();
	mainLoop();
	quit();
end

function startup( )
	Renderer:createWindow(WindowName,WindowWidth,WindowHeight,WindowBPP);
	AudioMan:loadSFX("BigExplosion", "data/sfx/BigExplosion.wav");
	AudioMan:loadSFX("Explosion", "data/sfx/Explosion.wav");
	AudioMan:loadSFX("Fire", "data/sfx/Fire.wav");
	AudioMan:loadSFX("Health", "data/sfx/Health.wav");
	AudioMan:loadSFX("BeamUp", "data/sfx/BeamUp.wav");
	--Renderer:setFullscreen(true);
	TextureMan:addTexture("Font", "data/gfx/font.bmp");
	loadMoon("Chronos"); -- Chronos, Kala, Shiva, Thoth, Wenut
	Player = PlayerClass.create(3*16, 8*16, 0);
	Player.lastBaseRoom = { x = 0, y = 0 };
	Player.lastBasePosition = { x = 3*16, y = 8*16 };
end

function mainLoop( )
	local running = true;
	while running == true do
		running = Interpret:isRunning();

		if currentTime > 0 then
			if gamePaused == false then
				LevelMan:render(0, 0, 0, 20, 12, -16, -16);
				LevelMan:render(1, 0, 0, 20, 12, -16 + (math.random() * shakiness), -16 + (math.random() * shakiness));
				--displayText(240, 230, "Room: " .. Player.moonPosition.y .. "," .. Player.moonPosition.x);
				updateMoon();
				updateBullets();
				updateEntities();
				Player:update();
				currentTime = currentTime - 0.01;
			else
				LevelMan:render(0, 0, 0, 20, 12, -16, -16);
				LevelMan:render(1, 0, 0, 20, 12, -16, -16);
				Player:checkInput();
				displayText(120, 80, "=PAUSED!=");
			end
				displayStats();
				Interpret:update();
			
		else
			gamePaused = false;
			Player.lives = Player.lives - 1;
			while gamePaused == false do
				Player:checkInput();
				Renderer:updateScreen();
				ControlMan:updateControls();
				displayText(10, 110, "The Moon's Exploded - with YOU on it!!");
				if Player.lives > 0 then
					displayText(50, 210, "Press PAUSE to Restart Sector.");
				else
					displayText(120, 80, "GAME OVER");
					displayText(100, 70, "No Lives Left!");
					displayText(50, 170, "Final Score: " .. string.format("%.0f",Player.score));
					displayText(50, 210, "Press PAUSE to Quit Game.");
				end
			end
			gamePaused = false;
			if Player.lives > 0 then
				Player.position = { x = 3*16, y = 8*16 };
				Player.moonPosition = { x=0, y=0 };
				loadLevel(currentLevel);
				renderRoom(0,0);
			else
				Interpret:quit();
			end
			
		end	

	end
end

function displayStats()
	if currentTime < 75 then
		shakiness = shakiness + 0.0001;
	end
	if totalResearchers == 0 and Player.cargo == 0 then
		displayText(100, 110, "Get Off The Moon!");
	end
	displayText(0, 195, "Moon: " .. currentMoon);
	displayText(0, 205, "Sector: " .. currentLevel);
	displayText(0, 220, "Shield: " .. string.format("%.2f",Player.health));
	displayText(0, 230, "Score: " .. string.format("%.0f",Player.score));
	displayText(216, 195, "Time: " .. string.format("%.2f",currentTime));
	displayText(160, 205, "Researchers: " .. Player.researchersSaved .. "/" .. Player.cargo .. "/" .. totalResearchers);
end

function addEntity( pX, pY, pPath, pU, pV, pSpeed, pHealth, pScore, pTime )
	local pPosition = { x = pX, y = pY };
	local pVelocity = { x = 0, y = 0 };
	local pMaxVelocity = 5.0;
	entityList:append({position = pPosition, velocity = pVelocity, path = pPath, u = pU, v = pV, w = 16, h = 16, speed = pSpeed, health = pHealth, score = pScore, time = pTime, maxVelocity = pMaxVelocity });
end

function updateEntities()
	for i,entity in ipairs(entityList) do
		TextureMan:blitTexture("LevelData", entity.position.x, entity.position.y, 0, entity.u, entity.v, entity.w, entity.h);
		if entity.path == "Left" then
			entity.velocity.x = entity.velocity.x - entity.speed;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "Right" then
			entity.velocity.x = entity.velocity.x + entity.speed;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "Up" then
			entity.velocity.y = entity.velocity.y - entity.speed;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "Down" then
			entity.velocity.y = entity.velocity.y + entity.speed;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "SinLeft" then
			entity.velocity.x = entity.velocity.x - entity.speed;
			entity.position.y = entity.position.y - math.sin(entity.speed * entity.time);
			entity.time = entity.time + 0.1;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "SinRight" then
			entity.velocity.x = entity.velocity.x + entity.speed;
			entity.position.y = entity.position.y - math.sin(entity.speed * entity.time);
			entity.time = entity.time + 0.1;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "DropDownLeft" then
			entity.velocity.x = entity.velocity.x - (entity.speed * entity.time);
			entity.position.y = entity.position.y + (math.atan2(entity.position.x, entity.position.y) * entity.speed);
			entity.time = entity.time + 0.001;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "DropDownRight" then
			entity.velocity.x = entity.velocity.x + (entity.speed * entity.time);
			entity.position.y = entity.position.y + (math.atan2(entity.position.x, entity.position.y) * entity.speed);
			entity.time = entity.time + 0.001;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "DropUpLeft" then
			entity.velocity.x = entity.velocity.x - (entity.speed * entity.time);
			entity.position.y = entity.position.y - (math.atan2(entity.position.x , entity.position.y) * entity.speed);
			entity.time = entity.time + 0.001;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "DropUpRight" then
			entity.velocity.x = entity.velocity.x + (entity.speed * entity.time);
			entity.position.y = entity.position.y - (math.atan2(entity.position.x, entity.position.y) * entity.speed);
			entity.time = entity.time + 0.001;
			if checkEntityAgainstTile(entity.position) == true then
				entityList:remove(entity);
				break;
			end
		elseif entity.path == "ShootRight" then
			entity.time = entity.time - 0.1;
			if entity.time < 0 then
				entity.time = entity.speed;
				addBullet ( entity.position.x, entity.position.y, "Right", "Enemy" );
			end
		elseif entity.path == "Explosion" then
			entity.time = entity.time - 1.0;
			if entity.time < 0 then
				entityList:remove(entity);
				break;
			end
			return;
		end

		if entity.velocity.x > entity.maxVelocity then
			entity.velocity.x = entity.maxVelocity;
		elseif entity.velocity.x < -entity.maxVelocity then
			entity.velocity.x = - entity.maxVelocity;
		elseif entity.velocity.y > entity.maxVelocity then
			entity.velocity.y = entity.maxVelocity;
		elseif entity.velocity.y < -entity.maxVelocity then
			entity.velocity.y = - entity.maxVelocity;
		end

		if entity.position.x < -32 or entity.position.x > 336 then
			entityList:remove(entity);
			break;
		end

		if checkAgainstBullets( entity.position.x, entity.position.y, 16, 16 ) == true then
			entity.health = entity.health - 2.0;
		end

		if checkAgainstPlayer( entity.position.x, entity.position.y, 16, 16 ) == true then
			Player.health = Player.health - 5.0;
			Player.velocity.x = Player.velocity.x + entity.velocity.x;
			Player.velocity.y = Player.velocity.y + entity.velocity.y;
			addEntity( entity.position.x, entity.position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
			AudioMan:playSFX("Explosion");
			entityList:remove(entity);
			break;
		end

		if entity.health < 0 then
			Player.score = Player.score + entity.score;
			addEntity( entity.position.x, entity.position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
			entityList:remove(entity);
			break;
		end

		entity.position.x = entity.position.x + entity.velocity.x;
		entity.position.y = entity.position.y + entity.velocity.y;
	end
end

function checkEntityAgainstTile( position )
	local aboveTile = LevelMan:getTileType( (position.x + 8 )/ 16, (position.y / 16 ), 1 );
	local belowTile = LevelMan:getTileType( (position.x + 8)/ 16, (position.y / 16 ) + 1, 1 );
	local leftTile = LevelMan:getTileType( position.x / 16, position.y / 16, 1 );
	local rightTile = LevelMan:getTileType( (position.x / 16) + 1, position.y / 16, 1 );
	
	if belowTile == "Solid" or belowTile == "ResearchLand" or belowTile == "ResearchLeft" or belowTile == "ResearchMid"  or belowTile == "ResearchRight" or belowTile == "Invis" then
		addEntity( position.x, position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
		return true;
	end
	if aboveTile == "Solid" or aboveTile == "ResearchLand" or aboveTile == "ResearchLeft" or aboveTile == "ResearchMid"  or aboveTile == "ResearchRight" or aboveTile == "Invis" then
		addEntity( position.x, position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
		return true;
	end
	if rightTile == "Solid" or rightTile == "ResearchLand" or rightTile == "ResearchLeft" or rightTile == "ResearchMid"  or rightTile == "ResearchRight" or rightTile == "Invis" then
		addEntity( position.x, position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
		return true;
	end
	if leftTile == "Solid" or leftTile == "ResearchLand" or leftTile == "ResearchLeft" or leftTile == "ResearchMid"  or leftTile == "ResearchRight" or leftTile == "Invis" then
		addEntity( position.x, position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
		return true;
	end

	return false;
end

function displayText( x, y, text )
	local textX = x;
	local textY = y;
	for c in text:gmatch"." do
		TextureMan:blitTexture("Font",textX, textY, 0, 0, (string.byte(c) - 33) * 8, 8, 8);
		textX = textX + 8;
	end

end

function finishedGame()
	gamePaused = false;
	while gamePaused == false do
		Player:checkInput();
		Renderer:updateScreen();
		ControlMan:updateControls();
		displayText(50, 110, "You've finished the game!");
		displayText(50, 120, "Wasn't it all worth it?!?");
		displayText(50, 130, "For this crappy screen ;)");
		displayText(120, 80, "WELL DONE");
		displayText(50, 170, "Final Score: " .. string.format("%.0f",Player.score));
		displayText(50, 210, "Press PAUSE to Quit Game.");
		Player.position.x = -16;
		Player.position.y = -16;
		EntityMan:moveTo("Player", -16, -16, 0);
	end
	loadMoon("Chronos");
	Interpret:quit();
end

function quit ( )
	--Renderer:setFullscreen(false);
	Renderer:createWindow("Shutting Down...",WindowWidth,WindowHeight,WindowBPP);
	Interpret:quit();
end
