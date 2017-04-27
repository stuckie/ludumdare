/// @desc Create an Object
/// @param Create Enum of what to create
/// @param Planet|Ship Planet to Create (only for Create.Planet) or Ship Type to Create (only for Create.Ship)
/// @param Player instance of Player to use as owner (only for Create.Ship)

enum Create
{	Planet
,	Ship
};

enum ConstructShip
{	None
,	Scout
,	Fighter
,	Destroyer
,	Dreadnaught
,	ColonyShip
};

var command = argument[0];
var _player = argument[2];

switch (command) {
	case Create.Planet: {
		var _planet = argument[1];

		var _x = _planet[? "X"];
		var _y = _planet[? "Y"];

		var inst = instance_create_layer(_x, _y, "Planets", objPlanet);
		inst.oPlanet = _planet;
		inst.oOwnedBy = _player

		return inst;
	};
	break;
	case Create.Ship: {
		var _ship = argument[1];

		var _x = _ship[? "X"];
		var _y = _ship[? "Y"];

		var inst = instance_create_layer(_x, _y, "Ships", objShip);
		inst.oShip = _ship;
		inst.oOwnedBy = _player;

		return inst;
	};
	break;
};