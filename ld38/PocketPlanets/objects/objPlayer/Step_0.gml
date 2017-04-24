/// @description 

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
			if (undefined == ship) continue;
			with (ship) {
				var isSelected = place_meeting(x, y, objSelection);
				ship.oHighlighted = isSelected;
			}
			ship.oSelected = scrSelectDisplayShip(ship.id, isSelected);
		}
		
		for (var i = ds_list_size(oPlanets); i > 0; --i) {
			var planet = oPlanets[| i - 1];
			if (undefined == planet) continue;
			with (planet) {
				var isSelected = place_meeting(x, y, objSelection);
				planet.oHighlighted = isSelected;
			}
			planet.oSelected = scrSelectDisplayPlanet(planet.id, isSelected);
		}
	}
}

if (true == mouse_check_button_released(mb_left)) {
	if (true == instance_exists(objSelection)) {
		instance_destroy(oSelectionObject);
		
		for (var i = ds_list_size(oShips); i > 0; --i) {
			var ship = oShips[| i - 1];
			if (ship == undefined) continue;
			ship.oHighlighted = false;
		}
		
		for (var i = ds_list_size(oPlanets); i > 0; --i) {
			var planet = oPlanets[| i - 1];
			if (planet == undefined) continue;
			planet.oHighlighted = false;
		}
	}
}

if (true == mouse_check_button_released(mb_right)) {
	for (var i = ds_list_size(oSelections); i > 0; --i) {
		var selected = oSelections[| i - 1];
		if (objShip == selected.object_index) {
			var inst = instance_position(mouse_x, mouse_y, objPlanet);
			if (noone != inst) {
				selected.oTarget = inst;
				selected.oState = SystemShipState.MovingTo;
				selected.oSelected = scrSelectDisplayShip(selected, false);
			} else {
				selected.oTargetX = mouse_x;
				selected.oTargetY = mouse_y;
				selected.oState = SystemShipState.MovingTo;
				selected.oSelected = scrSelectDisplayShip(selected, false);
			}
		}
	}
}