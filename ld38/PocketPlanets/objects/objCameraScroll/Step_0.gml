/// @description Check Right Down

if (true == mouse_check_button(mb_right)) {	
	if (true == oFirstCheck) oFirstCheck = false;
	else {
		global.MouseX += (global.LastMouseX - window_mouse_get_x());
		global.MouseY += (global.LastMouseY - window_mouse_get_y());
		
		camera_set_view_pos(camId, global.MouseX, global.MouseY);
	}
	
	global.LastMouseX = window_mouse_get_x();
	global.LastMouseY = window_mouse_get_y();
}
