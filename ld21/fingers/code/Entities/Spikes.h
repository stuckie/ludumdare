#ifndef _SPIKES_H_
#define _SPIKES_H_

#include "Entity.h"

#include <Resources/Resource.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <vector>

class Spikes : public Entity
{
	public:
		enum State
		{
			UP
		,	DOWN
		};
		
		Spikes(const GLESGAE::Resources::Locator& mesh);
		~Spikes();
		
		void update(const float delta);
		void render();
		
		void setTimer(const float time) { mTimer = time; }
		State getState() const { return mState; }
		void setState(const State state);
		void setManual(const bool manual) { mManual = manual; }
		void setDownTimer(const float timer);
		void toggle();
		
	private:
		std::vector<GLESGAE::Resource<GLESGAE::Mesh> > mFrames;
		State mState;
		unsigned int mCurrentFrame;
		float mTimer;
		float mAnimationTime;
		bool mManual;
		bool mAutoDown;
};

#endif

