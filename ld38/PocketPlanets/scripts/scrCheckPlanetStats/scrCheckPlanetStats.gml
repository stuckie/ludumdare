var stat = argument[0];
if (stat == "oShipToConstruct") {
	oCurrentShipProgress = 0;
	oCurrentShipCost = scrShipCost(oShipToConstruct);
}

if (oEcology + oDefense + oConstruction > 100) {
	if (stat == "oDefense") {
		if (oEcology > oConstruction) --oEcology;
		else --oConstruction;
	} else if (stat == "oConstruction") {
		if (oEcology > oDefense) --oEcology;
		else --oDefense;
	} else {
		if (oConstruction > oDefense) --oConstruction;
		else --oDefense;
	}
}

oPopulationTimer = room_speed * 10;
if (0 == alarm[0] || alarm[0] > oPopulationTimer) alarm[0] = oPopulationTimer;

oEcologyTimer = 1 + room_speed * (5 * (1 - (oEcology / 100)));
if (0 == alarm[1] || alarm[1] > oEcologyTimer) alarm[1] = oEcologyTimer;

oDefenseTimer = 1 + room_speed * (5 * (1 - (oDefense / 100)));
if (0 == alarm[2] || alarm[2] > oDefenseTimer) alarm[2] = oDefenseTimer;

oConstructionTimer = 1 + room_speed * (5 * (1 - (oConstruction / 100)));
if (0 == alarm[3] || alarm[3] > oConstructionTimer) alarm[3] = oConstructionTimer;