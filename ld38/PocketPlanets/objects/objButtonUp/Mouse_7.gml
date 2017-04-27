var val = variable_instance_get(oPlanet, oValue);
if (val < 100) {
	variable_instance_set(oPlanet, oValue, ++val);

	var thisVal = oValue;
	with (oPlanet) scrPlanet(Planet.Stats, thisVal);
}