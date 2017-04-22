var planet = argument[0];
var select = argument[1];

var system = planet.oSystem;
var list = system.oSelections;

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
return true;