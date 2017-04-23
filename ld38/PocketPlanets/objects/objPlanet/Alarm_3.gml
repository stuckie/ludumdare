/// @description Construction

var timer = room_speed * (oConstruction / 100);

oConstructionTimer = room_speed * timer;

alarm[3] = oConstructionTimer;

if (0 == oConstruction) return;

