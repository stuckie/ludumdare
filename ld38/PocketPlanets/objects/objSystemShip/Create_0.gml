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

oUIOffsetX = sprite_width / 2;
oUIOffsetY = sprite_height / 2;