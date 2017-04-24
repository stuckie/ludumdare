// Creates a ship for displaying within the System View

enum ConstructShip
{	None
,	Scout
,	Fighter
,	Destroyer
,	Dreadnaught
,	ColonyShip
};

var _ship = argument[0];
var _player = argument[1]

var _x = _ship[? "X"];
var _y = _ship[? "Y"];

var inst = instance_create_layer(_x, _y, "Ships", objShip);
inst.oShip = _ship;
inst.oOwnedBy = _player;

return inst;