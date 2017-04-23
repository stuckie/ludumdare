var _player = argument[0];
var _planet = argument[1];

if (_player.object_index == objPlayer) {
	_planet.oPlayerSeen = true;
}

with (_planet) {
	if (oAtmosphere < 10) {
		image_index = 0; // uninhabitable - dead world/asteroid
	} else if ((oAtmosphere > 9) && (oAtmosphere < 20)) {
		image_index = 1; // too cold - extreme
	} else if ((oAtmosphere > 19) && (oAtmosphere < 30)) {
		image_index = 2; // cold - taxing
	} else if ((oAtmosphere > 29) && (oAtmosphere < 45)) {
		image_index = 3; // average
	} else if ((oAtmosphere > 44) && (oAtmosphere < 55)) { 
		image_index = 4;
	} else if ((oAtmosphere > 54) && (oAtmosphere < 70)) {
		image_index = 3; // average
	} else if ((oAtmosphere > 69) && (oAtmosphere < 80)) {
		image_index = 5; // hot - taxing
	} else if ((oAtmosphere > 79) && (oAtmosphere < 90)) {
		image_index = 6; // too hot - extreme
	} else if (oAtmosphere > 89) {
		image_index = 0; // uninhabitable - dead world/asteroid
	}

	if (false == oPlayerSeen) image_index = 7;
}