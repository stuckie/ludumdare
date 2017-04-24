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
		draw_line_color(x, y, oTarget.x, oTarget.y, c_green, c_green);
	else
		draw_line_color(x, y, oTargetX, oTargetY, c_green, c_green);
}
	
if (true == oSelected) {
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, true);
}

if (SystemShipState.Orbit == oState) {
}