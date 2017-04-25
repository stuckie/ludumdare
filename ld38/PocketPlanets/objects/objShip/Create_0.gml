/// @description Setup defaults.. generally should be created from scrCreateSystemShip

enum SystemShipState
{	Setup
,	Idle
,	MovingTo
,	Combat
,	Orbit
};

oHighlighted = false;
oSelected = false;
oState = SystemShipState.Setup;

oSpeed = 1;
oTarget = undefined;
oTargetX = undefined;
oTargetY = undefined;

oOwnedBy = noone;

oUIOffsetX = sprite_width / 2;
oUIOffsetY = sprite_height / 2;

image_speed = 0;

oLaserFireTimer = 0.1 * room_speed;
oLaserFire = false;
oLaserOffsetX = 0;
oLaserOffsetY = 0;

oShields = 0;
oMaxShields = 0;
oHull = 0;
oMaxHull = 0;
oAttack = 0;

alarm[1] = room_speed;