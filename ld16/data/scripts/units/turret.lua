-- Turret Class

TurretClass = {};
TurretClass.__index = TurretClass;

function TurretClass.create( type, weapon )
	local unit = {};
	setmetatable(unit, TurretClass);

	unit.type = type;			-- Human or AI (hah)
	unit.class = CLASS_TURRET;

	unit.hp = 10;
	unit.sp = 10;
	unit.ap = 5;

	unit.hpMax = 10;
	unit.spMax = 10;
	unit.apMax = 5;

	unit.x = 0;
	unit.y = 0;
	unit.z = 0;

	unit.evade = 0;
	unit.moved = 0;

	unit.weapon1 = weapon;
	unit.weapon2 = WEAPON_NONE;

	return unit;
end

function TurretClass:moveLeft()

end

function TurretClass:moveRight()

end

function TurretClass:moveUp()

end

function TurretClass:moveDown()

end

function TurretClass:floorDown()

end

function TurretClass:floorUp()

end

function TurretClass:fire(x, y, z)
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

function TurretClass:door(x, y, z)

end

function TurretClass:skill1(x, y, z)
	-- dodge
end

function TurretClass:skill2(x, y, z)
	-- hide
end

function TurretClass:damage(amount)
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

function TurretClass:setPosition(x, y, z)
	derelictEntities[self.z][self.y][self.x] = nil;	

	self.x = x;
	self.y = y;
	self.z = z;

	derelictEntities[z][y][x] = self;
end

