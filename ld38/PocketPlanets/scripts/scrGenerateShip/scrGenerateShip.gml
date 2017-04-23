// Ships come with a blueprint... of sorts.. need to at least pass in size
// Should be built by a ship factory, and then whatever modules the player has selected stuffed inside

var type = argument[0];
var components = ds_list_create();

var ship = ds_map_create();
ship[? "Name"] = "Ship " + string(random(10000));
ship[? "Type"] = type;

ship[? "X"] = 0;
ship[? "Y"] = 0;

return ship;