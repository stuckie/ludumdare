/// @description Step

switch (oState) {
	case SystemShipState.Setup: {
		image_index = oShip[? "Type"] - 1;
		oSpeed = 1 / oShip[? "Type"];
		
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
				if (objSystemPlanet == oTarget.object_index)
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
	};
	break;
	case SystemShipState.Combat: {
	};
	break;
};