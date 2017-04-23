draw_self();

draw_set_color(c_white);
draw_sprite(oPlanet.sprite_index, oPlanet.image_index, x + 20, y + 20);
draw_text(x + 69, y + 0, string(oPlanet.oPopulation) + "M");
draw_text(x + 125, y + 0, string(oPlanet.oMaxPopulation) + "M");
draw_text(x + 90, y + 27, string(oPlanet.oConstruction));
draw_text(x + 90, y + 41, string(oPlanet.oDefense));
draw_text(x + 90, y + 55, string(oPlanet.oEcology));		

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