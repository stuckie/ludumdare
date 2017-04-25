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
} else {
	if (noone != oOwnedBy) {
		draw_sprite_ext(sprPlanetEnemy, 0, x, y, 1.0, 1.0, 0.0, oOwnedBy.image_blend, 1.0);
	}
}

if (oShields < oMaxShields)
	draw_rectangle_color(x - 5, y + 5, x - 5 + (10 * (oShields / oMaxShields)), y + 7, c_aqua, c_aqua, c_aqua, c_aqua, false);
	
if (oHull < oMaxHull)
	draw_rectangle_color(x - 5, y + 8, x - 5 + (10 * (oHull / oMaxHull)), y + 10, c_red, c_red, c_red, c_red, false);
