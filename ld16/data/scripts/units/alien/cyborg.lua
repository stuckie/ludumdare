-- Alien Cyborg

AlienCyborgClass = {};
AlienCyborgClass.__index = AlienCyborgClass;

function AlienCyborgClass.create( type )
	local unit = {};
	setmetatable(unit, AlienCyborgClass);

	unit.type = type;			-- Human or AI (hah)
	unit.class = CLASS_CYBORG;

	unit.hp = 30;
	unit.sp = 30;
	unit.ap = 10;

	unit.hpMax = 30;
	unit.spMax = 30;
	unit.apMax = 10;

	unit.moved = 0;
	unit.evade = 0;

	unit.x = 0;
	unit.y = 0;
	unit.z = 1;

	unit.weapon1 = WEAPON_ACID_STREAM;
	unit.weapon2 = WEAPON_CLAWS;

	unit.equipment = EQUIPMENT_NONE;

	unit.lootList = List:new();

	return unit;
end

function AlienCyborgClass:moveLeft()
	if self.x > 0 then
		local newX = self.x - 1;
		local newY = self.y;
		local newZ = self.z;
		if derelictShipTiles[newZ][newY][newX].tileCode == "0" or derelictShipTiles[newZ][newY][newX].tileCode == "G"
		or derelictShipTiles[newZ][newY][newX].tileCode == "8" or derelictShipTiles[newZ][newY][newX].tileCode == "9" then
			if derelictDoorTiles[newZ][newY][newX] == nil or derelictDoorTiles[newZ][newY][newX].isOpen == true then
				if derelictEntities[newZ][newY][newX] == nil then
					derelictEntities[self.z][self.y][self.x] = nil;
					self.x = newX;
					derelictEntities[self.z][self.y][self.x] = self;
					self.ap = self.ap - 1;
					self.moved = self.moved + 1;
				end
			end
		end
	end
end

function AlienCyborgClass:moveRight()
	if self.x < derelictRoomWidth * derelictFloorWidth-1 then
		local newX = self.x + 1;
		local newY = self.y;
		local newZ = self.z;
		if derelictShipTiles[newZ][newY][newX].tileCode == "0" or derelictShipTiles[newZ][newY][newX].tileCode == "G" 
		or derelictShipTiles[newZ][newY][newX].tileCode == "8" or derelictShipTiles[newZ][newY][newX].tileCode == "9" then
			if derelictDoorTiles[newZ][newY][newX] == nil or derelictDoorTiles[newZ][newY][newX].isOpen == true then
				if derelictEntities[newZ][newY][newX] == nil then
					derelictEntities[self.z][self.y][self.x] = nil;
					self.x = newX;
					derelictEntities[self.z][self.y][self.x] = self;
					self.ap = self.ap - 1;
					self.moved = self.moved + 1;
				end
			end
		end
	end
end

function AlienCyborgClass:moveUp()
	if self.y > 0 then
		local newX = self.x;
		local newY = self.y - 1;
		local newZ = self.z;
		if derelictShipTiles[newZ][newY][newX].tileCode == "0" or derelictShipTiles[newZ][newY][newX].tileCode == "G"
		or derelictShipTiles[newZ][newY][newX].tileCode == "8" or derelictShipTiles[newZ][newY][newX].tileCode == "9" then
			if derelictDoorTiles[newZ][newY][newX] == nil or derelictDoorTiles[newZ][newY][newX].isOpen == true then
				if derelictEntities[newZ][newY][newX] == nil then
					derelictEntities[self.z][self.y][self.x] = nil;
					self.y = newY;
					derelictEntities[self.z][self.y][self.x] = self;
					self.ap = self.ap - 1;
					self.moved = self.moved + 1;
				end
			end
		end
	end
end

function AlienCyborgClass:moveDown()
	if self.y < derelictRoomHeight * derelictFloorHeight-1 then
		local newX = self.x;
		local newY = self.y + 1;
		local newZ = self.z;
		if derelictShipTiles[newZ][newY][newX].tileCode == "0" or derelictShipTiles[newZ][newY][newX].tileCode == "G"
		or derelictShipTiles[newZ][newY][newX].tileCode == "8" or derelictShipTiles[newZ][newY][newX].tileCode == "9" then
			if derelictDoorTiles[newZ][newY][newX] == nil or derelictDoorTiles[newZ][newY][newX].isOpen == true then
				if derelictEntities[newZ][newY][newX] == nil then
					derelictEntities[self.z][self.y][self.x] = nil;
					self.y = newY;
					derelictEntities[self.z][self.y][self.x] = self;
					self.ap = self.ap - 1;
					self.moved = self.moved + 1;
				end
			end
		end
	end
end

function AlienCyborgClass:floorDown()
	if derelictShipTiles[self.z][self.y][self.x].tileCode == "9" then
		if self.z > 0 then
			derelictEntities[self.z][self.y][self.x] = nil;
			self.z = self.z - 1;
			derelictEntities[self.z][self.y][self.x] = self;
			self.ap = self.ap -1;
			self.moved = self.moved + 1;
		end
	end
end

function AlienCyborgClass:floorUp()
	if derelictShipTiles[self.z][self.y][self.x].tileCode == "8" then
		if self.z < derelictFloorDepth then
			derelictEntities[self.z][self.y][self.x] = nil;	
			self.z = self.z +1
			derelictEntities[self.z][self.y][self.x] = self;
			self.ap = self.ap -1;
			self.moved = self.moved + 1;
		end
	end
end

function AlienCyborgClass:fire(x, y, z)
	if self.ap > 1 then
		local entity = derelictEntities[z][y][x];
		if entity ~= nil then
			local distance = calcDistance(x, y, z, self.x, self.y, self.z);
			local canFireWep1 = checkWeaponRange(self.weapon1, distance);
			local canFireWep2 = checkWeaponRange(self.weapon2, distance);
			if canFireWep1 == true then
				local damage = calcWeaponDamage(self.weapon1, distance, entity.moved, entity.evade);
				entity:damage(damage);
				self.ap = self.ap - 2;
			elseif canFireWep2 == true then
				local damage = calcWeaponDamage(self.weapon2, distance, entity.moved, entity.evade);
				entity:damage(damage);
				self.ap = self.ap - 2;
			end
		end
	end
end

function AlienCyborgClass:door(x, y, z)
	local door = derelictDoorTiles[z][y][x];
	if door ~= nil then
		if door.isLocked == false then
			if door.isOpen == false then
				if self.ap > 1 then
					door.isOpen = true;
					self.ap = self.ap - 2;
				end
			end
		end
	end
end

function AlienCyborgClass:skill1(x, y, z)
	-- hack door
end

function AlienCyborgClass:skill2(x, y, z)
	-- hack turret
end

function AlienCyborgClass:damage(amount)
	print ("Damage: " .. amount);

	if self.sp > 0 then
		self.sp = self.sp - amount;
	else
		self.hp = self.hp - amount;
	end
	if self.hp < 1 then
		self.dead = true;
		derelictEntities[self.z][self.y][self.x] = nil;
	end
end

function AlienCyborgClass:setPosition(x, y, z)
	derelictEntities[self.z][self.y][self.x] = nil;	

	self.x = x;
	self.y = y;
	self.z = z;

	derelictEntities[z][y][x] = self;
end

