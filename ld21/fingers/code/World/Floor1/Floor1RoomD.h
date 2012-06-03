#ifndef _FLOOR1_ROOMD_H_
#define _FLOOR1_ROOMD_H_

#include "../Room.h"
#include "Floor1RoomDCollisions.h"

class Floor1RoomD : public Room
{
	public:
		static GLESGAE::Resources::Id PressurePadBottomLeft;
		static GLESGAE::Resources::Id PressurePadBottomRight;
		static GLESGAE::Resources::Id PressurePadTopLeft;
		static GLESGAE::Resources::Id PressurePadTopRight;
		
		static GLESGAE::Resources::Id SpikesA1;
		static GLESGAE::Resources::Id SpikesB1;
		static GLESGAE::Resources::Id SpikesC1;
		static GLESGAE::Resources::Id SpikesD1;
		
		static GLESGAE::Resources::Id SpikesA2;
		static GLESGAE::Resources::Id SpikesB2;
		static GLESGAE::Resources::Id SpikesC2;
		static GLESGAE::Resources::Id SpikesD2;
		
		static GLESGAE::Resources::Id SpikesA3;
		static GLESGAE::Resources::Id SpikesB3;
		static GLESGAE::Resources::Id SpikesC3;
		static GLESGAE::Resources::Id SpikesD3;
		
		static GLESGAE::Resources::Id SpikesA4;
		static GLESGAE::Resources::Id SpikesB4;
		static GLESGAE::Resources::Id SpikesC4;
		static GLESGAE::Resources::Id SpikesD4;
		
		static void pushedPadBottomLeft();
		static void pushedPadBottomRight();
		static void pushedPadTopLeft();
		static void pushedPadTopRight();
		
		Floor1RoomD();
		~Floor1RoomD();
		
		void update(const float delta);
		void render();
		void addEntity(const GLESGAE::Resource<Entity>& entity);
		void removeEntity(const GLESGAE::Resource<Entity>& entity);
};

#endif

