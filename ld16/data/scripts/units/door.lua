-- Door Class

DoorClass = {};
DoorClass.__index = DoorClass;

function DoorClass.create( locked )
	local unit = {};
	setmetatable(unit, DoorClass);

	unit.isLocked = locked;
	unit.isOpen = false;
	unit.class = CLASS_DOOR;
	unit.tileType = "empty";

	return unit;
end
