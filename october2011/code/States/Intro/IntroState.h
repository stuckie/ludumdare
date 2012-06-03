#ifndef _INTRO_STATE_H_
#define _INTRO_STATE_H_

#include <States/State.h>

class b2Body;
class b2World;
class b2WheelJoint;
class IntroState : public GLESGAE::State
{
	public:
		//! Starts the state
		IntroState();
		
		//! Update the state
		bool update(const float deltaTime);
		
		//! Pulls down the state
		~IntroState();
		
	private:
		IntroState(const IntroState&);
		IntroState& operator=(const IntroState&);
		
		b2World* mWorld;
		b2Body* mBody;
		
		b2Body* m_wheel1;
		b2Body* m_wheel2;

		b2WheelJoint* m_spring1;
		b2WheelJoint* m_spring2;
};

#endif

