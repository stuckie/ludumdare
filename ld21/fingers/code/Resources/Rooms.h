#ifndef _ROOMS_H_
#define _ROOMS_H_

#include <Resources/Resource.h>

namespace Fingers
{
	namespace Rooms
	{
		extern GLESGAE::Resources::Id		Bank;
		extern GLESGAE::Resources::Type		Type;
		
		extern unsigned int Floor1Id;
		namespace Floor1
		{
			extern GLESGAE::Resources::Group	Group;
		
			extern GLESGAE::Resources::Id		StartingRoom;
			extern GLESGAE::Resources::Id		RoomA;
			extern GLESGAE::Resources::Id		RoomB;
			extern GLESGAE::Resources::Id		RoomC;
			extern GLESGAE::Resources::Id		RoomD;
			extern GLESGAE::Resources::Id		RoomE;
			extern GLESGAE::Resources::Id		RoomF;
			extern GLESGAE::Resources::Id		RoomG;
		}

		extern unsigned int Floor2Id;	
		namespace Floor2
		{
			extern GLESGAE::Resources::Group	Group;
		
			extern GLESGAE::Resources::Id		RoomA;
			extern GLESGAE::Resources::Id		RoomB;
			extern GLESGAE::Resources::Id		RoomC;
			extern GLESGAE::Resources::Id		RoomD;
			extern GLESGAE::Resources::Id		RoomE;
			extern GLESGAE::Resources::Id		RoomF;
			extern GLESGAE::Resources::Id		RoomG;
		}

		extern unsigned int Floor3Id;	
		namespace Floor3
		{
			extern GLESGAE::Resources::Group	Group;
		
			extern GLESGAE::Resources::Id		RoomA;
			extern GLESGAE::Resources::Id		RoomB;
			extern GLESGAE::Resources::Id		RoomC;
			extern GLESGAE::Resources::Id		RoomD;
			extern GLESGAE::Resources::Id		RoomE;
			extern GLESGAE::Resources::Id		RoomF;
			extern GLESGAE::Resources::Id		RoomG;
			extern GLESGAE::Resources::Id		RoomH;
			extern GLESGAE::Resources::Id		Vault;
		}
	}
}

/// Layout:
/*
	Floor 1
	A		B		C
	D				E
	F	Starting	G
	
	Floor 2
	A		B		C
	D
	E		F		G
	
	Floor 3
	A		B		C
	D		Vault	H
	E		F		G
*/


#endif

