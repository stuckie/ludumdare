// Create a planet instance... called from the System to create an icon to show

var planet = argument[0];

var _x = planet[? "X"];
var _y = planet[? "Y"];

var inst = instance_create_layer(_x, _y, "Planets", objSystemPlanet);
inst.oPlanet = planet;

return inst;