/// @description Draw

draw_self();

var alpha = draw_get_alpha();
	
if (true == oHighlighted) {
	draw_set_alpha(0.5);
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, false);
	draw_set_alpha(alpha);
}

if (true == oSelected) {
	draw_rectangle_color(x - oUIOffsetX, y - oUIOffsetY, x + oUIOffsetX, y + oUIOffsetY, c_white, c_white, c_white, c_white, true);
	draw_set_alpha(0.75);
	draw_rectangle_color(x + sprite_width, y - sprite_height, x + sprite_width + 100.0, y - sprite_height + 200.0, c_dkgray, c_dkgray, c_dkgray, c_dkgray, false);
	draw_set_color(c_white);
	if (true == oScanned) {
		draw_text(x + sprite_width, y - sprite_height, " " + oPlanet[? "Name"]);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 2, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 35, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 68, y - sprite_height + 20);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 19, y - sprite_height + 54);
		draw_sprite(sprBuildingTemplate, 0, x + sprite_width + 52, y - sprite_height + 54);
		//draw_rectangle_color(x + sprite_width + 2, y - sprite_height + 90, x + sprite_width + 100, y - sprite_height + 91, c_yellow, c_yellow, c_yellow, c_yellow, false);
		draw_text(x + sprite_width, y - sprite_height + 90, " Minerals: " + string(oPlanet[? "Minerals"]));
		draw_text(x + sprite_width, y - sprite_height + 110, " Food: " + string(oPlanet[? "Food"]));
		draw_text(x + sprite_width, y - sprite_height + 130, " Water: " + string(oPlanet[? "Water"]));
		draw_text(x + sprite_width, y - sprite_height + 150, " Pop.: " + string(oPlanet[? "Population"]) + "Bil.");
	} else {
		draw_text(x + sprite_width, y - sprite_height, " Unknown");
		//draw_rectangle_color(x + sprite_width + 2, y - sprite_height + 90, x + sprite_width + 100, y - sprite_height + 91, c_yellow, c_yellow, c_yellow, c_yellow, false);
		draw_text(x + sprite_width, y - sprite_height + 90, " Minerals: ???");
		draw_text(x + sprite_width, y - sprite_height + 110, " Food: ???");
		draw_text(x + sprite_width, y - sprite_height + 130, " Water: ???");
		draw_text(x + sprite_width, y - sprite_height + 150, " Pop.: 0");
	}
	draw_set_alpha(alpha);
}

if (oSystem.id == oOwned) {
	draw_sprite(sprPlanetOwned, 0, x, y);
}