-- Player Controlling Thingumajig
-- Let's make it a class! cause I can.. and it's gonna have it's own data and stuff.. STUFF!!!!
-- perhaps coding late into the night is a bad thing
-- and who reads the source to LD entries anyway?
-- it's Christmas for Christ's sake!
-- go feast on a chicken
-- gobble gobble gobble ... no wait that's turkey.. cock-a-doodle-doooooooooooooooo

PlayerClass = {};
PlayerClass.__index = PlayerClass;

BLIP_NONE = 0;
BLIP_UNSEEN = 1;
BLIP_SEEN = 2; -- in which case, grab the sprite from the master entities list.

LOS_UNEXPLORED = 0;
LOS_EXPLORED = 1;
LOS_VISIBLE = 2;

COMMAND_MOVE = 0;
COMMAND_FIRE = 1;
COMMAND_DOOR = 2;
COMMAND_SKILL1 = 3;
COMMAND_SKILL2 = 4;

function PlayerClass.create( name, type, faction )
	local player = {};
	setmetatable(player, PlayerClass);

	player.name = name;			-- err, just have it PLAYER_ONE, etc..
	player.type = type;			-- Human or AI (hah)
	player.faction = faction;	-- Human or Alien

	player.unitList = List:new();

	player.lineOfSight = {};
	player.blips = {};

	player.currentUnit = 1;

	player.actionX = 0;
	player.actionY = 0;

	player.turn = 0;

	player.command = COMMAND_MOVE;

	for z=0,derelictFloorDepth do
		player.lineOfSight[z] = {};
		player.blips[z] = {};
		for y=0,derelictRoomHeight * derelictFloorHeight do
			player.lineOfSight[z][y] = {};
			player.blips[z][y] = {};
			for x=0,derelictRoomWidth * derelictFloorWidth do
				player.blips[z][y][x] = BLIP_NONE;
				player.lineOfSight[z][y][x] = LOS_UNEXPLORED;
			end
		end
	end

	return player;
end

function PlayerClass:addUnit(class)
	if class == CLASS_ENGINEER then
		local newUnit = HumanEngineerClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_MEDIC then
		local newUnit = HumanMedicClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_SOLDIER then
		local newUnit = HumanSoldierClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_COMMS then
		local newUnit = HumanCommsClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_SCOUT then
		local newUnit = HumanScoutClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_HEAVY then
		local newUnit = HumanHeavyClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_CYBORG then
		local newUnit = AlienCyborgClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_VIRUS then
		local newUnit = AlienVirusClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_GHOST then
		local newUnit = AlienGhostClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_GRUNT then
		local newUnit = AlienGruntClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_SIREN then
		local newUnit = AlienSirenClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_BLITZER then
		local newUnit = AlienBlitzerClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_ALIEN_QUEEN then
		local newUnit = AlienQueenClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_ALIEN_BROOD then
		local newUnit = AlienBroodClass.create(self.type);
		self.unitList:append(newUnit);

	elseif class == CLASS_TURRET then
		local newUnit = TurretClass.create(self.type);
		self.unitList:append(newUnit);

	end
end

function PlayerClass:getUnitAmount()
	return self.unitList:len();
end

function PlayerClass:getUnit(number)
	return self.unitList[number];
end

function PlayerClass:resetLOS()
	for z=0,derelictFloorDepth do
		for y=0,derelictRoomHeight * derelictFloorHeight do
			for x=0,derelictRoomWidth * derelictFloorWidth do
				if self.lineOfSight[z][y][x] == LOS_VISIBLE then
					self.lineOfSight[z][y][x] = LOS_EXPLORED;
				end
			end
		end
	end
	for z=0,derelictFloorDepth do
		for y=0,derelictRoomHeight * derelictFloorHeight do
			for x=0,derelictRoomWidth * derelictFloorWidth do
				if self.blips[z][y][x] == BLIP_SEEN then
					self.blips[z][y][x] = BLIP_UNSEEN;
				end
			end
		end
	end
end

