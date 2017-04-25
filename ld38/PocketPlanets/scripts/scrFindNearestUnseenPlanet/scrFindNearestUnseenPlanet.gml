var _ship = argument[0];

if (_ship.oState != SystemShipState.Idle) return false;

var gamePlanets = global.GameData.oPlanets;
if (ds_list_size(gamePlanets) == ds_list_size(oSeenPlanets)) return false;
var planet = undefined;
for (var i = ds_list_size(gamePlanets); i > 0; --i) {
	var iPlanet = gamePlanets[| i - 1];
	var seen = false;
	for (var j = ds_list_size(oSeenPlanets); j > 0; --j) {
		var jPlanet = oSeenPlanets[| j - 1];
		
		if (iPlanet == jPlanet) {
			seen = true;
			break;
		}
	}
	if (false == seen) {
		planet = iPlanet;
		break;
	}
}

_ship.oTarget = planet;
_ship.oState = SystemShipState.MovingTo;
ds_list_add(oSeenPlanets, planet); // we'll assume we'll get there...

return true;