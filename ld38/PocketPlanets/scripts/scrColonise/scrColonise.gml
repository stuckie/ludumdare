var _planet = argument[0];
var _owner = argument[1];

_planet.oOwnedBy = _owner;
_planet.oPopulation = 10;

_planet.oEcology = 34;
_planet.oDefense = 33;
_planet.oConstruction = 33;

ds_list_add(_owner.oPlanets, _planet);