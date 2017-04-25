var _ship = argument[0];

if (_ship.oState != SystemShipState.Idle) return false;

var planet = undefined;
for (var j = ds_list_size(oSeenPlanets); j > 0; --j) {
	var jPlanet = oSeenPlanets[| j - 1];
		
	if (jPlanet.oOwnedBy == noone) {
		planet = jPlanet;
		break;
	}
}

if (undefined == planet) return false;

_ship.oTarget = planet;
_ship.oState = SystemShipState.MovingTo;

return true;