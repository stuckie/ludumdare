// By default, lets give the player 3 ships; 2 scouts and 1 colony ship, like MOO!
oShipTotal = 3;
oScouts = 2;
oFighters = 0;
oDestroyers = 0;
oDreadnaughts = 0;
oColonyShips = 1;

// Player has their homeworld to start with.
oPlanetTotal = 1;

oPlanets = ds_list_create(); // list of planets owned by this player
oShips = ds_list_create(); // list of ships owned by this player

oSelectionObject = undefined;
oSelections = ds_list_create();