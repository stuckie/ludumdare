// Generate a random system structure

/* System {
		Planets - list of planet structs...
		Name - string.. random name?
		Sprite
		Icon
		X
		Y
	}
*/

var system = ds_map_create();

var planetCount = 1 + irandom(10); // upto ten planets a system?
var planets = ds_list_create();

system[? "Name"] = "System " + string(random(10000));
system[? "Planets"] = planets;

for (var i = 0; i < planetCount; ++i) {
	var planet = scrGeneratePlanet();
	ds_list_add(planets, planet);
}

return system;