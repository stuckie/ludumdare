
currentMoon = "Chronos";
currentLevel = "01";
currentRoom = "00";
currentTime = 999;

local moonData = {};
local levelData = {};

function unloadMoon()
	TextureMan:delTexture("LevelData");

	levelData = {};
	moonData = {};
end

function loadMoon( moonToLoad )
	currentMoon = moonToLoad;
	TextureMan:addTexture("LevelData", "data/gfx/" .. currentMoon .. ".bmp");
	dofile("data/levels/" .. currentMoon .. ".lua");

	currentLevel = "01";
	loadLevel( currentLevel );
	renderRoom( 0, 0 );
end

function loadLevel( levelToLoad )
	currentLevel = levelToLoad;
	local inputFile = assert(io.open("data/levels/" .. currentMoon .. "/" .. currentLevel .. ".moon" , "r"))
	currentTime = inputFile:read("*number");
	local fileData = inputFile:read("*all");
	inputFile:close();

	moonData = {};
	for y=0,moonHeight do
		moonData[y] = {};
		for x=0,moonWidth do
			moonData[y][x] = 0;
		end
	end

	levelData = {};
	for y=0,moonHeight do
		levelData[y] = {};
		for x=0,moonWidth do
			levelData[y][x] = 0;
		end
	end

	local y = 0;
	local x = 0;

	for roomNumber in fileData:gmatch"%d%d" do
		moonData[y][x] = roomNumber;
		levelData[y][x] = loadRoom(moonData[y][x]);
		x = x + 1;
		if x == moonWidth then
			x = 0;
			y = y + 1;
		end
		if y > moonHeight then
			-- file is too big!
			print("OOPS!");
			assert();
		end
	end

	_G["setupMoon" .. currentLevel]();

end

function loadRoom( roomToLoad )
	local inputFile = assert(io.open("data/levels/" .. currentMoon .. "/" .. roomToLoad .. ".cave" , "r"))
	local fileData = inputFile:read("*all")
	inputFile:close()

	local roomData = {};
	for y=0,roomHeight - 1 do
		roomData[y] = {};
		for x=0,roomWidth - 1 do
			roomData[y][x] = 0;
		end
	end

	local y = 0;
	local x = 0;

	for roomNumber in fileData:gmatch"%w" do
		roomData[y][x] = roomNumber;
		x = x + 1;
		if x == roomWidth then
			x = 0;
			y = y + 1;
		end
		if y > roomHeight then
			-- file is too big!
			print("OOPS!");
			assert();
		end
	end

	return roomData;
end

