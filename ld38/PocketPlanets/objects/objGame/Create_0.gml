/// @description Game Setup

// Right.. round two.
// It's 4.30pm
// I've a cup of tea
// Let's get going...

// We're simplifying right down here, so we want a couple of things...
// We want a global galaxy to play around in the size of the room.
// Ideally we want a quick frontend to set galaxy size, but we'll make do with what we have for now.
// That can be a problem at 1am...

// Some number setup...
global.PlanetCount = 0;
global.ShipCount = 0;

// We can already generate a system and spread it about, so lets go and do that.
global.GalaxyData = scrGenerateSystem();

// Next bit is taking that system and generating planets and ships from it.
oPlanets = ds_list_create();
oShips = ds_list_create();

var planets = global.GalaxyData[? "Planets"];
for (var i = ds_list_size(planets); i > 0; --i) {
	var planet = planets[| i - 1];
	var iPlanet = scrCreatePlanet(planet);
	iPlanet.oGame = id;
	ds_list_add(oPlanets, iPlanet);
};

var ships = global.GalaxyData[? "Ships"];
for (var i = ds_list_size(ships); i > 0; --i) {
	var ship = ships[| i - 1];
	var iShip = scrCreateShip(ship);
	iShip.oSystem = id;
	ds_list_add(oShips, iShip);
};

// Now generate the Players.. one user and 1 CPU just now?
global.Players = ds_list_create();
oPlayer = instance_create_layer(0, 0, "Controllers", objPlayer);
oAI = instance_create_layer(0, 0, "Controllers", objAI);
ds_list_add(global.Players, oPlayer);
ds_list_add(global.Players, oAI);

// Give each player a homeworld, and set their ships up.
var iHomeworld = irandom(ds_list_size(oPlanets));
var homeworld = oPlanets[| iHomeworld];
ds_list_add(oPlayer.oPlanets, homeworld);
homeworld.oAtmosphere = 50; // it's the homeworld, it's ideal
homeworld.oPopulation = 100;
homeworld.oOwnedBy = oPlayer;
scrScanPlanet(oPlayer, homeworld);
with (oPlayer)
	scrSelectDisplayPlanet(homeworld, true);
	
global.MouseX = homeworld.x - (camera_get_view_width(view_camera[0]) / 2);
global.MouseY = homeworld.y  - (camera_get_view_height(view_camera[0]) / 2);
camera_set_view_pos(view_camera[0], global.MouseX, global.MouseY);

var ship = scrGenerateShip(ConstructShip.Scout);
ship[? "X"] = homeworld.x + 32;
ship[? "Y"] = homeworld.y;
ds_list_add(global.GalaxyData[? "Ships"], ship);
var iShip = scrCreateShip(ship);
iShip.oSystem = id;
ds_list_add(oShips, iShip);
ds_list_add(oPlayer.oShips, iShip);

ship = scrGenerateShip(ConstructShip.Scout);
ship[? "X"] = homeworld.x - 32;
ship[? "Y"] = homeworld.y;
ds_list_add(global.GalaxyData[? "Ships"], ship);
var iShip = scrCreateShip(ship);
iShip.oSystem = id;
ds_list_add(oShips, iShip);
ds_list_add(oPlayer.oShips, iShip);

ship = scrGenerateShip(ConstructShip.ColonyShip);
ship[? "X"] = homeworld.x;
ship[? "Y"] = homeworld.y - 32;
ds_list_add(global.GalaxyData[? "Ships"], ship);
var iShip = scrCreateShip(ship);
iShip.oSystem = id;
ds_list_add(oShips, iShip);
ds_list_add(oPlayer.oShips, iShip);


draw_set_font(font_0);
global.LastMouseX = 0;
global.LastMouseY = 0;