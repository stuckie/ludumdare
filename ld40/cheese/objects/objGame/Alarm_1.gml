/// @description MORE CHEESE!

var pickupLayerId = layer_get_id("Pickups");
var objectsLayerId = layer_get_id("Objects");
var objectsMapId = layer_tilemap_get_id("Objects");
var _w = tilemap_get_width(objectsMapId);
var _h = tilemap_get_height(objectsMapId);
var _ww = tilemap_get_tile_width(objectsMapId);
var _hh = tilemap_get_tile_height(objectsMapId);

var canPlace = false;
var _x = irandom(_w);
var _y = irandom(_h);
while (false == canPlace) {	
	var tile = tilemap_get(objectsMapId, _x, _y);
	if (0 == tile_get_index(tile)) {
		if (noone == instance_position((_x * _ww) + 8, (_y * _hh) + 8, objCheese)) {
			canPlace = true;
			break;
		}
	}
	
	_x = random(_w);
	_y = random(_h);
}

instance_create_layer((_x * _ww) + 8, (_y * _hh) + 8, pickupLayerId, objCheese);
alarm[1] = room_speed;
