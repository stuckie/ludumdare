#ifndef _CRUSHER_H_
#define _CRUSHER_H_

#include "Entity.h"

#include <Resources/Resource.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <vector>

class Crusher : public Entity
{
	public:
		enum Direction
		{
			LEFT
		,	RIGHT
		,	UP
		,	DOWN
		,	STOP
		};
		
		Crusher(const GLESGAE::Resources::Locator& mesh);
		~Crusher();
		
		void update(const float delta);
		void render();
		
		void setSpeed(const float speed) { mSpeed = speed; }
		void swapDirection();
		void setDirection(const Direction direction) { mDirection = direction; }
		float getSpeed() const { return mSpeed; }
		
	private:
		GLESGAE::Resource<GLESGAE::Mesh> mArmMesh;
		Direction mDirection;
		float mSpeed;
};

#endif

