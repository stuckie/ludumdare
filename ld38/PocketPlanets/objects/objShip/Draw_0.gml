/// @description Draw

draw_self();

var alpha = draw_get_alpha();

if (true == oHighlighted) {
	draw_set_alpha(0.5);
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, false);
	draw_set_alpha(alpha);
}

if (SystemShipState.MovingTo == oState) {
	if ((undefined != oTarget)
	&& (true == instance_exists(oTarget)))
		draw_line_color(x, y, oTarget.x, oTarget.y, oOwnedBy.image_blend, oOwnedBy.image_blend);
	else if ((undefined != oTargetX) && (undefined != oTargetY))
		draw_line_color(x, y, oTargetX, oTargetY, oOwnedBy.image_blend, oOwnedBy.image_blend);
}
	
if (true == oSelected) {
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, true);
}

if (SystemShipState.Orbit == oState) {
}

if (SystemShipState.Combat == oState) {
	if ((undefined != oTarget)
	&& (true == instance_exists(oTarget))
	&& (true == oLaserFire))
		draw_line_color(x, y, oTarget.x + oLaserOffsetX, oTarget.y + oLaserOffsetY, c_red, c_red);
}

if (oShields < oMaxShields)
	draw_rectangle_color(x - 5, y + 5, x - 5 + (10 * (oShields / oMaxShields)), y + 7, c_aqua, c_aqua, c_aqua, c_aqua, false);
	
if (oHull < oMaxHull)
	draw_rectangle_color(x - 5, y + 8, x - 5 + (10 * (oHull / oMaxHull)), y + 10, c_red, c_red, c_red, c_red, false);
