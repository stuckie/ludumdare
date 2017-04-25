/// @description Stupidly quick "AI"

oScouts = 0;
oFighters = 0;
oDestroyers = 0;
oDreadnaughts = 0;
oColonyShips = 0;

for (var i = ds_list_size(oShips); i > 0; --i) {
	var ship = oShips[| i - 1];
	if (ship.oType == ConstructShip.Scout) {
		oScouts++;
		if (false == scrFindNearestUnseenPlanet(ship))
			scrFindNearestEnemy(ship);
	}
	else if (ship.oType == ConstructShip.Fighter) {
		oFighters++;
		scrFindNearestEnemy(ship);
	}
	else if (ship.oType == ConstructShip.Destroyer) {
		oDestroyers++;
		scrFindNearestEnemy(ship);
	}
	else if (ship.oType == ConstructShip.Dreadnaught) {
		oDreadnaughts++;
		scrFindNearestEnemy(ship);
	}
	else if (ship.oType == ConstructShip.ColonyShip) {
		oColonyShips++;
		scrFindNearestPlanet(ship);
	}
}

oShipTotal = oScouts + oFighters + oDestroyers + oDreadnaughts + oColonyShips;

oBuildingColonyShips = 0;
oBuildingFighters = 0;
oBuildingScouts = 0;
oBuildingDestroyers = 0;
oBuildingDreadnaughts = 0;

for (var i = ds_list_size(oPlanets); i > 0; --i) {
	var planet = oPlanets[| i - 1];
	if (planet.oAtmosphereState == Atmosphere.Ideal) {
		planet.oEcology = 72;
		planet.oDefense = 8;
		planet.oConstruction = 20;
	} else {
		planet.oEcology = 100;
		planet.oDefense = 0;
		planet.oConstruction = 0;
	}
	if (planet.oShipToConstruct == ConstructShip.Scout) ++oBuildingScouts;
	if (planet.oShipToConstruct == ConstructShip.ColonyShip) ++oBuildingColonyShips;
	if (planet.oShipToConstruct == ConstructShip.Fighter) ++oBuildingFighters;
	if (planet.oShipToConstruct == ConstructShip.Destroyer) ++oBuildingDestroyers;
	if (planet.oShipToConstruct == ConstructShip.Dreadnaught) ++oBuildingDreadnaughts;
	scrPickShipToConstruct(planet);
}