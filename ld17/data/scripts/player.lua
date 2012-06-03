-- Player Class.. events should be passed here, really

dofile("data/scripts/pirateship.lua");
dofile("data/scripts/piratemen.lua");
dofile("data/scripts/fort.lua");

PlayerClass = {};
PlayerClass.__index = PlayerClass;

local COMMAND_MOVE = 0;
local COMMAND_ATTACK = 1;
local COMMAND_DOCK = 2;
local COMMAND_PILLAGE = 3;

function PlayerClass.create( name, type, beard )
	local player = {};
	setmetatable(player, PlayerClass);

	player.name = name;
	player.type = type;				-- local or networked, or AI
	player.beard = beard;			-- Red, Blue, Pink, Green, Grey, Black

	player.unitList = List:new();	-- copy of internal units for quick access

	player.currentUnit = nil;

	player.captain = { u = 0, v = 192 };
	player.pirate = { u = 64, v = 192 };
	player.flag = { u = 0, v = 128 };
	player.fort = { u = 128, v = 192 };
	player.selected = { u = 192, v = 192 };

	player.command = COMMAND_MOVE;

	return player;
end

function PlayerClass:addUnit(type, x, y)
	local newUnit = addUnit(self, type);
	newUnit.x = x;
	newUnit.y = y;
	self.unitList:append(newUnit);
	return newUnit;
end

function PlayerClass:getUnitAmount()
	return self.unitList:len();
end

function PlayerClass:getUnit(number)
	return getUnit(number);
end

function PlayerClass:removeUnit(unit)
	self.unitList:remove(unit);
end

function PlayerClass:takeUnit(unit)
	self.unitList:append(unit)
	unit.owner = self;
end

function PlayerClass:selectUnit()
	for i,unit in ipairs(self.unitList) do
		if calcDistanceXY(unit.x + 32, unit.y + 32,(MOUSE_X) + (gameCamera.x * 64), (MOUSE_Y) + (gameCamera.y * 64)) < 32 then
			self.currentUnit = unit;
			unit.selected = true;
		end
	end
end


function PlayerClass:update()
	for i,unit in ipairs(self.unitList) do
		unit:update();
		unit:render();
		if self.type == "AI" then
			if unit.type ~= "Pirate Fort" then
				-- effectively randomly move things around, unless something's within reach, then go and attack it.
				for i,enemy in ipairs(globalUnitList) do
					if enemy.type ~= "Pirate Fort" and enemy.owner.beard ~= "Neutral" then
						if calcDistanceXY(unit.x, unit.y, enemy.x, enemy.y) < 500 then
							unit:attack(enemy);
							break;
						elseif calcDistanceXY(unit.x, unit.y, enemy.x, enemy.y) < 1000 then
							unit:moveTo(enemy.x, enemy.y);
							break;
						end
					end
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