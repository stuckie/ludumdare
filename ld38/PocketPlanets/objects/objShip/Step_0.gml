/// @description Step

switch (oState) {
	case SystemShipState.Setup: {
		oType = oShip[? "Type"];
		image_index = oType - 1;
		oSpeed = 1 / oType;
		
		image_blend = oOwnedBy.image_blend;
		
		oUIOffsetX = sprite_width / 2;
		oUIOffsetY = sprite_height / 2;
		
		switch (oType) {
			case ConstructShip.Scout: {
				oMaxShields = 5; oShields = 5;
				oMaxHull = 10; oHull = 10;
				oAttack = 1;
			};
			break;
			case ConstructShip.Fighter: {
				oMaxShields = 10; oShields = 10;
				oMaxHull = 20; oHull = 20;
				oAttack = 2;
			};
			break;
			case ConstructShip.Destroyer: {
				oMaxShields = 20; oShields = 20;
				oMaxHull = 20; oHull = 40;
				oAttack = 4;
			};
			break;
			case ConstructShip.Dreadnaught: {
				oMaxShields = 40; oShields = 40;
				oMaxHull = 80; oHull = 80;
				oAttack = 8;
			};
			break;
			case ConstructShip.ColonyShip: {
				oMaxShields = 50; oShields = 50;
				oMaxHull = 100; oHull = 100;
				oAttack = 1;
			};
			break;
		};
		
		oState = SystemShipState.Idle;
	};
	break;
	case SystemShipState.Idle: {
		oTarget = undefined;
		oTargetX = undefined;
		oTargetY = undefined;
	};
	break;
	case SystemShipState.MovingTo: {
		if ((undefined != oTarget)
		&& (true == instance_exists(oTarget))) {
			move_towards_point(oTarget.x, oTarget.y, oSpeed);
			image_angle = point_direction(x, y, oTarget.x, oTarget.y);
			var distance = oTarget.sprite_width;
			if (objShip == oTarget.object_index) distance = 32;
			if (distance > abs(point_distance(x, y, oTarget.x, oTarget.y))) {
				speed = 0;
				if (objPlanet == oTarget.object_index)
					oState = SystemShipState.Orbit;
				else {
					if (objShip == oTarget.object_index) {
						if ((oTarget.oOwnedBy != oOwnedBy)
						&& (oTarget.oOwnedBy != noone))
							oState = SystemShipState.Combat;
							oTarget.oState = SystemShipState.Combat;
							oTarget.oTarget = id;
						}
					else
						oState = SystemShipState.Idle;
				}
			}
		} else if ((undefined != oTargetX) && (undefined != oTargetY)) {
			move_towards_point(oTargetX, oTargetY, oSpeed);
			image_angle = point_direction(x, y, oTargetX, oTargetY);
			if (oSpeed > point_distance(x, y, oTargetX, oTargetY)) {
				speed = 0;
				oState = SystemShipState.Idle;
			}
		} else
			oState = SystemShipState.Idle;
	};
	break;
	case SystemShipState.Orbit: {
		switch (oType) {
			case ConstructShip.Scout: {
				if ((undefined != oTarget)
				&& (objPlanet == oTarget.object_index)) {
					scrPlanet(Planet.Scan, oTarget, oOwnedBy);
					oTarget = undefined;
				}
				oState = SystemShipState.Idle;
			};
			break;
			case ConstructShip.Fighter:
			case ConstructShip.Destroyer:
			case ConstructShip.Dreadnaught: {
				oState = SystemShipState.Combat;
				if ((oTarget.oOwnedBy != oOwnedBy)
				&& (oTarget.oOwnedBy != noone)) {
					oState = SystemShipState.Combat;
					oTarget.oState = SystemShipState.Combat;
					oTarget.oTarget = id;
				}
			};
			break;
			case ConstructShip.ColonyShip: {
				if ((undefined != oTarget)
				&& (objPlanet == oTarget.object_index)) {
					scrPlanet(Planet.Scan, oTarget, oOwnedBy)
					if (noone == oTarget.oOwnedBy) {
						scrPlanet(Planet.Colonise, oTarget, oOwnedBy);
						scrShip(Ship.Destroy, id);
					}
				}
			};
			break;
		};
	};
	break;
	case SystemShipState.Combat: {
		if ((undefined != oTarget)
		&& (true == instance_exists(oTarget))) {
			if (0 > alarm[0]) alarm[0] = oLaserFireTimer;
			var dist = point_distance(x, y, oTarget.x, oTarget.y);
			if (64 < abs(dist)) {
				oState = SystemShipState.MovingTo;
			}
		} else
			oState = SystemShipState.Idle;
	};
	break;
};

if (0 >= oHull) scrShip(Ship.Destroy, id);
