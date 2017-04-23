// Generate a random planet structure

var _x = argument[0];
var _y = argument[1];

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