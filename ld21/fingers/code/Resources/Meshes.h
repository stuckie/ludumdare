#ifndef _MESHES_H_
#define _MESHES_H_

#include <Resources/Resource.h>

namespace Fingers
{
	namespace Meshes
	{
		extern GLESGAE::Resources::Group	Bank;
	}

	namespace PlayerMeshes
	{
		extern GLESGAE::Resources::Group	Group;
		
		extern GLESGAE::Resources::Id		Heart;
		
		namespace Frames {
			extern GLESGAE::Resources::Id 	Static;
			
			extern GLESGAE::Resources::Id	Walk1;
			extern GLESGAE::Resources::Id	Walk2;
			
			extern GLESGAE::Resources::Id	Hurt;
			
			extern GLESGAE::Resources::Id	Death;
		}
	}
	
	namespace CollectableMeshes
	{
		extern GLESGAE::Resources::Group	Group;
		
		extern GLESGAE::Resources::Id		Gems;
		extern GLESGAE::Resources::Id		Health;
	}
	
	namespace PushableMeshes
	{
		extern GLESGAE::Resources::Group	Group;
		
		extern GLESGAE::Resources::Id		Mirror;
		extern GLESGAE::Resources::Id		Weight;
		extern GLESGAE::Resources::Id		StarDiamond;
	}
	
	namespace TrapMeshes
	{
		extern GLESGAE::Resources::Group	Group;
		
		extern GLESGAE::Resources::Id		PressurePadDown;
		extern GLESGAE::Resources::Id		PressurePadUp;
		extern GLESGAE::Resources::Id		SpikesDown;
		extern GLESGAE::Resources::Id		SpikesUp;
		extern GLESGAE::Resources::Id		CameraBox;
		extern GLESGAE::Resources::Id		CameraSight;
		extern GLESGAE::Resources::Id		ArrowBox;
		extern GLESGAE::Resources::Id		Arrow;
		extern GLESGAE::Resources::Id		CrusherHead;
		extern GLESGAE::Resources::Id		CrusherArm;
		extern GLESGAE::Resources::Id		TrapDoorClosed;
		extern GLESGAE::Resources::Id		TrapDoorOpen;
		extern GLESGAE::Resources::Id		MovableWall;
		extern GLESGAE::Resources::Id		LaserBox;
		extern GLESGAE::Resources::Id		Laser;
	}
	
	namespace RoomMeshes
	{
		extern GLESGAE::Resources::Group	Group;
		
		namespace Background {
			extern GLESGAE::Resources::Id	Floor;
		}
		
		namespace Collidables {
			extern GLESGAE::Resources::Id	BlockWall;
			extern GLESGAE::Resources::Id	StairWell;
			extern GLESGAE::Resources::Id	Door;
			extern GLESGAE::Resources::Id	ExitDoor;
		}
	}
	
	namespace FontMeshes
	{
		extern GLESGAE::Resources::Group	Group;
		
		extern GLESGAE::Resources::Id		Standard;
		extern GLESGAE::Resources::Id		Complete;
		extern GLESGAE::Resources::Id		Lost;
	}
}

#endif

