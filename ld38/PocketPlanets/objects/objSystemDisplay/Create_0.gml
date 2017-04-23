/// @description Insert description here
// You can write your code in this editor

// Test code
oSystem = scrGenerateSystem();

show_debug_message("Planets: " + string(ds_list_size(oSystem[? "Planets"])));

oPlanets = ds_list_create();
oShips = ds_list_create();

var planets = oSystem[? "Planets"];

// TEST code to pick a home planet
var homePlanet = irandom(ds_list_size(planets) - 1);
var planet = planets[| homePlanet];
planet[? "Owned"] = id;
planet[? "Scanned"] = true;
planet[? "Population"] = 1;

for (var i = ds_list_size(planets); i > 0; --i) {
	var planet = planets[| i - 1];
	var iPlanet = scrCreateSystemPlanet(planet);
	iPlanet.oSystem = id;
	ds_list_add(oPlanets, iPlanet)
};


var ships = oSystem[? "Ships"];
for (var i = ds_list_size(ships); i > 0; --i) {
	var ship = ships[| i - 1];
	var iShip = scrCreateSystemShip(ship);
	iShip.oSystem = id;
	ds_list_add(oShips, iShip);
};

oHighlighted = false;
oSelections = ds_list_create();
oSelectionObject = undefined;

oCamera = ds_map_create();
oCamera[? "x"] = 0;
oCamera[? "y"] = 0;
oCamera[? "mX"] = 0;
oCamera[? "mY"] = 0;
oCamera[? "id"] = view_camera[0];

draw_set_font(font_0);