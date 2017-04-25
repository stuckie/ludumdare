var _ship = argument[0];

if (_ship.oState != SystemShipState.Idle) return false;

var gameShips = global.GameData.oShips;
for (var i = ds_list_size(gameShips); i > 0; --i) {
	var iShip = gameShips[| i - 1];
	if (iShip.oOwnedBy != id) {
		_ship.oTarget = iShip;
		_ship.oState = SystemShipState.MovingTo;
		return true;
	}
}

var planet = undefined;
for (var j = ds_list_size(oSeenPlanets); j > 0; --j) {
	var jPlanet = oSeenPlanets[| j - 1];
		
	if ((jPlanet.oOwnedBy != noone)
	&& (jPlanet.oOwnedBy != id)) {
		_ship.oTarget = jPlanet;
		_ship.oState = SystemShipState.MovingTo;
		return true;
	}
}

return false;