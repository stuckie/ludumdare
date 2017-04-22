/// @description Frame Logic..

if (true == mouse_check_button_pressed(mb_right)) {
	oCamera[? "mX"] = display_mouse_get_x();
	oCamera[? "mY"] = display_mouse_get_y();
}

if (true == mouse_check_button(mb_right)) {
	if (false == oHighlighted) { // Make sure we're not hovering over something
		var camId = oCamera[? "id"];
		var camX = oCamera[? "x"];
		var camY = oCamera[? "y"];
		var lastX = oCamera[? "mX"];
		var lastY = oCamera[? "mY"];
	
		camX += (lastX - display_mouse_get_x());
		camY += (lastY - display_mouse_get_y());
	
		camera_set_view_pos(camId, camX, camY);
	
		oCamera[? "mX"] = display_mouse_get_x();
		oCamera[? "mY"] = display_mouse_get_y();
		oCamera[? "x"] = camX;
		oCamera[? "y"] = camY;
	}
}

if (true == mouse_check_button_released(mb_right)) {
	if (1 == ds_list_size(oSelections)) {
		var selected = oSelections[| 0];
		if (objSystemPlanet == selected.object_index) {
			var ship = scrGenerateShip(ShipSize.Tiny);
			ship[? "X"] = mouse_x;
			ship[? "Y"] = mouse_y;
			ds_list_add(oSystem[? "Ships"], ship);
			var iShip = scrCreateSystemShip(ship);
			iShip.oSystem = id;
			ds_list_add(oShips, iShip);
		}
	}
		
	for (var i = ds_list_size(oSelections); i > 0; --i) {
		var selected = oSelections[| i - 1];
		if (objSystemShip == selected.object_index) {
			var inst = instance_position(mouse_x, mouse_y, objSystemViewObject);
			if (noone != inst) {
				selected.oTarget = inst;
				selected.oState = SystemShipState.MovingTo;
				selected.oSelected = scrSelectDisplayShip(selected, false);
			}
		}
	}
}

if (true == mouse_check_button_pressed(mb_left)) {
	if (false == instance_exists(objSelection))
		oSelectionObject = instance_create_layer(mouse_x, mouse_y, "UI", objSelection);
}

if (true == mouse_check_button(mb_left)) {
	if (true == instance_exists(objSelection)) {
		oSelectionObject.image_xscale = mouse_x - oSelectionObject.x;
		oSelectionObject.image_yscale = mouse_y - oSelectionObject.y;
			
		for (var i = ds_list_size(oShips); i > 0; --i) {
			var ship = oShips[| i - 1];
			with (ship) {
				var isSelected = place_meeting(x, y, objSelection);
				ship.oHighlighted = isSelected;
				ship.oSelected = scrSelectDisplayShip(id, isSelected);
			}
		}
		
		for (var i = ds_list_size(oPlanets); i > 0; --i) {
			var planet = oPlanets[| i - 1];
			with (planet) {
				var isSelected = place_meeting(x, y, objSelection);
				planet.oHighlighted = isSelected;
				planet.oSelected = scrSelectDisplayPlanet(id, isSelected);
			}
		}
	}
}

if (true == mouse_check_button_released(mb_left)) {
	if (true == instance_exists(objSelection)) {
		instance_destroy(oSelectionObject);
		
		for (var i = ds_list_size(oShips); i > 0; --i) {
			var ship = oShips[| i - 1];
			ship.oHighlighted = false;
		}
		
		for (var i = ds_list_size(oPlanets); i > 0; --i) {
			var planet = oPlanets[| i - 1];
			planet.oHighlighted = false;
		}
	}
}