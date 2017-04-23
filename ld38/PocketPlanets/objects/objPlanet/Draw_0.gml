/// @description Draw Planet

draw_self();
	
if (true == oHighlighted) {
	var alpha = draw_get_alpha();
	draw_set_alpha(0.5);
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, false);
	draw_set_alpha(alpha);
}

if (true == oSelected) {
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, true);
}

if (oGame.oPlayer == oOwnedBy) {
	draw_sprite(sprPlanetOwned, 0, x, y);
}