// Generate a random planet structure

enum PlanetType
{	Green
,	Desert
,	Volcanic
,	Rocky
,	MAX_TYPE
};

enum PlanetSize
{	Tiny
,	Small
,	Medium
,	Large
,	Massive
,	MAX_SIZE
};

var type = irandom(PlanetType.MAX_TYPE - 1);
var size = irandom(PlanetSize.MAX_SIZE - 1);

/*
	Planet {
		Sprite sprite
		Name string.. use random name thingy?
		Icon image_index
		Size PlanetSize
		Type PlanetType
		Mineral int - generate per tick
		Food int - generate per tick
		Water int - generate per tick
		Space - Grid - size dependent
		X - x position in system
		Y - y position in system 
	}
*/

// For now, lets just have all planets shown at the same size...

var planet = ds_map_create();

switch (size) {
	case PlanetSize.Tiny: {
		planet[? "Sprite"] = sprTinyPlanets;
		planet[? "Space"] = ds_grid_create(1, 1);
	};
	break;
	case PlanetSize.Small: {
		planet[? "Sprite"] = sprTinyPlanets;// sprSmallPlanets;
		planet[? "Space"] = ds_grid_create(2, 2);
	};
	break;
	case PlanetSize.Medium: {
		planet[? "Sprite"] = sprTinyPlanets;// sprMediumPlanets;
		planet[? "Space"] = ds_grid_create(3, 3);
	};
	break;
	case PlanetSize.Large: {
		planet[? "Sprite"] = sprTinyPlanets;// sprLargePlanets;
		planet[? "Space"] = ds_grid_create(4, 4);
	};
	break;
	case PlanetSize.Massive: {
		planet[? "Sprite"] = sprTinyPlanets;// sprMassivePlanets;
		planet[? "Space"] = ds_grid_create(5, 5);
	};
	break;
};

switch (type) {
	case PlanetType.Green: {
		planet[? "Icon"] = 0;
		planet[? "Water"] = 100 + ((irandom(100) * 10) * size);
		planet[? "Minerals"] = 50 + ((irandom(100) * 10) * size);
		planet[? "Food"] = 50 + ((irandom(100) * 10) * size);
	};
	break;
	case PlanetType.Rocky: {
		planet[? "Icon"] = 1;
		planet[? "Water"] = 10 + ((irandom(100) * 10) * size);
		planet[? "Minerals"] = 100 + ((irandom(100) * 10) * size);
		planet[? "Food"] = 10 + ((irandom(100) * 10) * size);
	};
	break;
	case PlanetType.Volcanic: {
		planet[? "Icon"] = 2;
		planet[? "Water"] = 0 + ((irandom(100) * 10) * size);
		planet[? "Minerals"] = 200 + ((irandom(100) * 10) * size);
		planet[? "Food"] = 0 + ((irandom(100) * 10) * size);
	};
	break;
	case PlanetType.Desert: {
		planet[? "Icon"] = 3;
		planet[? "Water"] = 10 + ((irandom(100) * 10) * size);
		planet[? "Minerals"] = 100 + ((irandom(100) * 10) * size);
		planet[? "Food"] = 50 + ((irandom(100) * 10) * size);
	};
	break;
};

planet[? "Type"] = type;
planet[? "Size"] = size;
planet[? "X"] = irandom(room_width);
planet[? "Y"] = irandom(room_height);
planet[? "Name"] = "Planet " + string(random(10000));
planet[? "Population"] = 0;
planet[? "Scanned"] = false;
planet[? "Owned"] = noone;

return planet;