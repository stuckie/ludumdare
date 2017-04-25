var _planet = argument[0];
var _owner = argument[1];

_planet.oOwnedBy = _owner;
_planet.oPopulation = 10;

_planet.oEcology = 70;
_planet.oDefense = 15;
_planet.oConstruction = 15;

ds_list_add(_owner.oPlanets, _planet);