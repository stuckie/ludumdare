var type = argument[0];

switch (type) {
	case ConstructShip.None: return 0;
	case ConstructShip.Scout: return 3;
	case ConstructShip.Fighter: return 5;
	case ConstructShip.Destroyer: return 10;
	case ConstructShip.Dreadnaught: return 12;
	case ConstructShip.ColonyShip: return 8;
};