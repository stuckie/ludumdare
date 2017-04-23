draw_self();

if (true == oHighlighted) {
	var alpha = draw_get_alpha();
	draw_set_alpha(0.5);
	draw_rectangle_color(x, y, x + sprite_width, y + sprite_height, c_white, c_white, c_white, c_white, false);
	draw_set_alpha(alpha);
}