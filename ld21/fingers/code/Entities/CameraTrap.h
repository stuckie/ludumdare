#ifndef _CAMERA_TRAP_H_
#define _CAMERA_TRAP_H_

#include "Entity.h"

#include <Resources/Resource.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <vector>

class CameraTrap : public Entity
{
	public:
		enum State
		{
			TURN_CW
		,	TURN_CCW
		,	STOP
		};
		
		struct Command
		{
			State state;
			float speed;
			float width;
			float duration;
			
			Command(const State state, const float speed, const float width, const float duration)
			: state(state), speed(speed), width(width), duration(duration) {}
		};
		
		CameraTrap(const GLESGAE::Resources::Locator& mesh);
		~CameraTrap();
		
		void update(const float delta);
		void render();
		
		void setPath(const std::vector<Command>& path) { mPath = path; }
		void setPosition(const GLESGAE::Vector2& position) { mPosition = position; }
		
	private:
		std::vector<Command> mPath;
		State mState;
		unsigned int mCurrentFrame;
		float mTimer;
		float mAnimationTime;
		GLESGAE::Vector2 mPosition;
};

#endif

