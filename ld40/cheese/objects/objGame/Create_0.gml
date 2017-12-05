/// @description Init game variables

enum GameState
{	CountDown
,	GamePlay
,	Paused
,	Results
};

mState = GameState.CountDown;

mCountDown = 3;
alarm[0] = room_speed;

for (var i = global.Players; i < global.MaxControllers; ++i) {
	var controller = global.Controllers[@ i];
	controller[@ Controller.Type] = ControllerType.AI;
}

var _mx = 0;
var _my = 0;
if (rmKitchen == room) {
	_mx = 208;
	_my = 48;
}

for (var i = 0; i < global.MaxControllers; ++i) {
	var mouse = instance_create_layer(_mx + (i * 32), _my, "Cats_And_Mice", objMouse);
	mouse.mId = i;
}