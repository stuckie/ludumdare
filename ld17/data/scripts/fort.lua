-- Fort

-- Rules:
-- The fort can hold gold which does not decay over time!
-- The fort can also produce men and ships - at a cost of gold, of course!
-- When a fort is looted, it becomes yours.
-- They CAN be destroyed though!

FortClass = {};
FortClass.__index = FortClass;

UNIT_FORT = 2;

function FortClass.create( id, owner )
	local unit = {};
	setmetatable(unit, FortClass);

	print ("Creating Fort with ID " .. id);

	unit.id = id;				-- unique id of this unit.
	unit.owner = owner;			-- Which player this unit belonds to
	unit.type = "Pirate Fort";

	unit.x = 0;
	unit.y = 0;
	unit.z = 1;					-- should probably always be 1 unless we have planes!... this is the collision layer

	unit.gold = 0;
	unit.health = 100;
	unit.dead = false;

	unit.selected = false;

	return unit;
end

function FortClass:update()
	-- nothing really to update, but it's essentially a "pure virtual"
end

function FortClass:damage(amount)
	self.health = self.health - amount;

	if self.health < 1 then
		self.dead = true;
		self.owner:removeUnit(self);
		removeUnit(self);
	end
end

function FortClass:setPosition(x, y, z)
	entityMap:kill(self.x, self.y, self.z);

	self.x = x;
	self.y = y;
	self.z = z;

	entityMap:add(self, self.x, self.y, self.z);
end

function FortClass:render()
	TextureMan:blitTexture(self.owner.beard, self.x - gameCamera.x * 64, self.y - gameCamera.y * 64, 0, 128, 192, 64, 64);
end