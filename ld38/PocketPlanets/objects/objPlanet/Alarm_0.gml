/// @description Population

if (oPopulation < floor(oMaxPopulation)) {
	oPopulation += 1;
	if (Atmosphere.Ideal == oAtmosphereState) oPopulation += 1;
	else if (Atmosphere.Taxing == oAtmosphereState) oPopulation -= 1;
	else if (Atmosphere.Extreme == oAtmosphereState) oPopulation -= 2;
	else if (Atmosphere.Uninhabitable == oAtmosphereState) oPopulation -= 3;
}

if ((0 == oHull) || (0 == oPopulation)) scrPlanet(Planet.Destroy, id);

if (Atmosphere.Ideal == oAtmosphereState) {
	oMaxPopulation += 1;
}

alarm[0] = oPopulationTimer;