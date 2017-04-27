if (ConstructShip.ColonyShip < oShipToConstruct) oShipToConstruct = ConstructShip.None;
else if (ConstructShip.None > oShipToConstruct) oShipToConstruct = ConstructShip.ColonyShip;

if (oAtmosphere > 100) oAtmosphere = 100;
if (oAtmosphere < 0) oAtmosphere = 0;

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

if (oOwnedBy != noone) {
	if (oAtmosphereState == Atmosphere.Taxing) oPopulation -= 0.01;
	if (oAtmosphereState == Atmosphere.Extreme) oPopulation -= 0.05;
	if (oAtmosphereState == Atmosphere.Uninhabitable) oPopulation -= 0.1;
}

if (0 >= oPopulation) scrPlanet(Planet.Destroy, id);