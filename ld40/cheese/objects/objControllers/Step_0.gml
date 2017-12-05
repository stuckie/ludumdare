/// @description Update all controllers

for (var i = 0; i < global.MaxControllers; ++i) {
	var controller = global.Controllers[@ i];
	switch (controller[Controller.Type]) {
		case ControllerType.AI: { 
		};
		break;
		case ControllerType.Keyboard: {
			controller[@ Controller.Left] = keyboard_check(vk_left) ? true : false;
			controller[@ Controller.Right] = keyboard_check(vk_right) ? true : false;
			controller[@ Controller.Up] = keyboard_check(vk_up) ? true : false;
			controller[@ Controller.Down] = keyboard_check(vk_down) ? true : false;
			controller[@ Controller.Action] = (keyboard_check(vk_space) || keyboard_check(vk_return)) ? true : false;
			controller[@ Controller.Pause] = keyboard_check(vk_escape) ? true : false;			
		};
		break;
		case ControllerType.Joypad: {
			var padId = controller[Controller.Id];
			controller[@ Controller.Left] = gamepad_button_check(padId, gp_padl);
			controller[@ Controller.Right] = gamepad_button_check(padId, gp_padr);
			controller[@ Controller.Up] = gamepad_button_check(padId, gp_padu);
			controller[@ Controller.Down] = gamepad_button_check(padId, gp_padd);
			controller[@ Controller.Action] = gamepad_button_check(padId, gp_face1);
			controller[@ Controller.Pause] = gamepad_button_check(padId, gp_start);
			
			var deadzone = gamepad_get_axis_deadzone(padId);
			controller[@ Controller.Left] = (gamepad_axis_value(padId, gp_axislh) < -deadzone) ? true : false;
			controller[@ Controller.Right] = (gamepad_axis_value(padId, gp_axislh) > deadzone) ? true : false;
			controller[@ Controller.Up] = (gamepad_axis_value(padId, gp_axislv) < -deadzone) ? true : false;
			controller[@ Controller.Down] = (gamepad_axis_value(padId, gp_axislv) > deadzone) ? true : false;
		};
		break;
	}
};