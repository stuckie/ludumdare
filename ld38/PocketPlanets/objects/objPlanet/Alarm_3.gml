/// @description Construction

alarm[3] = oConstructionTimer;

if (0 == oConstruction) return;

if (ConstructShip.None == oShipToConstruct) return;
if (oCurrentShipCost > oCurrentShipProgress) ++oCurrentShipProgress;
if (oCurrentShipCost == oCurrentShipProgress) {
	oCurrentShipProgress = 0;
	scrBuildShip(oShipToConstruct, oOwnedBy, id);
	if (oOwnedBy.object_index == objPlayer)
		oCurrentShipCost = scrShipCost(oShipToConstruct);
	else oShipToConstruct = ConstructShip.None;
}

oAtmosphere += 1;