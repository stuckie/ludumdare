/// @description Setup defaults.. generally should be created from scrCreateSystemPlanet

enum SystemPlanetState
{	Setup
,	Idle
};

oHighlighted = false;
oSelected = false;
oState = SystemPlanetState.Setup;
oScanned = false;
oOwned = noone;

oPopulationTimer = 10 * room_speed;
oMineralTimer = room_speed;
oWaterTimer = room_speed;
oFoodTimer = room_speed;

alarm[0] = oPopulationTimer;
alarm[1] = oMineralTimer;
alarm[2] = oWaterTimer;
alarm[3] = oFoodTimer;