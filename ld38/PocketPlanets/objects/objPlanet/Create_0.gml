oEcology = 0;
oDefense = 0;
oConstruction = 0;
oPopulation = 0;
oMaxPopulation = 100;
oAtmosphere = irandom(100);
oPlayerSeen = false;
oOwnedBy = noone;
oShipToConstruct = ConstructShip.Scout;

image_speed = 0;

enum Atmosphere
{	Uninhabitable
,	Extreme
,	Taxing
,	Average
,	Ideal
};

oAtmosphereState = Atmosphere.Uninhabitable;

// 45 - 55 - ideal  +1 Pop
// 30 - 45/55 - 70 - Average
// 20 - 30/70 - 80 - Taxing -1 Pop
// 10 - 20/80 - 90 - Extreme -2 Pop
// 0 - 10/90 - 99 - Unhabitable

if (oAtmosphere < 10) {
	image_index = 0; // uninhabitable - dead world/asteroid
	oAtmosphereState = Atmosphere.Uninhabitable;
} else if ((oAtmosphere > 9) && (oAtmosphere < 20)) {
	image_index = 1; // too cold - extreme
	oAtmosphereState = Atmosphere.Extreme;
} else if ((oAtmosphere > 19) && (oAtmosphere < 30)) {
	image_index = 2; // cold - taxing
	oAtmosphereState = Atmosphere.Taxing;
} else if ((oAtmosphere > 29) && (oAtmosphere < 45)) {
	image_index = 3; // average
	oAtmosphereState = Atmosphere.Average;
} else if ((oAtmosphere > 44) && (oAtmosphere < 55)) { 
	image_index = 4;
	oAtmosphereState = Atmosphere.Ideal;
} else if ((oAtmosphere > 54) && (oAtmosphere < 70)) {
	image_index = 3; // average
	oAtmosphereState = Atmosphere.Average;
} else if ((oAtmosphere > 69) && (oAtmosphere < 80)) {
	image_index = 5; // hot - taxing
	oAtmosphereState = Atmosphere.Taxing;
} else if ((oAtmosphere > 79) && (oAtmosphere < 90)) {
	image_index = 6; // too hot - extreme
	oAtmosphereState = Atmosphere.Extreme;
} else if (oAtmosphere > 89) {
	image_index = 0; // uninhabitable - dead world/asteroid
	oAtmosphereState = Atmosphere.Uninhabitable;
}

if (false == oPlayerSeen) image_index = 7;

oEcologyTimer = room_speed * room_speed; // 1 minute
oDefenseTimer = room_speed * room_speed;
oConstructionTimer = room_speed * room_speed;
oPopulationTimer = room_speed * room_speed;

alarm[0] = oPopulationTimer;
alarm[1] = oEcologyTimer;
alarm[2] = oDefenseTimer;
alarm[3] = oConstructionTimer;

oHighlighted = false;
oSelected = false;

oUIOffsetX = sprite_width / 2;
oUIOffsetY = sprite_height / 2;