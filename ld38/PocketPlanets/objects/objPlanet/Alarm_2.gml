/// @description Defense

var timer = room_speed * (oDefense / 100);

oDefenseTimer = room_speed * timer;

alarm[2] = oDefenseTimer;

if (0 == oDefense) return;
