-- Locker Class
-- These contain goodies and things...

LockerClass = {};
LockerClass.__index = LockerClass;

function LockerClass.create( locked )
	local unit = {};
	setmetatable(unit, LockerClass);

	unit.isLocked = locked;
	unit.class = CLASS_LOCKER;
	
	unit.tileType = "empty";

	return unit;
end
