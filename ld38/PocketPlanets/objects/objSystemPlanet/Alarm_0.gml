/// @description Population Increase

oPlanet[? "Population"] += 1;
oPlanet[? "Food"] -= oPlanet[? "Population"];
oPlanet[? "Water"] -= oPlanet[? "Population"];

alarm[0] = oPopulationTimer;