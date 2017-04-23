/// @description Draw

draw_self();

var alpha = draw_get_alpha();

if (true == oHighlighted) {
	draw_set_alpha(0.5);
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, false);
	draw_set_alpha(alpha);
}

if (SystemShipState.MovingTo == oState) {
	if (undefined != oTarget)
		draw_line_color(x, y, oTarget.x, oTarget.y, c_red, c_red);
	else
		draw_line_color(x, y, oTargetX, oTargetY, c_red, c_red);
}
	
if (true == oSelected) {
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, true);
	draw_set_alpha(0.75);
	draw_rectangle_color(x + sprite_width, y - sprite_height, x + sprite_width + 100.0, y - sprite_height + 100.0, c_dkgray, c_dkgray, c_dkgray, c_dkgray, false);
	draw_set_color(c_white);
	if ((SystemShipState.Idle == oState)
	|| (SystemShipState.MovingTo == oState)) {
		draw_text(x + sprite_width, y - sprite_height, " " + oShip[? "Name"]);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 2, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 35, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 68, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 19, y - sprite_height + 54);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 52, y - sprite_height + 54);
	}
	if (SystemShipState.Orbit == oState) {
		draw_text(x + sprite_width, y - sprite_height, " " + oShip[? "Name"]);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 2, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 35, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 68, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 19, y - sprite_height + 54);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 52, y - sprite_height + 54);
	}
	draw_set_alpha(alpha);
}
