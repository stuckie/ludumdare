#include "Crusher.h"

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

Crusher::Crusher(const GLESGAE::Resources::Locator& mesh)
: Entity(mesh, Entity::RENDER_BOX_COLLIDE, Fingers::Entities::Crusher)
, mArmMesh()
, mDirection(DOWN)
, mSpeed(1.0F)
{
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());

	mArmMesh = resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherArm);
}

Crusher::~Crusher()
{
}

void Crusher::swapDirection()
{
	switch (mDirection) {
		case LEFT:
			mDirection = RIGHT;
		break;
		case RIGHT:
			mDirection = LEFT;
		break;
		case UP:
			mDirection = DOWN;
		break;
		case DOWN:
			mDirection = UP;
		break;
		case STOP:
			default:
		break;
	}
}

void Crusher::update(const float delta)
{
	switch (mDirection) {
		case LEFT: {
			Vector3 position;
			mTransform->getPosition(&position);
			position.x() += (mSpeed * delta);
			mTransform->setPosition(position);
		};
		break;
		case RIGHT: {
			Vector3 position;
			mTransform->getPosition(&position);
			position.x() -= (mSpeed * delta);
			mTransform->setPosition(position);
		};
		break;
		case UP: {
			Vector3 position;
			mTransform->getPosition(&position);
			position.y() += (mSpeed * delta);
			mTransform->setPosition(position);
		};
		break;
		case DOWN: {
			Vector3 position;
			mTransform->getPosition(&position);
			position.y() -= (mSpeed * delta);
			mTransform->setPosition(position);
		};
		break;
		case STOP:
		default:
		break;
	}
}

void Crusher::render()
{
	Application* application(Application::getInstance());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	
	graphicsSystem->drawMesh(mMesh, mTransform);
}

