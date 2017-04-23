/// @description General Game Logic

if (true == mouse_check_button_pressed(mb_right)) {
	if (false == instance_exists(objCameraScroll))
		instance_create_layer(0, 0, "Controllers", objCameraScroll);
}

if (true == mouse_check_button_released(mb_right)) {
	if (true == instance_exists(objCameraScroll))
		instance_destroy(objCameraScroll);
}