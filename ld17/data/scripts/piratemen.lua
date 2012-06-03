-- Pirate Men, YARGH!

-- Rules:
-- Men essentially acts as health, once men reach 0, the unit is destroyed.
-- Each Troop can hold upto 25 men.
-- Morale is essentially a combat boost.
-- Men who have 100 morale means they fight at peak proficency.
-- As Men are lost, the morale dips drastically ( 5pts per man lost )
-- As Men move, the morale drops also ( 1pt per tile )
-- If Morale is zero, effectively the unit will more or less die ( unless are very lucky. )
-- Morale is gained by winning fights, finding loot and maintaining a high gold to men ratio that increases morale over time.
-- Gold is lost when a man dies ( his share gets lost, as it was in his pockets! )
-- Gold can be exchanged between the Booty and a Unit when at a friendly Port.
-- The equation for morale based on men and gold therefore is as follows: every N seconds morale += gold/men;

PirateMenClass = {};
PirateMenClass.__index = PirateMenClass;

UNIT_PIRATEMEN = 0;

PIRATEMAN_STANDING = "Standing";
PIRATEMAN_WALKING = "Walking";
PIRATEMAN_ATTACKING = "Attacking";
PIRATEMAN_LOOTING = "Looting";

function PirateMenClass.create( id, owner )
	local unit = {};
	setmetatable(unit, PirateMenClass);

	print ("Creating PirateMan with ID " .. id);

	unit.id = id;				-- unique id of this unit.
	unit.owner = owner;			-- Which player this unit belonds to
	unit.type = "Pirate Men!";

	unit.men = 25;
	unit.morale = 100;

	unit.maxMen = 25;
	unit.maxMorale = 100;

	unit.x = 0;
	unit.y = 0;
	unit.z = 1;					-- should probably always be 1 unless we have planes!... this is the collision layer

	unit.gold = 0;
	unit.timeForMoraleBoost = 0;
	unit.boostDelay = 5; -- should be 5 seconds.
	unit.speed = 15;

	unit.waypoints = List:new(); -- list of waypoints.

	unit.dead = false;

	unit.selected = false;

	unit.attackDelay = 5;
	unit.attackTime = 5;

	unit.anim1 = { u = 64, v = 128 };
	unit.anim2 = { u = 128, v = 128 };

	unit.frame = unit.anim1;
	unit.frameDelay = 0.5;
	unit.maxFrameDelay = 0.5;
	unit.state = PIRATEMAN_STANDING;
	unit.enemy = nil;

	return unit;
end

function PirateMenClass:lookAt(objX, objY)
	local x = objX - self.x;
	local y = objY - self.y;

	local speed = self.speed * DeltaTime;
	local radAngle = math.atan2(y, x);

	local newX = self.x + ( math.cos(radAngle) * speed );
	local newY = self.y + ( math.sin(radAngle) * speed );

	if self:checkCollision(newX, newY) == false then
		self.x = newX;
		self.y = newY;
	else
		self.waypoints:pop(1);
		self.state = PIRATEMAN_STANDING;
	end
end

function PirateMenClass:checkCollision(x, y)
	x = (x+32)/64;
	y = (y+32)/64;

	x = math.modf(x);
	y = math.modf(y);

	if x < 0 then x = 0 end
	if y < 0 then y = 0 end
	if x > 99 then x = 99 end
	if y > 99 then y = 99 end

	local tile = layer0Map[y][x];
	if tile ~= nil then
		if tile.tileCode == "0" then
			return true
		end
	end

	return false;
end

function PirateMenClass:update()
	-- Piratey Morale Boost!
	self.timeForMoraleBoost = self.timeForMoraleBoost - DeltaTime;
	if self.timeForMoraleBoost < 0 then
		self.timeForMoraleBoost = GameTime:Time() + self.boostDelay;
		if self.morale < self.maxMorale then
			self.morale = self.morale + (self.gold/self.men);
			if self.morale > self.maxMorale then self.morale = self.maxMorale end
		end
	end

	-- Move Them Pirates!
	if self.state == PIRATEMAN_STANDING then
		if self.waypoints:len() > 0 then
			self.state = PIRATEMAN_WALKING;
		end
	elseif self.state == PIRATEMAN_WALKING then
		-- Update Frame!
		self.frameDelay = self.frameDelay - DeltaTime;
		if self.frameDelay < 0 then
			self.frameDelay = self.maxFrameDelay;
			if self.frame == self.anim1 then self.frame = self.anim2
			elseif self.frame == self.anim2 then self.frame = self.anim1
			end
		end

		if self.waypoints:len() > 0 then
			local waypoint = self.waypoints[1];
			self:lookAt(waypoint.x, waypoint.y);
			if calcDistanceXY(self.x, self.y, waypoint.x, waypoint.y) < (32.0 * DeltaTime) then
				self.waypoints:pop(1);
				self.state = PIRATEMAN_STANDING;
			end
		end
	elseif self.state == PIRATEMAN_ATTACKING then
		-- Update Frame!
		self.frameDelay = self.frameDelay - DeltaTime;
		self.attackDelay = self.attackDelay - DeltaTime;
		if self.frameDelay < 0 then
			self.frameDelay = self.maxFrameDelay / 2; -- more animated!!!
			if self.frame == self.anim1 then self.frame = self.anim2
			elseif self.frame == self.anim2 then self.frame = self.anim1
			end
		end
		if self.attackDelay < 0 then
			self.attackDelay = self.attackTime;
			if self.enemy ~= nil then
				self.enemy:damage(5 * (self.morale/self.maxMorale));
			end
		end
	elseif self.state == PIRATEMAN_LOOTING then
		-- Update Frame!
		self.frameDelay = self.frameDelay - DeltaTime;
		if self.frameDelay < 0 then
			self.frameDelay = self.maxFrameDelay / 3;
			if self.frame == self.anim1 then self.frame = self.anim2
			elseif self.frame == self.anim2 then self.frame = self.anim1
			end
		end
	end

	if self.enemy ~= nil then
		if calcDistanceXY(self.x, self.y, self.enemy.x, self.enemy.y) < 32.0 then
			if self.state ~= PIRATEMAN_ATTACKING then
				addPirateAttackCloud(self.x, self.y);
				self.state = PIRATEMAN_ATTACKING;
			end
		end
	end
end

function PirateMenClass:moveTo(x, y)
	-- Lets just blindly shove this on the waypoint stack for the moment.. really we should be doing some A* here
	self.waypoints:append({x=x, y=y});
end

function PirateMenClass:attack(entity)
	print("Entity " .. self.id .. " Attacking: " .. entity.id);
	self.enemy = entity;
	local distance = calcDistanceXY(self.x, self.y, entity.x, entity.y);
	if distance > 32.0 then
		self:moveTo(entity.x, entity.y);
	else
		addPirateAttackCloud(self.x, self.y);
		self.state = PIRATEMAN_ATTACKING;
	end
end

function PirateMenClass:damage(amount)
	self.men = self.men - amount;

	if self.men < 1 then
		self.dead = true;
		self.owner:removeUnit(self);
		removeUnit(self);
	end
end

function PirateMenClass:setPosition(x, y, z)
	entityMap:kill(self.x, self.y, self.z);

	self.x = x;
	self.y = y;
	self.z = z;

	entityMap:add(self, self.x, self.y, self.z);
end

function PirateMenClass:render()
	TextureMan:blitTexture(self.owner.beard, self.x - gameCamera.x * 64, self.y - gameCamera.y * 64, 0, self.frame.u, self.frame.v, 64, 64);
end