function renderRoom( roomX, roomY )
	entityList:clear();
	bulletList:clear();
	for y=0,roomHeight -1 do
		for x=0,roomWidth -1 do
			if roomX == 0 and roomY == 0 then
				createTile("Sky", x, y, 0);
			else
				createTile("CavernBack", x, y, 0);
			end

			if levelData[roomY][roomX][y][x] == "1" then
				createTile("Solid", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "T" then
				createTile("ResearchLand", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "F" then
				createTile("ResearchLeft", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "H" then
				createTile("ResearchRight", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "G" then
				createTile("ResearchMid", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "8" then
				createTile("CavernBack", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "X" then
				createTile("Sky", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "x" then
				createTile("LeaveSky", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "R" then
				createTile("LeaveRight", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "L" then
				createTile("LeaveLeft", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "U" then
				createTile("LeaveUp", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "D" then
				createTile("LeaveDown", x, y, 1);
			elseif levelData[roomY][roomX][y][x] == "A" then
				createTile("Invis", x, y, 1);
			end
		end
	end
end

local WallNum = 0;

function createTile ( WallType, x, y, z )
	WallNum = WallNum + 1;
	local WallTex = 0;
	local CurrentEntity = "Wall." .. WallType .. "." .. WallNum;

	if WallType == "Solid" then WallTex = 0; end
	if WallType == "ResearchLand" then WallTex = 16; end
	if WallType == "ResearchLeft" then WallTex = 32; end
	if WallType == "ResearchMid" then WallTex = 48; end
	if WallType == "ResearchRight" then WallTex = 64; end
	if WallType == "CavernBack" then WallTex = 80; end
	if WallType == "Sky" then WallTex = 96; end
	
	if WallType == "LeaveSky" then WallTex = 96; end
	if WallType == "LeaveUp" then WallTex = 80; end
	if WallType == "LeaveLeft" then WallTex = 80; end
	if WallType == "LeaveRight" then WallTex = 80; end
	if WallType == "LeaveDown" then WallTex = 80; end

	if WallType == "Invis" then WallTex = 240; end
	
	LevelMan:addTile(CurrentEntity, WallType, x, y, z);
	LevelMan:texTile(CurrentEntity, "LevelData", "LevelData", 240, WallTex, 16, 16, 255, 0, 255);
	
end

function updateMoon()
	_G["moon" .. currentLevel]();
end

function updateEnemyBases( enemyBases )
	if enemyBases:len() > 0 then
		for i,enemyBase in ipairs(enemyBases) do
			if enemyBase.baseHealth > 0 then
				enemyBase.baseCounter = enemyBase.baseCounter - 1;
				if enemyBase.baseCounter == 0 then
					enemyBase.baseCounter = enemyBase.baseRespawn;
					addEntity( enemyBase.basePosition.x + enemyBase.offsetX, 
						enemyBase.basePosition.y + enemyBase.offsetY, 
						enemyBase.baseEnemy.path, enemyBase.baseEnemy.u, enemyBase.baseEnemy.v, 
						enemyBase.baseEnemy.speed, enemyBase.baseEnemy.health, enemyBase.baseEnemy.score, 
						enemyBase.baseEnemy.time );
				end
				if checkAgainstBullets(enemyBase.basePosition.x, enemyBase.basePosition.y, 16, 32) == true then
					enemyBase.baseHealth = enemyBase.baseHealth - 2.0;
					if enemyBase.baseHealth <= 0 then
						Player.score = Player.score + 1000;
						AudioMan:playSFX("BigExplosion");
					end
				end
				TextureMan:blitTexture("LevelData", enemyBase.basePosition.x, enemyBase.basePosition.y, 0, enemyBase.aliveU, enemyBase.aliveV, enemyBase.width, enemyBase.height);
				if checkAgainstPlayer( enemyBase.basePosition.x, enemyBase.basePosition.y, 16, 16 ) == true then
					Player.health = Player.health - 10.0;
					Player.velocity.x = -Player.velocity.x;
					Player.velocity.y = -Player.velocity.y;
					addEntity( enemyBase.basePosition.x, enemyBase.basePosition.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
				end
			else
				TextureMan:blitTexture("LevelData", enemyBase.basePosition.x, enemyBase.basePosition.y, 0, enemyBase.deadU, enemyBase.deadV, 32, 32);
			end
		end
	end
end

function updateResearchBases( researchBase )
	if researchBase ~= nil then
		if researchBase.researchers > 0 then
			TextureMan:blitTexture("LevelData", researchBase.position.x, researchBase.position.y, 0, researchBase.activeU, researchBase.activeV, 16, 16);
		else
			TextureMan:blitTexture("LevelData", researchBase.position.x, researchBase.position.y, 0, researchBase.inactiveU, researchBase.inactiveV, 16, 16);
		end
		if checkAgainstPlayer( researchBase.position.x, researchBase.position.y, 16, 16 ) == true then
			if Player.velocity.y > Player.speed then
				Player.velocity.x = -Player.velocity.x;
				Player.velocity.y = -Player.velocity.y/2;
			else
				Player.velocity.x = -Player.velocity.x;
				Player.velocity.y = -(moonGravity + Player.speed);
				if researchBase.researchers > 0 then
					if Player.health < 100 then
						AudioMan:playSFX("Health");
						Player.health = Player.health + 0.1;
					end
				end
				Player.landed = true;
				Player.lastBaseRoom = researchBase.room;
				Player.lastBasePosition.x = researchBase.position.x;
				Player.lastBasePosition.y = researchBase.position.y - 16;
			end
		else
			Player.landed = false;
		end
	end
end

function transferResearchers( amount, to )
	if to == "Player" then
		local currentBase = getResearchBase(Player.moonPosition.x, Player.moonPosition.y);
		if currentBase == nil then return; end
		if currentBase.researchers > 0 then
			currentBase.researchers = currentBase.researchers - amount;
			totalResearchers = totalResearchers - amount;
			Player.cargo = Player.cargo + 1;
			AudioMan:playSFX("BeamUp");
		end
	elseif to == "Base" then
		if Player.moonPosition.x == 0 and Player.moonPosition.y == 0 then
			if Player.cargo > 0 then
				Player.cargo = Player.cargo - amount;
				Player.researchersSaved = Player.researchersSaved + amount;
				AudioMan:playSFX("BeamUp");
				return;
			end
		end
		local currentBase = getResearchBase(Player.moonPosition.x, Player.moonPosition.y);
		if currentBase == nil then return; end
		if Player.cargo > 0 then
			currentBase.researchers = currentBase.researchers + amount;
			totalResearchers = totalResearchers + amount;
			Player.cargo = Player.cargo - amount;
			AudioMan:playSFX("BeamUp");
		end
	end
end

function nextLevel()
	if currentLevel == "05" then
		nextMoon();
	elseif currentLevel == "04" then
		loadLevel("05");
	elseif currentLevel == "03" then
		loadLevel("04");
	elseif currentLevel == "02" then
		loadLevel("03");
	elseif currentLevel == "01" then
		loadLevel("02");
	end
	
	Player.lastBaseRoom = { x = 0, y = 0 };
	Player.lastBasePosition = { x = 3*16, y = 8*16 };
	Player.position = Player.lastBasePosition;
	Player.cargo = 0;
	Player.researchersSaved = Player.researchersSaved + 1;
	Player.score = Player.score + Player.health + ( 1000 * Player.researchersSaved );
	Player.researchersSaved = 0;
	Player.velocity.x = 0;
	Player.velocity.y = 0;
	shakiness = 1;
end

function nextMoon()
	unloadMoon();
	if currentMoon == "Chronos" then
		loadMoon("Kala");
		return;
	elseif currentMoon == "Kala" then
		loadMoon("Shiva");
		return;
	elseif currentMoon == "Shiva" then
		loadMoon("Thoth");
		return;
	elseif currentMoon == "Thoth" then
		loadMoon("Wenut");
		return;
	else
		finishedGame();
	end
end