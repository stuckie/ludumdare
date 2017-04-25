var _planet = argument[0];

var owner = _planet.oOwnedBy;
if (noone == owner) return;
var planets = owner.oPlanets;

for (var i = ds_list_size(planets); i > 0; --i) {
	var planet = planets[| i - 1];
	if (planet == _planet) {
		ds_list_delete(planets, i - 1);
		break;
	}
}

_planet.oOwnedBy = noone;
_planet.oEcology = 0;
_planet.oConstruction = 0;
_planet.oDefense = 0;
_planet.oShipToConstruct = ConstructShip.None;
_planet.alarm[0] = -1;
_planet.alarm[1] = -1;
_planet.alarm[2] = -1;
_planet.alarm[3] = -1;
_planet.oPopulation = 0;
_planet.oMaxPopulation = 0;