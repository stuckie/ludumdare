#include "PressurePad.h"

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

PressurePad::PressurePad(const GLESGAE::Resources::Locator& mesh)
: Entity(mesh, Entity::RENDER_BOX_COLLIDE, Fingers::Entities::PressurePad)
, mFrames()
, mState(UP)
{	
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());

	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::TrapMeshes::Group, Fingers::TrapMeshes::PressurePadUp));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::TrapMeshes::Group, Fingers::TrapMeshes::PressurePadDown));
	
	mMesh = mFrames[0U];
	
	setSphereSize(0.25F);
	setBoxSize(Vector2(0.2F, 0.2F));
}

PressurePad::~PressurePad()
{
}

void PressurePad::update(const float /*delta*/)
{
	setUp();
}

void PressurePad::setUp()
{
	mState = UP;
	mMesh = mFrames[0U];
}

void PressurePad::setDown()
{
	mState = DOWN;
	mMesh = mFrames[1U];
}

void PressurePad::render()
{
	Application* application(Application::getInstance());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	
	graphicsSystem->drawMesh(mMesh, mTransform);
}

