#include "TrapDoor.h"

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

TrapDoor::TrapDoor(const GLESGAE::Resources::Locator& mesh)
: Entity(mesh, Entity::RENDER_BOX_COLLIDE, Fingers::Entities::TrapDoor)
, mFrames()
, mState(CLOSED)
, mCurrentFrame(0U)
, mTimer(1.0F + ((rand() % 100) * 0.01F))
, mAnimationTime(2.0F)
, mManual(false)
{	
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());

	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::TrapMeshes::Group, Fingers::TrapMeshes::TrapDoorClosed));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::TrapMeshes::Group, Fingers::TrapMeshes::TrapDoorOpen));
	
	mMesh = mFrames[mCurrentFrame];
	
	setSphereSize(0.25F);
	setBoxSize(Vector2(0.2F, 0.2F));
}

TrapDoor::~TrapDoor()
{
}

void TrapDoor::setState(const State state)
{
	switch (state) {
		case OPEN:
			mCurrentFrame = 1U;
			mState = OPEN;
			break;
		case CLOSED:
			mCurrentFrame = 0U;
			mState = CLOSED;
			break;
		default:
			break;
	};
	
	mMesh = mFrames[mCurrentFrame];
}

void TrapDoor::update(const float delta)
{
	if (false == mManual) {
		mAnimationTime -= delta;
	
		if (mAnimationTime < 0.0F) {
			mAnimationTime = mTimer;
			switch (mState) {
				case OPEN:
					setState(CLOSED);
					break;
				case CLOSED:
					setState(OPEN);
					break;
				default:
					break;
			};
		}
	}
}

void TrapDoor::render()
{
	Application* application(Application::getInstance());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	
	graphicsSystem->drawMesh(mMesh, mTransform);
}

