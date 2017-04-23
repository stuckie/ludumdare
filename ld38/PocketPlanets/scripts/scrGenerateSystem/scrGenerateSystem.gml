// Generate a random system structure

/* System {
		Planets - list of planet structs...
		Ships - list of ship structs...
		Name - string.. random name?
		Sprite
		Icon
		X
		Y
	}
*/

var system = ds_map_create();

var planetCount = 20;
var planetDist = 128;
var planets = ds_list_create();

system[? "Name"] = "System " + string(random(10000));
system[? "Planets"] = planets;

// Quite useless procedural placement...
var width = floor(room_width / planetDist);
var height = floor(room_height / planetDist);
var spaces = ds_grid_create(width + 1, height + 1);

if (planetCount > width * height) {
	planetCount = width * height;
	show_debug_message("Too Many Planets.. max: " + string(planetCount));
}

var positions = ds_grid_create(planetCount, 2);
for (var i = planetCount; i > 0; --i) {
	var _x = irandom(width);
	var _y = irandom(height);
	if (0 == spaces[# _x, _y]) {
		spaces[# _x, _y] = 1;
		positions[# i - 1, 0] = _x;
		positions[# i - 1, 1] = _y;
	} else
		++i; // try again..
};

for (var i = planetCount; i > 0; --i) {
	var planet = scrGeneratePlanet((positions[# i - 1, 0] * planetDist) + irandom(planetDist), (positions[# i - 1, 1] * planetDist) + irandom(planetDist));
	ds_list_add(planets, planet);
}

ds_grid_destroy(positions);

system[? "Ships"] = ds_list_create();

return system;