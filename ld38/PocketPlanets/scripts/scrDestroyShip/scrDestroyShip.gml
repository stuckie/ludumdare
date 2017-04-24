var _ship = argument[0];

var owner = _ship.oOwnedBy;
var ships = owner.oShips;

for (var i = ds_list_size(ships); i > 0; --i) {
	var ship = ships[| i - 1];
	if (ship == _ship) {
		ds_list_delete(ships, i - 1);
		break;
	}
}

instance_destroy(_ship);