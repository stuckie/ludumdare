/// @description General Game Logic

if (true == mouse_check_button_pressed(mb_right)) {
	if (false == instance_exists(objCameraScroll))
		instance_create_layer(0, 0, "Controllers", objCameraScroll);
}

if (true == mouse_check_button_released(mb_right)) {
	if (true == instance_exists(objCameraScroll))
		instance_destroy(objCameraScroll);
}

if (os_browser != browser_not_a_browser)
&& ((view_wport[0] != display_get_width())
&& (view_hport[0] != display_get_height())) {
	window_set_size(display_get_width(), display_get_height());
	view_wport[0] = display_get_width();
	view_hport[0] = display_get_height();
	camera_set_view_size(view_camera[0], display_get_width(), display_get_height());
}