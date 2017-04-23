/// @description Ecology

var timer = room_speed * (oEcology / 100);

oEcologyTimer = room_speed * timer;

alarm[1] = oEcologyTimer;

if (0 == oEcology) return;

if (oAtmosphere < 50) oAtmosphere += 1;
else if (oAtmosphere > 50) oAtmosphere -= 1;

