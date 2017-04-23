if (false == oSetup) {
	oConstructionUp = instance_create_layer(x + 125, y + 28, "UI", objButtonUp);
	oConstructionDown = instance_create_layer(x + 69, y + 28, "UI", objButtonDown);

	oEcologyUp = instance_create_layer(x + 125, y + 56, "UI", objButtonUp);
	oEcologyDown = instance_create_layer(x + 69, y + 56, "UI", objButtonDown);

	oDefenseUp = instance_create_layer(x + 125, y + 42, "UI", objButtonUp);
	oDefenseDown = instance_create_layer(x + 69, y + 42, "UI", objButtonDown);

	oShipUp = instance_create_layer(x + 175, y + 84, "UI", objButtonUp);
	oShipDown = instance_create_layer(x + 69, y + 84, "UI", objButtonDown);
	
	oClose = instance_create_layer(x + 181, y, "UI", objButtonClose);
	
	oConstructionUp.oPlanet = oPlanet;
	oConstructionUp.oValue = "oConstruction";
	
	oConstructionDown.oPlanet = oPlanet;
	oConstructionDown.oValue = "oConstruction";

	oEcologyUp.oPlanet = oPlanet;
	oEcologyUp.oValue = "oEcology";
	
	oEcologyDown.oPlanet = oPlanet;
	oEcologyDown.oValue = "oEcology";

	oDefenseUp.oPlanet = oPlanet;
	oDefenseUp.oValue = "oDefense";
	
	oDefenseDown.oPlanet = oPlanet;
	oDefenseDown.oValue = "oDefense";
	
	oShipUp.oPlanet = oPlanet;
	oShipUp.oValue = "oShipToConstruct";
	
	oShipDown.oPlanet = oPlanet;
	oShipDown.oValue = "oShipToConstruct";

	oSetup = true;
}