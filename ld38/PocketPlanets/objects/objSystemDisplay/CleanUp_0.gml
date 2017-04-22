/// @description Tidy your room

for (var i = ds_list_size(oPlanets); i > 0; --i)
	instance_destroy(oPlanets[| i - 1]);
	
ds_list_destroy(oPlanets);

ds_list_destroy(oSelections);

for (var i = ds_list_size(oShips); i > 0; --i)
	instance_destroy(oShips[| i - 1]);
	
ds_list_destroy(oShips);

ds_map_destroy(oCamera);