/// @description Population

oPopulation += 1;
if (Atmosphere.Ideal == oAtmosphereState) oPopulation += 1;
else if (Atmosphere.Taxing == oAtmosphereState) oPopulation -= 1;
else if (Atmosphere.Extreme == oAtmosphereState) oPopulation -= 2;

var timer = room_speed - (room_speed * (oEcology / 100));

oPopulationTimer = room_speed * timer;

alarm[0] = oPopulationTimer;

show_debug_message("Pop! :" + string(oPopulation));