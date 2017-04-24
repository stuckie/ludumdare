/// @description Step

switch (oState) {
	case SystemShipState.Setup: {
		oType = oShip[? "Type"];
		image_index = oType - 1;
		oSpeed = 1 / oType;
		
		oUIOffsetX = sprite_width / 2;
		oUIOffsetY = sprite_height / 2;
	};
	break;
	case SystemShipState.Idle: {
	};
	break;
	case SystemShipState.MovingTo: {
		if (undefined != oTarget) {
			move_towards_point(oTarget.x, oTarget.y, oSpeed);
			image_angle = point_direction(x, y, oTarget.x, oTarget.y);
			if (oTarget.sprite_width > point_distance(x, y, oTarget.x, oTarget.y)) {
				speed = 0;
				if (objPlanet == oTarget.object_index)
					oState = SystemShipState.Orbit;
				else
					oState = SystemShipState.Idle;
			}
		} else if ((undefined != oTargetX) && (undefined != oTargetY)) {
			move_towards_point(oTargetX, oTargetY, oSpeed);
			image_angle = point_direction(x, y, oTargetX, oTargetY);
			if (oSpeed > point_distance(x, y, oTargetX, oTargetY)) {
				speed = 0;
				oState = SystemShipState.Idle;
			}
		}
	};
	break;
	case SystemShipState.Orbit: {
		switch (oType) {
			case ConstructShip.Scout: {
				if ((undefined != oTarget)
				&& (objPlanet == oTarget.object_index)) {
					scrScanPlanet(oOwnedBy, oTarget);
				}
			};
			break;
			case ConstructShip.ColonyShip: {
				if ((undefined != oTarget)
				&& (objPlanet == oTarget.object_index)) {
					scrScanPlanet(oOwnedBy, oTarget);
					if (noone == oTarget.oOwnedBy) {
						scrColonise(oTarget, oOwnedBy);
						scrDestroyShip(id);
					}
				}
			};
			break;
		};
	};
	break;
	case SystemShipState.Combat: {
	};
	break;
};