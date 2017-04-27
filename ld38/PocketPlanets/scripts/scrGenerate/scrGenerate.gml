/// @desc Generate something
/// @param Generate Enum of what to generate (required)
/// @param Type|X Type of Ship (Generate.Ship) or X position of Planet (required for Generate.Planet)
/// @param Y position of Planet (required for Generate.Planet only)

enum Generate
{	System
,	Planet
,	Ship
};

var command = argument[0];

switch (command) {
	/////////////////////////////////////////////////////////////
	// Generate System
	/////////////////////////////////////////////////////////////
	case Generate.System: {
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
			var planet = scrGenerate(Generate.Planet, (positions[# i - 1, 0] * planetDist) + irandom(planetDist), (positions[# i - 1, 1] * planetDist) + irandom(planetDist));
			ds_list_add(planets, planet);
		}

		ds_grid_destroy(positions);

		system[? "Ships"] = ds_list_create();

		return system;
	};
	break;
	/////////////////////////////////////////////////////////////
	// Generate Planet
	/////////////////////////////////////////////////////////////
	case Generate.Planet: {
		var _x = argument[1];
		var _y = argument[2];

		var Atmosphere = irandom(100); // atmosphere ranges 0 - 99
		// 50 - ideal  +1 Pop
		// 30 - 50/50 - 70 - Average
		// 20 - 30/80 - 80 - Taxing -1 Pop
		// 10 - 20/80 - 90 - Extreme -2 Pop
		// 0 - 10/90 - 99 - Unhabitable

		var MaxPopulation = Atmosphere * 2; // Max population will increase with Atmosphere and Ecology spending

		var planet = ds_map_create();

		planet[? "X"] = _x;
		planet[? "Y"] = _y;
		planet[? "Name"] = "Planet " + string(++global.PlanetCount);
		planet[? "Population"] = 0;
		planet[? "Scanned"] = false;
		planet[? "Owned"] = noone;
		planet[? "MaxPopulation"] = MaxPopulation;
		planet[? "Atmosphere"] = Atmosphere;

		return planet;
	};
	break;
	/////////////////////////////////////////////////////////////
	// Generate Ship
	/////////////////////////////////////////////////////////////
	case Generate.Ship: {
		var type = argument[1];
		var components = ds_list_create();

		var ship = ds_map_create();
		ship[? "Name"] = "Ship " + string(random(10000));
		ship[? "Type"] = type;

		ship[? "X"] = 0;
		ship[? "Y"] = 0;

		return ship;
	};
	break;
};