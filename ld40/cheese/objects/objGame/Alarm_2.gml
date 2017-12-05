/// @description MORE TRAPS!

var pickupLayerId = layer_get_id("Traps");
var objectsLayerId = layer_get_id("Objects");
var objectsMapId = layer_tilemap_get_id("Objects");
var _w = tilemap_get_width(objectsMapId);
var _h = tilemap_get_height(objectsMapId);

var canPlace = false;
var _x = irandom(_w);
var _y = irandom(_h);
while (false == canPlace) {	
	var tile = tilemap_get(objectsMapId, _x, _y);
	if (0 == tile_get_index(tile)) {
		if (noone == instance_position(_x * 32, _y * 32, objTrap)) {
			canPlace = true;
			break;
		}
	}
	
	_x = random(_w);
	_y = random(_h);
}

instance_create_layer(_x * 32, _y * 32, pickupLayerId, objTrap);
alarm[2] = 2 * room_speed;