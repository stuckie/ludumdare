#ifndef _PRESSURE_PAD_H_
#define _PRESSURE_PAD_H_

#include "Entity.h"

#include <Resources/Resource.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <vector>

class PressurePad : public Entity
{
	public:
		enum State
		{
			UP
		,	DOWN
		};
		
		PressurePad(const GLESGAE::Resources::Locator& mesh);
		~PressurePad();
		
		void update(const float delta);
		void render();
		
		State getState() const { return mState; }
		void setDown();
		void setUp();
		
	private:
		std::vector<GLESGAE::Resource<GLESGAE::Mesh> > mFrames;
		State mState;
};

#endif

