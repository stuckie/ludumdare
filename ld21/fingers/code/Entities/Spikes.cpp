#include "Spikes.h"

#include "../Resources/Entities.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Mesh.h>
#include <Maths/Matrix3.h>
#include <Maths/Matrix4.h>
#include <Time/Clock.h>
#include <cstdlib>
#include "../Resources/Meshes.h"
#include "../Resources/Camera.h"

using namespace GLESGAE;

Spikes::Spikes(const GLESGAE::Resources::Locator& mesh)
: Entity(mesh, Entity::RENDER_BOX_COLLIDE, Fingers::Entities::Spikes)
, mFrames()
, mState(DOWN)
, mCurrentFrame(0U)
, mTimer(1.0F + ((rand() % 100) * 0.01F))
, mAnimationTime(2.0F)
, mManual(false)
, mAutoDown(false)
{	
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());

	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesDown));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp));
	
	mMesh = mFrames[mCurrentFrame];
	
	setSphereSize(0.25F);
	setBoxSize(Vector2(0.2F, 0.2F));
}

Spikes::~Spikes()
{
}

void Spikes::setState(const State state)
{
	switch (state) {
		case UP:
			mCurrentFrame = 1U;
			mState = UP;
			break;
		case DOWN:
			mCurrentFrame = 0U;
			mState = DOWN;
			break;
		default:
			break;
	};

	mMesh = mFrames[mCurrentFrame];
}

void Spikes::setDownTimer(const float timer)
{
	mAutoDown = true;
	setState(DOWN);
	mAnimationTime = timer;
	mManual = false;
}

void Spikes::toggle()
{
	switch (mState) {
		case UP:
			setState(DOWN);
			break;
		case DOWN:
			setState(UP);
			break;
		default:
			break;
	};
}

void Spikes::update(const float delta)
{
	if (false == mManual) {
		mAnimationTime -= delta;
	
		if (mAnimationTime < 0.0F) {
			mAnimationTime = mTimer;
			if (true == mAutoDown) {
				mManual = true;
				setState(UP);
				mAutoDown = false;
			}
			else {
				switch (mState) {
					case UP:
						setState(DOWN);
						break;
					case DOWN:
						setState(UP);
						break;
					default:
						break;
				};
			}
		}
	}
}

void Spikes::render()
{
	Application* application(Application::getInstance());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	
	graphicsSystem->drawMesh(mMesh, mTransform);
}

