/// @desc Ship megascript
/// @param Command enum to perform
/// @param Type|Ship type of ship to build (Build, Cost Only), chosen Ship instance (Select, Destroy Only)
/// @param Player|Select player to bind to ship (Build Only), select choice for this ship (Select Only)
/// @param Planet planet to build ship on (Build Only)

enum Ship
{	Build
,	Select
,	Cost
,	Destroy
};

var command = argument[0];

switch (command) {
	case Ship.Build: {
		var _type = argument[1];
		var _player = argument[2];
		var _planet = argument[3];

		var ship = scrGenerate(Generate.Ship, _type);

		var _angle = 0;
		var _x = -sin(degtorad(_angle));
		var _y = cos(degtorad(_angle));
		var _offset = 32;
		while (false == position_empty(_planet.x + (_x * _offset), _planet.y + (_y * _offset))) {
			_angle += 45;
			_x = sin(degtorad(_angle));
			_y = cos(degtorad(_angle));
	
			if (_angle >= 360) {
				_angle = 0;
				_offset += 16;
			}
		}
		ship[? "X"] = _planet.x + (_x * _offset);
		ship[? "Y"] = _planet.y + (_y * _offset);
		ds_list_add(global.GalaxyData[? "Ships"], ship);
		var iShip = scrCreate(Create.Ship, ship, _player);
		ds_list_add(_player.oShips, iShip);
		ds_list_add(global.GameData.oShips, iShip);

		return iShip;
	};
	break;
	case Ship.Select: {
		var ship = argument[1];
		var select = argument[2];

		var list = oSelections;

		for (var i = ds_list_size(list); i > 0; --i) {
			if (ship == list[| i - 1]) {
				if (false == select) {
					ds_list_delete(list, i - 1);
					return false;
				} else
					return true; // already selected
			}
		}

		if (false == select) return false;

		ds_list_add(list, ship);
		return true;
	};
	break;
	case Ship.Cost: {
		var type = argument[1];

		switch (type) {
			case ConstructShip.None: return 0;
			case ConstructShip.Scout: return 3;
			case ConstructShip.Fighter: return 5;
			case ConstructShip.Destroyer: return 10;
			case ConstructShip.Dreadnaught: return 12;
			case ConstructShip.ColonyShip: return 8;
		};
	};
	break;
	case Ship.Destroy: {
		var _ship = argument[1];

		var owner = _ship.oOwnedBy;
		var ships = owner.oShips;

		for (var i = ds_list_size(ships); i > 0; --i) {
			var ship = ships[| i - 1];
			if (ship == _ship) {
				ds_list_delete(ships, i - 1);
				break;
			}
		}

		ships = global.GameData.oShips;
		for (var i = ds_list_size(ships); i > 0; --i) {
			var ship = ships[| i - 1];
			if (ship == _ship) {
				ds_list_delete(ships, i - 1);
				break;
			}
		}

		instance_destroy(_ship);
	};
	break;
};