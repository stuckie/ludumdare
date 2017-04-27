/// @desc Planet megascript
/// @param Command enum of command to call
/// @param Planet|Stat instance of planet or Stat to check ( for Stats only )
/// @param Player|Select instance of player ( for Scan only ) or selection ( for Select)

var command = argument[0];
var _planet = argument[1];

enum Planet
{	Scan
,	Select
,	Destroy
,	Stats
,	Colonise
};

switch (command) {
	case Planet.Scan: {
		var _player = argument[2];

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
	};
	break;
	case Planet.Select: {
		var _select = argument[2];
		var list = oSelections;

		for (var i = ds_list_size(list); i > 0; --i) {
			if (_planet == list[| i - 1]) {
				if (false == _select) {
					ds_list_delete(list, i - 1);
					return false;
				} else
					return true; // already selected
			}
		}

		if (false == _select) return false;

		ds_list_add(list, _planet);

		if (true == instance_exists(objPlanetStats))
			instance_destroy(objPlanetStats);
		
		var inst = instance_create_layer(_planet.x + _planet.sprite_width, _planet.y - _planet.sprite_height, "UI", objPlanetStats);
		inst.oPlanet = _planet;

		return true;
	};
	break;
	case Planet.Destroy: {
		var owner = _planet.oOwnedBy;
		if (noone == owner) return;
		var planets = owner.oPlanets;

		for (var i = ds_list_size(planets); i > 0; --i) {
			var planet = planets[| i - 1];
			if (planet == _planet) {
				ds_list_delete(planets, i - 1);
				break;
			}
		}

		_planet.oOwnedBy = noone;
		_planet.oEcology = 0;
		_planet.oConstruction = 0;
		_planet.oDefense = 0;
		_planet.oShipToConstruct = ConstructShip.None;
		_planet.alarm[0] = -1;
		_planet.alarm[1] = -1;
		_planet.alarm[2] = -1;
		_planet.alarm[3] = -1;
		_planet.oPopulation = 0;
		_planet.oMaxPopulation = 0;
	};
	break;
	case Planet.Stats: {
		var stat = argument[1];
		if (stat == "oShipToConstruct") {
			oCurrentShipProgress = 0;
			oCurrentShipCost = scrShip(Ship.Cost, oShipToConstruct);
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
	};
	break;
	case Planet.Colonise: {
		var _player = argument[2];
		
		_planet.oOwnedBy = _player;
		_planet.oPopulation = 10;

		_planet.oEcology = 72;
		_planet.oDefense = 14;
		_planet.oConstruction = 14;

		ds_list_add(_player.oPlanets, _planet);
	};
	break;
};