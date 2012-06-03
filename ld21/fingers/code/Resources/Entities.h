#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#include <Resources/Resource.h>

namespace Fingers
{
	namespace Entities
	{
		extern GLESGAE::Resources::Id Bank;
		extern GLESGAE::Resources::Group Group;
		extern GLESGAE::Resources::Type Type;
		
		typedef unsigned int Tag;
		
		extern Tag Player;
		
		extern Tag Gem;
		extern Tag StarDiamond;
		extern Tag Health;
		
		extern Tag Mirror;
		extern Tag Weight;
		
		extern Tag PressurePad;
		extern Tag TrapDoor;
		extern Tag MovableWall;
		extern Tag Crusher;
		extern Tag Camera;
		extern Tag Laser;
		extern Tag Spikes;
		extern Tag Arrow;
		
		extern Tag Background;
		extern Tag Wall;
		extern Tag DoorNorth;
		extern Tag DoorSouth;
		extern Tag DoorEast;
		extern Tag DoorWest;
		extern Tag ExitDoor;
		extern Tag Stairs;
	}
}

#endif

