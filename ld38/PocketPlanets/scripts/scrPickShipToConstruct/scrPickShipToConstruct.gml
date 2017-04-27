// favour colony ships if we still have places to explore

var planet = argument[0];

if (planet.oShipToConstruct == ConstructShip.None) {
	planet.oCurrentShipProgress = 0;
	if (oColonyShips + oBuildingColonyShips < oMaxColonyShips && ds_list_size(oPlanets) < ds_list_size(oSeenPlanets)) {
		planet.oShipToConstruct = ConstructShip.ColonyShip;
		planet.oCurrentShipCost = scrShip(Ship.Cost, ConstructShip.ColonyShip);
	}else if (oScouts + oBuildingScouts < oMaxScouts) {
		planet.oShipToConstruct = ConstructShip.Scout;
		planet.oCurrentShipCost = scrShip(Ship.Cost, ConstructShip.Scout);
	}else if (oFighters + oBuildingFighters < oMaxFighters){
		planet.oShipToConstruct = ConstructShip.Fighter;
		planet.oCurrentShipCost = scrShip(Ship.Cost, ConstructShip.Fighter);
	}else if (oDestroyers + oBuildingDestroyers < oMaxDestroyers){
		planet.oShipToConstruct = ConstructShip.Destroyer;
		planet.oCurrentShipCost = scrShip(Ship.Cost, ConstructShip.Destroyer);
	}else if (oDreadnaughts + oBuildingDreadnaughts < oMaxDreadnaughts){
		planet.oShipToConstruct = ConstructShip.Dreadnaught;
		planet.oCurrentShipCost = scrShip(Ship.Cost, ConstructShip.Dreadnaught);
	}
}