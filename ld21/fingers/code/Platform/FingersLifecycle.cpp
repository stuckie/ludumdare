#include "FingersLifecycle.h"

#include <Platform/Application.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Context/FixedFunctionContext.h>
#include <Events/EventSystem.h>
#include <Input/InputSystem.h>
#include <States/StateStack.h>
#include <Time/Clock.h>
#include <Time/Timer.h>
#include <Resources/ResourceManager.h>

#include "../States/Game/GameState.h"
#include "../Resources/Camera.h"
#include "../Resources/Timers.h"
#include "../Resources/IndexBuffers.h"
#include "../Resources/Materials.h"
#include "../Resources/Transforms.h"
#include "../Resources/VertexBuffers.h"
#include "../Resources/Meshes.h"

#include <Graphics/Camera.h>
#include <Graphics/Material.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/Mesh.h>
#include <Maths/Matrix4.h>

using namespace GLESGAE;

FingersLifecycle::FingersLifecycle()
: mGameTimer()
{
}

void FingersLifecycle::onCreate()
{
	// Platform specific madness.. for example, ask for a window of a certain resolution if possible, setup scaling and so on.
}

void FingersLifecycle::onStart()
{
	Application* application(Application::getInstance());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	EventSystem* eventSystem(application->getEventSystem());
	StateStack* stateStack(application->getStateStack());
	ResourceManager* resourceManager(application->getResourceManager());
	
	// Create Global Resource Banks
	ResourceBank<Timer>& timerBank(resourceManager->createBank<Timer>(Resources::Timer));
	Fingers::Timers::Bank = timerBank.getId();
	Fingers::Timers::Group = timerBank.newGroup();
	
	ResourceBank<IndexBuffer>& indexBank(resourceManager->createBank<IndexBuffer>(Resources::IndexBuffer));
	Fingers::IndexBuffers::Bank = indexBank.getId();
	Fingers::IndexBuffers::Group = indexBank.newGroup();
	
	ResourceBank<VertexBuffer>& vertexBank(resourceManager->createBank<VertexBuffer>(Resources::VertexBuffer));
	Fingers::VertexBuffers::Bank = vertexBank.getId();
	Fingers::VertexBuffers::Group = vertexBank.newGroup();
	
	ResourceBank<Material>& materialBank(resourceManager->createBank<Material>(Resources::Material));
	Fingers::Materials::Bank = materialBank.getId();
	Fingers::Materials::Group = materialBank.newGroup();
	
	ResourceBank<Matrix4>& transformBank(resourceManager->createBank<Matrix4>(Resources::Matrix4));
	Fingers::Transforms::Bank = transformBank.getId();
	Fingers::Transforms::Group = transformBank.newGroup();
	
	ResourceBank<Mesh>& meshBank(resourceManager->createBank<Mesh>(Resources::Mesh));
	Fingers::Meshes::Bank = meshBank.getId();
	Fingers::PlayerMeshes::Group = meshBank.newGroup();
	Fingers::RoomMeshes::Group = meshBank.newGroup();
	Fingers::TrapMeshes::Group = meshBank.newGroup();
	Fingers::CollectableMeshes::Group = meshBank.newGroup();
	Fingers::PushableMeshes::Group = meshBank.newGroup();
	Fingers::FontMeshes::Group = meshBank.newGroup();
	
	ResourceBank<Camera>& cameraBank(resourceManager->createBank<Camera>(Resources::Camera));
	Fingers::Camera::Bank = cameraBank.getId();
	Fingers::Camera::Group = cameraBank.newGroup();
	Resource<Camera>& camera(cameraBank.add(Fingers::Camera::Group, Resources::Camera, new Camera(Camera::CAMERA_2D)));
	Fingers::Camera::Id = camera.getId();
	
	Resource<Timer>& gameTimer(timerBank.add(Fingers::Timers::Group, Resources::Timer, new Timer));
	Fingers::Timers::GameTimer = gameTimer.getId();
	mGameTimer = gameTimer;
	
	
	unsigned int screenWidth(800);
	unsigned int screenHeight(480);
	unsigned int screenBPP(32);
	bool fullscreen(false);
	
	if (false == graphicsSystem->initialise("Thieving Fingers", screenWidth, screenHeight, screenBPP, fullscreen)) {
		//TODO: OH NOES! WE'VE DIEDED!
	}

	FixedFunctionContext* const fixedContext(graphicsSystem->getFixedContext());
	if (0 != fixedContext) {
		fixedContext->enableFixedFunctionVertexPositions();
	}
	
	eventSystem->bindToWindow(graphicsSystem->getWindow());
	
	stateStack->replace<GameState>();
}

void FingersLifecycle::onResume()
{
}

bool FingersLifecycle::onLoop()
{
	Application* application(Application::getInstance());
	EventSystem* eventSystem(application->getEventSystem());
	InputSystem* inputSystem(application->getInputSystem());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	StateStack* stateStack(application->getStateStack());
	mGameTimer->update(application->getClock());

	eventSystem->update();
	inputSystem->update();
	graphicsSystem->beginFrame();
	const bool isRunning(stateStack->update(mGameTimer->getDelta()));
	graphicsSystem->endFrame();
	
	return isRunning;
}

void FingersLifecycle::onPause()
{
}

void FingersLifecycle::onStop()
{
}

void FingersLifecycle::onDestroy()
{
}

