// Creates a ship for displaying within the System View

var ship = argument[0];

var _x = ship[? "X"];
var _y = ship[? "Y"];

var inst = instance_create_layer(_x, _y, "Ships", objSystemShip);
inst.oShip = ship;

return inst;