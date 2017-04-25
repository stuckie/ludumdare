/// @description Defense

alarm[2] = oDefenseTimer;

if (0 == oDefense) return;

if (oShields == oMaxShields) oShields++;
oMaxShields++;

oAtmosphere += 1;