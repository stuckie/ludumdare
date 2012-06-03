#ifndef _FLOOR1_ROOMF_H_
#define _FLOOR1_ROOMF_H_

#include "../Room.h"
#include "Floor1RoomFCollisions.h"

class Floor1RoomF : public Room
{
	public:
		static GLESGAE::Resources::Id LeftSpikes;
		static GLESGAE::Resources::Id RightSpikes;
		
		Floor1RoomF();
		~Floor1RoomF();
		
		void update(const float delta);
		void render();
		void addEntity(const GLESGAE::Resource<Entity>& entity);
		void removeEntity(const GLESGAE::Resource<Entity>& entity);
};

#endif

