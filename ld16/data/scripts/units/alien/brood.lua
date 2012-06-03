--Alien Brood Spawn

AlienBroodClass = {};
AlienBroodClass.__index = AlienBroodClass;

function AlienBroodClass.create( type )
	local unit = {};
	setmetatable(unit, AlienBroodClass);

	unit.type = type;			-- Human or AI (hah)
	unit.class = CLASS_ALIEN_BROOD;

	unit.hp = 10;
	unit.sp = 0;
	unit.ap = 10;

	unit.hpMax = 10;
	unit.spMax = 0;
	unit.apMax = 10;

	unit.x = 0;
	unit.y = 0;
	unit.z = 1;

	unit.evade = 0;
	unit.moved = 0;

	unit.weapon1 = WEAPON_CLAWS;
	unit.weapon2 = WEAPON_NONE;

	unit.equipment = EQUIPMENT_NONE;

	unit.lootList = List:new();

	return unit;
end

function AlienBroodClass:moveLeft()
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

function AlienBroodClass:moveRight()
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

function AlienBroodClass:moveUp()
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

function AlienBroodClass:moveDown()
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

function AlienBroodClass:floorDown()
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

function AlienBroodClass:floorUp()
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

function AlienBroodClass:fire(x, y, z)
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

function AlienBroodClass:door(x, y, z)
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

function AlienBroodClass:skill1(x, y, z)
	-- hatch
end

function AlienBroodClass:skill2(x, y, z)
	-- spit
end

function AlienBroodClass:damage(amount)
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

function AlienBroodClass:setPosition(x, y, z)
	derelictEntities[self.z][self.y][self.x] = nil;	

	self.x = x;
	self.y = y;
	self.z = z;

	derelictEntities[z][y][x] = self;
end

