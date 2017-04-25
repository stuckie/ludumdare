draw_self();

draw_set_color(c_white);
draw_sprite(oPlanet.sprite_index, oPlanet.image_index, x + 20, y + 20);
draw_text(x + 69, y - 1, string(oPlanet.oPopulation) + "M");
draw_text(x + 125, y - 1, string(floor(oPlanet.oMaxPopulation)) + "M");
draw_text(x + 90, y + 26, string(oPlanet.oConstruction));
draw_text(x + 90, y + 40, string(oPlanet.oDefense));
draw_text(x + 90, y + 54, string(oPlanet.oEcology));		

var shipToConstruct = "";
switch (oPlanet.oShipToConstruct) {
	case ConstructShip.None: shipToConstruct = "None"; break;
	case ConstructShip.Scout: shipToConstruct = "Scout"; break;
	case ConstructShip.Fighter: shipToConstruct = "Fighter"; break;
	case ConstructShip.Destroyer: shipToConstruct = "Destroyer"; break;
	case ConstructShip.Dreadnaught: shipToConstruct = "Dreadnaught"; break;
	case ConstructShip.ColonyShip: shipToConstruct = "Colony Ship"; break;
};

draw_text(x + 94, y + 83, shipToConstruct);
draw_text(x + 90, y + 68, string(oPlanet.oMaxShields));

draw_rectangle_color(x + 70 + oPlanet.oAtmosphere - 1, y + 15, x + 70 + oPlanet.oAtmosphere + 1, y + 23, c_white, c_white, c_white, c_white, false);
draw_rectangle_color(x + 4, y + 88, x + 4 + (30 * (oPlanet.oCurrentShipProgress/oPlanet.oCurrentShipCost)), y + 93, c_white, c_white, c_white, c_white, false);
