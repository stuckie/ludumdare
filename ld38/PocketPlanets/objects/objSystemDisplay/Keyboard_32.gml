/// @description Right Click Scroll

/*if (0 == ds_list_size(oSelections))*/ { // only if there's no selections...
	var camId = oCamera[? "id"];
	var camX = oCamera[? "x"];
	var camY = oCamera[? "y"];
	var lastX = oCamera[? "mX"];
	var lastY = oCamera[? "mY"];
	
	camX += (lastX - mouse_x);
	camY += (lastY - mouse_y);
	
	camera_set_view_pos(camId, camX, camY);
	
	oCamera[? "mX"] = mouse_x;
	oCamera[? "mY"] = mouse_y;
	oCamera[? "x"] = camX;
	oCamera[? "y"] = camY;
	
	draw_sprite(sprShip, 0, mouse_x, mouse_y);
}