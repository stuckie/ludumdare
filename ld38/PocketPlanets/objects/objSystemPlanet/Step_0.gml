/// @description Step

switch (oState) {
	case SystemPlanetState.Setup: {
		sprite_index = oPlanet[? "Sprite"];
		image_index = oPlanet[? "Icon"];
		
		oUIOffsetX = sprite_width / 2;
		oUIOffsetY = sprite_height / 2;
		
		oScanned = oPlanet[? "Scanned"];
		oOwned = oPlanet[? "Owned"];
	};
	break;
	case SystemPlanetState.Idle: {
	};
	break;
};