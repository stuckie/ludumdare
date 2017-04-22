/// @description Step

switch (oState) {
	case SystemShipState.Setup: {
		sprite_index = oShip[? "Sprite"];
		image_index = oShip[? "Icon"];
		
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