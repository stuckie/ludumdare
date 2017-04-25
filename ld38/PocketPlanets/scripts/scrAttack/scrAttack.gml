if ((undefined == oTarget)
|| (false == instance_exists(oTarget)))
	return;
	
var hasHit = irandom(100);
if (hasHit > 50) {
	oLaserOffsetX = 0;
	oLaserOffsetY = 0;
	
	if (oTarget.oShields <= 0)
		oTarget.oHull -= oAttack;
	else
		oTarget.oShields -= oAttack;
} else {
	oLaserOffsetX = irandom(16);
	oLaserOffsetY = irandom(16);
}

if (0 >= oTarget.oHull) {
	if (object_index == objShip)
		oState = SystemShipState.Idle;
	if (oTarget.object_index == objPlanet) {
		oTarget.oPopulation = 0;
		oTarget.oAtmosphere += 10;
		oTarget.oHull = oTarget.oMaxHull;
		oTarget.oOwnedBy = noone;
	}
	oTarget = undefined;
}