local debounce = false;
function PlayerClass:controlUnit()
	if self.type == PLAYER_AI then
		if ControlMan:getSTART() == true then
			-- turn over
			if ACTIVE_PLAYER < MAX_PLAYERS - 1 then
				ACTIVE_PLAYER = ACTIVE_PLAYER + 1;
			else
				ACTIVE_PLAYER = 0;
			end
			setMenu(CHANGE_PLAYER);
			changeState(FRONT_STATE);
			return;
		end
		return;
	end

	local unit = self.unitList[self.currentUnit];

	if self.command == COMMAND_MOVE then
		if ControlMan:getRight() == true and debounce == true then
			debounce = false;
			unit:moveRight();
		elseif ControlMan:getLeft() == true and debounce == true then
			debounce = false;
			unit:moveLeft();
		elseif ControlMan:getUp() == true and debounce == true then
			debounce = false;
			unit:moveUp();
		elseif ControlMan:getDown() == true and debounce == true then
			debounce = false;
			unit:moveDown();
		elseif ControlMan:getSTART() == true and debounce == true then
			debounce = false;
			if derelictShipTiles[unit.z][unit.y][unit.x].tileCode == "8" then
				unit:floorUp();
			elseif derelictShipTiles[unit.z][unit.y][unit.x].tileCode == "9" then
				unit:floorDown();
			end
		elseif ControlMan:getLeft() == false and ControlMan:getRight() == false
			and ControlMan:getUp() == false and ControlMan:getDown() == false
			and ControlMan:getSTART() == false and debounce == false then
				debounce = true;
		end
	
	gameCamera.x = unit.x - 10;
	gameCamera.y = unit.y - 7;
	gameCamera.z = unit.z;

	self.actionX = unit.x;
	self.actionY = unit.y;

	elseif self.command == COMMAND_FIRE then
		if ControlMan:getRight() == true and debounce == true then
			debounce = false;
			self:actionRight();
		elseif ControlMan:getLeft() == true and debounce == true then
			debounce = false;
			self:actionLeft();
		elseif ControlMan:getUp() == true and debounce == true then
			debounce = false;
			self:actionUp();
		elseif ControlMan:getDown() == true and debounce == true then
			debounce = false;
			self:actionDown();
		elseif ControlMan:getSTART() == true and debounce == true then
			debounce = false
			unit:fire(self.actionX, self.actionY, unit.z);
		elseif ControlMan:getLeft() == false and ControlMan:getRight() == false
			and ControlMan:getUp() == false and ControlMan:getDown() == false
			and ControlMan:getSTART() == false and debounce == false then
				debounce = true;
		end
	elseif self.command == COMMAND_DOOR then
		if ControlMan:getRight() == true and debounce == true then
			debounce = false;
			self:actionRight();
		elseif ControlMan:getLeft() == true and debounce == true then
			debounce = false;
			self:actionLeft();
		elseif ControlMan:getUp() == true and debounce == true then
			debounce = false;
			self:actionUp();
		elseif ControlMan:getDown() == true and debounce == true then
			debounce = false;
			self:actionDown();
		elseif ControlMan:getSTART() == true and debounce == true then
			debounce = false
			unit:door(self.actionX, self.actionY, unit.z);
		elseif ControlMan:getLeft() == false and ControlMan:getRight() == false
			and ControlMan:getUp() == false and ControlMan:getDown() == false
			and ControlMan:getSTART() == false and debounce == false then
				debounce = true;
		end
	elseif self.command == COMMAND_SKILL1 then
		if ControlMan:getRight() == true and debounce == true then
			debounce = false;
			self:actionRight();
		elseif ControlMan:getLeft() == true and debounce == true then
			debounce = false;
			self:actionLeft();
		elseif ControlMan:getUp() == true and debounce == true then
			debounce = false;
			self:actionUp();
		elseif ControlMan:getDown() == true and debounce == true then
			debounce = false;
			self:actionDown();
		elseif ControlMan:getSTART() == true and debounce == true then
			debounce = false
			unit:skill1(self.actionX, self.actionY, unit.z);
		elseif ControlMan:getLeft() == false and ControlMan:getRight() == false
			and ControlMan:getUp() == false and ControlMan:getDown() == false
			and ControlMan:getSTART() == false and debounce == false then
				debounce = true;
		end
	elseif self.command == COMMAND_SKILL2 then
		if ControlMan:getRight() == true and debounce == true then
			debounce = false;
			self:actionRight();
		elseif ControlMan:getLeft() == true and debounce == true then
			debounce = false;
			self:actionLeft();
		elseif ControlMan:getUp() == true and debounce == true then
			debounce = false;
			self:actionUp();
		elseif ControlMan:getDown() == true and debounce == true then
			debounce = false;
			self:actionDown();
		elseif ControlMan:getSTART() == true and debounce == true then
			debounce = false
			unit:skill2(self.actionX, self.actionY, unit.z);
		elseif ControlMan:getLeft() == false and ControlMan:getRight() == false
			and ControlMan:getUp() == false and ControlMan:getDown() == false
			and ControlMan:getSTART() == false and debounce == false then
				debounce = true;
		end
	end

	if ControlMan:getA() == true then
		hudDisplayCommand(COMMAND_MOVE);
		self.command = COMMAND_MOVE;
		self.actionX = unit.x;
		self.actionY = unit.y;
	elseif ControlMan:getS() == true then
		hudDisplayCommand(COMMAND_FIRE);
		self.command = COMMAND_FIRE;
		self.actionX = unit.x;
		self.actionY = unit.y;
	elseif ControlMan:getD() == true then
		hudDisplayCommand(COMMAND_DOOR);
		self.command = COMMAND_DOOR;
		self.actionX = unit.x;
		self.actionY = unit.y;
	elseif ControlMan:getQ() == true then
		hudDisplayCommand(COMMAND_SKILL1);
		self.command = COMMAND_SKILL1;
		self.actionX = unit.x;
		self.actionY = unit.y;
	elseif ControlMan:getE() == true then
		hudDisplayCommand(COMMAND_SKILL2);
		self.command = COMMAND_SKILL2;
		self.actionX = unit.x;
		self.actionY = unit.y;
	end

	if ControlMan:get1() == true and hudElementExists("Unit1") == false then
			addHudElement("Unit1", self.unitList[1], 100, 320);
	elseif ControlMan:get2() == true and hudElementExists("Unit2") == false then
			addHudElement("Unit2", self.unitList[2], 200, 320);
	elseif ControlMan:get3() == true and hudElementExists("Unit3") == false then
			addHudElement("Unit3", self.unitList[3], 300, 320);
	elseif ControlMan:get4() == true and hudElementExists("Unit4") == false then
			addHudElement("Unit4", self.unitList[4], 400, 320);
	elseif ControlMan:get1() == true and hudElementExists("Unit1") == true then
			removeHudElement("Unit1");
	elseif ControlMan:get2() == true and hudElementExists("Unit2") == true then
			removeHudElement("Unit2");
	elseif ControlMan:get3() == true and hudElementExists("Unit3") == true then
			removeHudElement("Unit3");
	elseif ControlMan:get4() == true and hudElementExists("Unit4") == true then
			removeHudElement("Unit4");
	end

	if unit.ap == 0 then
		if self.currentUnit == self.unitList:len() then
			-- turn over
			if ACTIVE_PLAYER < MAX_PLAYERS - 1 then
				ACTIVE_PLAYER = ACTIVE_PLAYER + 1;
			else
				ACTIVE_PLAYER = 0;
			end
			setMenu(CHANGE_PLAYER);
			changeState(FRONT_STATE);
			return;
		else
			self.currentUnit = self.currentUnit + 1;
		end
	end

end

function PlayerClass:renderAction()
	if self.command ~= COMMAND_MOVE then
		TextureMan:blitTexture("tileData", self.actionX * 32 - gameCamera.x * 32, self.actionY * 32 - gameCamera.y * 32, 0, 64, 224, 32, 32);
	else
		TextureMan:blitTexture("tileData", self.actionX * 32 - gameCamera.x * 32, self.actionY * 32 - gameCamera.y * 32, 0, 64, 192, 32, 32);
	end
end

function PlayerClass:actionLeft()
	self.actionX = self.actionX - 1;
end

function PlayerClass:actionRight()
	self.actionX = self.actionX + 1;
end

function PlayerClass:actionUp()
	self.actionY = self.actionY - 1;
end

function PlayerClass:actionDown()
	self.actionY = self.actionY + 1;
end

function PlayerClass:resetUnits()
	for i=1, self.unitList:len() do
		local unit = self.unitList[i];
		unit.ap = unit.apMax;
		unit.moved = 0;
	end
	self.currentUnit = 1;
end

function PlayerClass:blip(x, y, z)
	player.blips[z][y][x] = BLIP_SEEN;
end