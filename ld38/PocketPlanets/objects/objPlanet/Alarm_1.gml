/// @description Ecology

alarm[1] = oEcologyTimer;

if (0 == oEcology) return;

if (oAtmosphere < 50) oAtmosphere += 1;
else if (oAtmosphere > 50) oAtmosphere -= 1;

