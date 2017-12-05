/// @description Create the structs for the Controllers

enum Controller
{	Left	= 0
,	Right	= 1
,	Up		= 2
,	Down	= 3
,	Action	= 4
,	Pause	= 5

,	Type	= 6
,	Id		= 7
};

enum ControllerType
{	AI = -1
,	Keyboard = 0
,	Joypad = 1
};

global.Controller_AI = -1;
global.Controllers = [];
global.Players = 1; // players take the first n controller slots
global.MaxControllers = 8;

for (var i = 0; i < global.MaxControllers; ++i) {
	var controller = [];
	controller[Controller.Left] = false;
	controller[Controller.Right] = false;
	controller[Controller.Up] = false;
	controller[Controller.Down] = false;
	controller[Controller.Action] = false;
	controller[Controller.Pause] = false;
	controller[Controller.Type] = ControllerType.Keyboard;
	controller[Controller.Id] = i;
	global.Controllers[i] = controller;
}
