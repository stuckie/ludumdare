#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

#include <Resources/Resource.h>
#include <Graphics/Camera.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <Input/Controller.h>
#include <vector>

class Player : public Entity
{
	public:
		enum State
		{
			WALKING
		,	STANDING
		,	HURT
		,	DEAD
		};
		
		Player(const GLESGAE::Resources::Locator& mesh);
		~Player();
		
		void update(const float delta);
		void render();
		
		void modifyHealth(const int health);
		void addGem() { ++mGems; }
		
		void setPosition(const GLESGAE::Vector2& position);
		
	private:
		std::vector<GLESGAE::Resource<GLESGAE::Mesh> > mFrames;
		State mState;
		GLESGAE::Controller::Id mPointerId;
		GLESGAE::Controller::Id mKeyboardId;
		int mHealth;
		int mGems;
		GLESGAE::Vector2 mWalkStart;
		GLESGAE::Resource<GLESGAE::Camera> mCamera;
		unsigned int mCurrentFrame;
		float mAnimationTime;
		GLESGAE::Resource<GLESGAE::Matrix4> mIconTransform;
};

#endif

