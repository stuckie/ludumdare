/// Ship has finished building at planet, now to place it somewhere near the planet
// Probably want to also post a notification or something?

var _type = argument[0];
var _player = argument[1];
var _planet = argument[2];

var ship = scrGenerateShip(_type);

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
var iShip = scrCreateShip(ship, _player);
ds_list_add(_player.oShips, iShip);
ds_list_add(global.GameData.oShips, iShip);

return iShip;