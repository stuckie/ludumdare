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
global.GameData = id;

randomise();

// We can already generate a system and spread it about, so lets go and do that.
global.GalaxyData = scrGenerate(Generate.System);

// Next bit is taking that system and generating planets and ships from it.
oPlanets = ds_list_create();
oShips = ds_list_create();

var planets = global.GalaxyData[? "Planets"];
for (var i = ds_list_size(planets); i > 0; --i) {
	var planet = planets[| i - 1];
	var iPlanet = scrCreate(Create.Planet, planet, noone);
	iPlanet.oGame = id;
	ds_list_add(oPlanets, iPlanet);
};

// Now generate the Players.. one user and 1 CPU just now?
global.Players = ds_list_create();
oPlayer = instance_create_layer(0, 0, "Controllers", objPlayer);
ds_list_add(global.Players, oPlayer);


// Give each player a homeworld, and set their ships up.
var iHomeworld = irandom(ds_list_size(oPlanets));
var homeworld = oPlanets[| iHomeworld];
homeworld.oAtmosphere = 50; // it's the homeworld, it's ideal
scrPlanet(Planet.Scan, homeworld, oPlayer);
scrPlanet(Planet.Colonise, homeworld, oPlayer);
homeworld.oPopulation = 100;

with (oPlayer)
	scrPlanet(Planet.Select, homeworld, true);
	
oPlayer.image_blend = c_white;
	
global.MouseX = homeworld.x - (camera_get_view_width(view_camera[0]) / 2);
global.MouseY = homeworld.y  - (camera_get_view_height(view_camera[0]) / 2);
camera_set_view_pos(view_camera[0], global.MouseX, global.MouseY);

var ship = scrShip(Ship.Build, ConstructShip.Scout, oPlayer, homeworld);
ship = scrShip(Ship.Build, ConstructShip.Scout, oPlayer, homeworld);
ship = scrShip(Ship.Build, ConstructShip.ColonyShip, oPlayer, homeworld);

var hue = 0;
for (var i = 0; i < 5; ++i) {
	var AI = instance_create_layer(0, 0, "Controllers", objAI);
	ds_list_add(global.Players, AI);
	var aiHomeworld = irandom(ds_list_size(oPlanets) - 1);
	homeworld = oPlanets[| aiHomeworld];	
	while (noone != homeworld.oOwnedBy) {
		aiHomeworld = irandom(ds_list_size(oPlanets) - 1);
		homeworld = oPlanets[| aiHomeworld];
	}

	homeworld.oAtmosphere = 50; // it's the homeworld, it's ideal
	scrPlanet(Planet.Scan, homeworld, AI);
	scrPlanet(Planet.Colonise, homeworld, AI);
	homeworld.oPopulation = 100;
	ds_list_add(AI.oSeenPlanets, homeworld);
	
	ship = scrShip(Ship.Build, ConstructShip.Scout, AI, homeworld);
	ship = scrShip(Ship.Build, ConstructShip.Scout, AI, homeworld);
	ship = scrShip(Ship.Build, ConstructShip.ColonyShip, AI, homeworld);
	
	AI.image_blend = make_color_hsv(hue, 255, 255);
	hue += 20;
}

draw_set_font(font_0);
global.LastMouseX = 0;
global.LastMouseY = 0;