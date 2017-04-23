/// @description Check for splash skip

if ((true == keyboard_check_released(vk_anykey))
|| (true == mouse_check_button_released(mb_any)))
	alarm[0] = 1;