// Generate a random galaxy structure

/* Galaxy {
		Systems - list of system structs...
		Name - string.. random name?
		Sprite
		Icon
		X
		Y
	}
*/

var galaxy = ds_map_create();

var systemCount = 1 + irandom(10); // upto ten systems a galaxy?
var systems = ds_list_create();

galaxy[? "Name"] = "Galaxy " + string(random(10000));
galaxy[? "Systems"] = systems;

for (var i = 0; i < systemCount; ++i) {
	var system = scrGenerateSystem();
	ds_list_add(systems, system);
}

return galaxy;