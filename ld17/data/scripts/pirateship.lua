-- Pirate Ship, YARGH!

-- Rules:
-- The Pirate Ship can sail on yonder sea!
-- Each Ship can hold upto 5 Pirate Men troops ( so that's 100, effectively )
-- Ships speed up by sailing with the wind ( watch the clouds )
-- Ships cost GOLD! 100 gold per ship.
-- Ships can dock/ransack ports if they're on a beach
-- Ships cost gold to upkeep... they'll drain 1g every 5 seconds.
-- Should a Ship run out of morale, the crew mutinies! The ungrateful swines!
-- Morale is gained by winning fights, and finding loot.
-- Gold can be exchanged between the Booty and a Unit when at a friendly Port.

PirateShipClass = {};
PirateShipClass.__index = PirateShipClass;

UNIT_PIRATESHIP = 1;

SHIP_STOPPED = "Stopped";
SHIP_SAILING = "Sailing";
SHIP_ATTACKING = "Attacking";
SHIP_DOCKED = "Docked";
SHIP_NEED_REPAIRED = "Damaged";

function PirateShipClass.create( id, owner )
	local unit = {};
	setmetatable(unit, PirateShipClass);

	unit.id = id;				-- unique id of this unit.
	unit.owner = owner;			-- Which player this unit belonds to
	unit.type = "Pirate Ship";
	unit.state = SHIP_STOPPED;

	unit.health = 100;
	unit.men = 5;
	unit.morale = 100;

	unit.maxMen = 5;
	unit.maxMorale = 100;
	unit.maxHealth = 100;

	unit.x = 0;
	unit.y = 0;
	unit.z = 0;					-- should probably always be 1 unless we have planes!... this is the collision layer

	unit.gold = 0;
	unit.goldDeductionTime = 10;
	unit.goldDeductionStart = 10;
	unit.speed = 30; 			-- This is modified by the wind, somewhat.

	unit.waypoints = List:new(); -- list of waypoints.

	unit.dead = false;

	unit.selected = false;
	unit.cannonReload = 0;
	unit.cannonReloadTime = 10;
	unit.bored = 20;
	unit.boredTimeout = 20;

	unit.gfxUP = { u=128 ,v=0 };
	unit.gfxDOWN = { u=0 ,v=0 };
	unit.gfxLEFT = { u=64 ,v=0 };
	unit.gfxRIGHT = { u=192 ,v=0 };
	unit.gfxUPLEFT = { u=64 ,v=64 };
	unit.gfxUPRIGHT = { u=128 ,v=64 };
	unit.gfxDOWNLEFT = { u=0 ,v=64 };
	unit.gfxDOWNRIGHT = { u=192 ,v=64 };

	unit.direction = unit.gfxUP;

	return unit;
end

local math = math;

function PirateShipClass:lookAt(objX, objY)
	local x = objX - self.x;
	local y = objY - self.y;

	local speed = self.speed * DeltaTime;
	local radAngle = math.atan2(y, x);
	local angle = (math.deg(radAngle) + 180);

	if angle < 20 then self.direction = self.gfxLEFT;
	elseif angle < 80 then self.direction = self.gfxUPLEFT;
	elseif angle < 100 then self.direction = self.gfxUP;
	elseif angle < 160 then self.direction = self.gfxUPRIGHT;
	elseif angle < 200 then self.direction = self.gfxRIGHT;
	elseif angle < 260 then self.direction = self.gfxDOWNRIGHT;
	elseif angle < 280 then self.direction = self.gfxDOWN;
	elseif angle < 340 then self.direction = self.gfxDOWNLEFT;
	elseif angle < 360 then self.direction = self.gfxLEFT;
	else self.direction = self.gfxUP;
	end

	local newX = self.x + ( math.cos(radAngle) * speed ) + (WindX * DeltaTime);
	local newY = self.y + ( math.sin(radAngle) * speed ) + (WindY * DeltaTime);
	if self:checkCollision(newX, newY) == false then
		self.x = newX;
		self.y = newY;
	else
		self.waypoints:pop(1);
	end
end

function PirateShipClass:checkCollision(x, y)
	x = (x+32)/64;
	y = (y+32)/64;

	x = math.modf(x);
	y = math.modf(y);

	if x < 0 then x = 0 end
	if y < 0 then y = 0 end
	if x > 99 then x = 99 end
	if y > 99 then y = 99 end

	local tile0 = layer0Map[y][x];
	local tile1 = layer1Map[y][x];
	if tile0 ~= nil then
		if tile0.tileCode == "0" and tile1 == nil then
			return false
		end
	end

	return true;
end

function PirateShipClass:update()
	-- Move Them Pirates!
	if self.waypoints:len() > 0 then
		self.state = SHIP_SAILING;
		local waypoint = self.waypoints[1];
		self:lookAt(waypoint.x, waypoint.y);
		if calcDistanceXY(self.x, self.y, waypoint.x, waypoint.y) < (32.0 * DeltaTime) then
			self.waypoints:pop(1);
		end
	elseif self.state ~= SHIP_ATTACKING then
		if self.waypoints:len() == 0 then
			self.state = SHIP_STOPPED;
		end
	end

	-- Ship maintenance costs gold...
	if self.gold > 0 then
		self.goldDeductionTime = self.goldDeductionTime - DeltaTime;
		if self.goldDeductionTime < 0 then
			self.gold = self.gold - 1;
			self.goldDeductionTime = self.goldDeductionStart;
		end
	elseif self.gold <= 0 then
		-- start pulling down morale....
		self.goldDeductionTime = self.goldDeductionTime - DeltaTime;
		if self.goldDeductionTime < 0 then
			self.morale = self.morale - 5;
			self.goldDeductionTime = self.goldDeductionStart;
		end
	end

	-- MUTINY! unless we already have...
	if self.morale <= 0 then
		if self.owner.beard ~= "Neutral" then
			self.owner:removeUnit(self);
			getPlayer("Neutral"):takeUnit(self);
		end
	end

	self.cannonReload = self.cannonReload - DeltaTime;
end

function PirateShipClass:moveTo(x, y)
	-- Lets just blindly shove this on the waypoint stack for the moment.. really we should be doing some A* here
	self.waypoints:append({x=x, y=y});
end

function PirateShipClass:attack(entity)
	if entity == nil then
		self.state = SHIP_STOPPED;
		return
	end

	if self.state ~= SHIP_ATTACKING then
		self.state = SHIP_ATTACKING;
	else
		self.bored = self.bored - DeltaTime;
		if self.bored < 0 then
			self.state = SHIP_STOPPED;
			self.bored = self.boredTimeout;
		end
	end

	if self.cannonReload < 0 then
		fireCannonBall(self.x + 32, self.y + 32, entity.x + 32, entity.y + 32, entity);
		self.cannonReload = self.cannonReloadTime;
	end
end

function PirateShipClass:damage(amount)
	self.health = self.health - amount;

	if self.health < 1 then
		self.dead = true;
		self.owner:removeUnit(self);
		removeUnit(self);
	end
end

function PirateShipClass:setPosition(x, y, z)
	self.x = x;
	self.y = y;
	self.z = z;
end

function PirateShipClass:render()
	if (calcDistanceX((gameCamera.x*64) + 64, self.x*64) < WindowWidth + 64
	and calcDistanceY((gameCamera.y*64) + 64, self.y*64) < WindowHeight + 64) then
		TextureMan:blitTexture(self.owner.beard, self.x - gameCamera.x * 64, self.y - gameCamera.y * 64, 0, self.direction.u, self.direction.v, 64, 64);
	end
end