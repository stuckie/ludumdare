#ifndef _TRAP_DOOR_H_
#define _TRAP_DOOR_H_

#include "Entity.h"

#include <Resources/Resource.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <vector>

class TrapDoor : public Entity
{
	public:
		enum State
		{
			OPEN
		,	CLOSED
		};
		
		TrapDoor(const GLESGAE::Resources::Locator& mesh);
		~TrapDoor();
		
		void update(const float delta);
		void render();
		
		void setTimer(const float time) { mTimer = time; }
		State getState() const { return mState; }
		void setState(const State state);
		void setManual(const bool manual) { mManual = manual; }
		
	private:
		std::vector<GLESGAE::Resource<GLESGAE::Mesh> > mFrames;
		State mState;
		unsigned int mCurrentFrame;
		float mTimer;
		float mAnimationTime;
		bool mManual;
};

#endif

