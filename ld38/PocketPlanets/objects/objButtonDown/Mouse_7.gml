var value = variable_instance_get(oPlanet, oValue);
	if (value > 0) {
	variable_instance_set(oPlanet, oValue, --value);

	var thisVal = oValue;
	with (oPlanet) scrPlanet(Planet.Stats, thisVal);
}