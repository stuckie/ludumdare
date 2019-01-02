#include "CameraTrap.h"

#include "../Resources/Entities.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Mesh.h>
#include <Maths/Matrix3.h>
#include <Maths/Matrix4.h>
#include <Time/Clock.h>
#include <cmath>
#include "../Resources/Meshes.h"
#include "../Resources/Camera.h"

using namespace GLESGAE;

CameraTrap::CameraTrap(const GLESGAE::Resources::Locator& mesh)
: Entity(mesh, Entity::RENDER_BOX_COLLIDE, Fingers::Entities::Camera)
, mPath()
, mCurrentFrame(0U)
, mTimer(0.0F)
, mAnimationTime(2.0F)
, mPosition()
{
	mPath.push_back(Command(STOP, 0.0F, 0.0F, 0.0F));
}

CameraTrap::~CameraTrap()
{
}

void CameraTrap::update(const float delta)
{
	mAnimationTime -= delta;
	
	if (mAnimationTime < 0.0F) {
		++mCurrentFrame;
		if (mCurrentFrame >= mPath.size())
			mCurrentFrame = 0U;
			
		mAnimationTime = mPath[mCurrentFrame].duration;
	}
	
	switch (mPath[mCurrentFrame].state) {
		case TURN_CW: {
				mTimer += delta;
				Vector3 position;
				mTransform->getPosition(&position);
				position.x() = mPosition.x() + (sinf(mTimer * mPath[mCurrentFrame].speed) * mPath[mCurrentFrame].width);
				position.y() = mPosition.y() - (cosf(mTimer * mPath[mCurrentFrame].speed) * mPath[mCurrentFrame].width);
				mTransform->setPosition(position);
			};
			break;
		case TURN_CCW: {
				mTimer += delta;
				Vector3 position;
				mTransform->getPosition(&position);
				position.x() = mPosition.x() - (cosf(mTimer * mPath[mCurrentFrame].speed) * mPath[mCurrentFrame].width);
				position.y() = mPosition.y() + (sinf(mTimer * mPath[mCurrentFrame].speed) * mPath[mCurrentFrame].width);
				mTransform->setPosition(position);
			};
			break;
		case STOP:
		default:
			break;
	};
}

void CameraTrap::render()
{
	Application* application(Application::getInstance());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	
	graphicsSystem->drawMesh(mMesh, mTransform);
}

