// Ships come with a blueprint... of sorts.. need to at least pass in size
// Should be built by a ship factory, and then whatever modules the player has selected stuffed inside

enum ShipSize
{	Tiny
,	Small
,	Medium
,	Large
,	Huge
};

var size = argument[0];
var components = ds_list_create();

var ship = ds_map_create();
ship[? "Name"] = "Ship " + string(random(10000));
ship[? "Size"] = size;

switch (size) {
	case ShipSize.Tiny: {
		ship[? "Sprite"] = sprShipsTiny;
		ship[? "Icon"] = 0;
	};
	break;
	case ShipSize.Small: {
		ship[? "Sprite"] = sprShipsTiny; // sprShipsSmall;
		ship[? "Icon"] = 0;
	};
	break;
	case ShipSize.Medium: {
		ship[? "Sprite"] = sprShipsTiny; // sprShipsMedium;
		ship[? "Icon"] = 0;
	};
	break;
	case ShipSize.Large: {
		ship[? "Sprite"] = sprShipsTiny; // sprShipsLarge;
		ship[? "Icon"] = 0;
	};
	break;
	case ShipSize.Huge: {
		ship[? "Sprite"] = sprShipsTiny; // sprShipsHuge
		ship[? "Icon"] = 0;
	};
	break;
};

ship[? "X"] = 0;
ship[? "Y"] = 0;

return ship;