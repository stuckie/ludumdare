var planet = argument[0];
var select = argument[1];

var list = oSelections;

for (var i = ds_list_size(list); i > 0; --i) {
	if (planet == list[| i - 1]) {
		if (false == select) {
			ds_list_delete(list, i - 1);
			return false;
		} else
			return true; // already selected
	}
}

if (false == select) return false;

ds_list_add(list, planet);

if (true == instance_exists(objPlanetStats))
	instance_destroy(objPlanetStats);
		
var inst = instance_create_layer(planet.x + planet.sprite_width, planet.y - planet.sprite_height, "UI", objPlanetStats);
inst.oPlanet = planet;

return true;