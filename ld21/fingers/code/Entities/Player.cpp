#include "Player.h"

#include "../Resources/Entities.h"

#include <Input/InputSystem.h>
#include <Input/Pointer.h>
#include <Input/Keyboard.h>
#include <Platform/Application.h>
#include <Resources/ResourceManager.h>
#include <States/StateStack.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Mesh.h>
#include <Maths/Matrix3.h>
#include <Maths/Matrix4.h>
#include <Time/Clock.h>
#include <cmath>
#include "../Resources/Meshes.h"
#include "../Resources/Camera.h"
#include "../Resources/Transforms.h"

using namespace GLESGAE;

extern bool gameComplete;
extern bool gameLost;

Player::Player(const GLESGAE::Resources::Locator& mesh)
: Entity(mesh, Entity::RENDER_SPHERE_COLLIDE, Fingers::Entities::Player)
, mFrames()
, mState(STANDING)
, mPointerId()
, mKeyboardId()
, mHealth(100)
, mGems(0)
, mWalkStart(0.0F, 0.0F)
, mCamera()
, mCurrentFrame(4U)
, mAnimationTime(0.1F)
, mIconTransform()
{	
	Application* application(Application::getInstance());
	InputSystem* inputSystem(application->getInputSystem());
	ResourceManager* resourceManager(application->getResourceManager());
	
	Controller::PointerController* myPointer(inputSystem->newPointer());
	mPointerId = myPointer->getControllerId();
	
	Controller::KeyboardController* myKeyboard(inputSystem->newKeyboard());
	mKeyboardId = myKeyboard->getControllerId();
	
	mCamera = resourceManager->getBank<Camera>(Fingers::Camera::Bank, Resources::Camera).get(Fingers::Camera::Group, Fingers::Camera::Id);
	mCamera->getTransformMatrix().setPosition(Vector3(0.5F, -0.5F, 1.0F));
	
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::PlayerMeshes::Group, Fingers::PlayerMeshes::Frames::Walk1));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::PlayerMeshes::Group, Fingers::PlayerMeshes::Frames::Static));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::PlayerMeshes::Group, Fingers::PlayerMeshes::Frames::Walk2));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::PlayerMeshes::Group, Fingers::PlayerMeshes::Frames::Static));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::PlayerMeshes::Group, Fingers::PlayerMeshes::Frames::Hurt));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::PlayerMeshes::Group, Fingers::PlayerMeshes::Frames::Death));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::PlayerMeshes::Group, Fingers::PlayerMeshes::Heart));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::CollectableMeshes::Group, Fingers::CollectableMeshes::Gems));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::FontMeshes::Group, Fingers::FontMeshes::Complete));
	mFrames.push_back(resourceManager->getBank<Mesh>(Fingers::Meshes::Bank, Resources::Mesh).get(Fingers::FontMeshes::Group, Fingers::FontMeshes::Lost));
	
	mMesh = mFrames[mCurrentFrame];
	
	mIconTransform = resourceManager->getBank<Matrix4>(Fingers::Transforms::Bank, Resources::Matrix4).add(Fingers::Transforms::Group, Resources::Matrix4, new Matrix4);
	
	setSphereSize(0.1F);
	setBoxSize(Vector2(0.1F, 0.1F));
}

Player::~Player()
{
}

void Player::modifyHealth(const int health)
{
	if (mState != HURT) {
		const int currentHealth(mHealth);
		mHealth += health;
		
		if (mHealth < currentHealth) {
			mState = HURT;
			mAnimationTime = 1.0F;
			mCurrentFrame = 4U;
			mMesh = mFrames[mCurrentFrame];
		}
	
		if (mHealth <= 0) {
			mState = DEAD;
			mCurrentFrame = 5U;
			mMesh = mFrames[mCurrentFrame];
			gameLost = true;
		}
	}
}

void Player::setPosition(const Vector2& position)
{
	if (mState != DEAD)
		Entity::setPosition(position);
}

void Player::update(const float delta)
{
	Vector3 cameraPosition;
	mCamera->getTransformMatrix().getPosition(&cameraPosition);
		cameraPosition.x() = mLastPosition.x() + 0.5F;
		cameraPosition.y() = mLastPosition.y() - 0.5F;
	mCamera->getTransformMatrix().setPosition(cameraPosition);
	
	mCamera->update();
	mAnimationTime -= delta;
	
	Application* application(Application::getInstance());
	InputSystem* inputSystem(application->getInputSystem());
	
	Controller::PointerController* myPointer(inputSystem->getPointer(mPointerId));
	Controller::KeyboardController* myKeyboard(inputSystem->getKeyboard(mKeyboardId));
	
	if (myKeyboard->getKey(Controller::KEY_ESCAPE) == 1.0F)
		application->getStateStack()->pop();
	
	switch (mState) {
		case WALKING:{
			if (mAnimationTime < 0.0F) {
				++mCurrentFrame;
				if (mCurrentFrame > 3U)
					mCurrentFrame = 0U;
					
				mAnimationTime = 0.1F;
				mMesh = mFrames[mCurrentFrame];
			}
		}
		break;
	
		case HURT: {
			if (mAnimationTime < 0.0F) {
				mAnimationTime = 0.5F;
				mCurrentFrame = 1U;
				mMesh = mFrames[mCurrentFrame];
				mState = STANDING;
			}
			else
				return;
		}
		break;
	
		case DEAD:
			return;
		break;
		
		case STANDING:
		default:
		break;
	}
	
	float deltaX(myPointer->getAxis(0U) - mWalkStart.x());
	float deltaY(myPointer->getAxis(1U) - mWalkStart.y());
	
	if (0.0F != myPointer->getButton(1U)) {
		if (WALKING != mState) {
			mState = WALKING;
			mWalkStart.x() = myPointer->getAxis(0U);
			mWalkStart.y() = myPointer->getAxis(1U);
		}
	}
	else if ((true == myKeyboard->getKey(Controller::KEY_ARROW_LEFT)) 
		|| (true == myKeyboard->getKey(Controller::KEY_ARROW_RIGHT))
		||	(true == myKeyboard->getKey(Controller::KEY_ARROW_UP)) 
		|| (true == myKeyboard->getKey(Controller::KEY_ARROW_DOWN))) {
		mState = WALKING;
		deltaX = deltaY = 0.0F;
		if (myKeyboard->getKey(Controller::KEY_ARROW_LEFT))
			deltaX = -50.0F;
		else if (myKeyboard->getKey(Controller::KEY_ARROW_RIGHT))
			deltaX = 50.0F;
			
		if (myKeyboard->getKey(Controller::KEY_ARROW_UP))
			deltaY = -50.0F;
		else if (myKeyboard->getKey(Controller::KEY_ARROW_DOWN))
			deltaY = 50.0F;
	}
	else {
		mState = STANDING;
		mCurrentFrame = 1U;
		mMesh = mFrames[mCurrentFrame];
		mWalkStart.setToZero();
	}
	
	
	if (WALKING == mState) {		
		if (deltaX > 50.0F)
			deltaX = 50.0F;
		else if (deltaX < -50.0F)
			deltaX = -50.0F;
			
		if (deltaY > 50.0F)
			deltaY = 50.0F;
		else if (deltaY < -50.0F)
			deltaY = -50.0F;
	
		Vector3 position;
		mTransform->getPosition(&position);
			mLastPosition = position;
			position.x() -= (deltaX * 0.01F) * delta;
			position.y() -= (deltaY * 0.01F) * delta;
		mTransform->setPosition(position);
		
	
		float angle(0.0F);
		if (position.x() - mLastPosition.x() == 0.0F) {
			if (position.y() > mLastPosition.y())
				angle = 0.0F;
			else
				angle = 3.14F;
		}
		else {
			angle = atanf( (position.y() - mLastPosition.y()) / (position.x() - mLastPosition.x()) );
			if (position.x() > mLastPosition.x() )
				angle = 3.14F / 2.0F - angle;
			else
				angle = 3.14F * 1.5F - angle;
		}
		
		Matrix3 rotation;
		mTransform->getRotation(&rotation);
			rotation(0, 0) = cosf(angle);
			rotation(0, 1) = sinf(angle);
			rotation(1, 0) = -sinf(angle);
			rotation(1, 1) = cosf(angle);
		mTransform->setRotation(rotation);
	}
}

void Player::render()
{
	Application* application(Application::getInstance());
	GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
	
	graphicsSystem->setCamera(mCamera);
	graphicsSystem->drawMesh(mMesh, mTransform);
	
	for (int gemCount(0); gemCount < mGems; ++gemCount) {
		Vector3 position;
		mIconTransform->getPosition(&position);
		position.x() = (mLastPosition.x() + 0.4F) - (gemCount * 0.02F);
		position.y() = (mLastPosition.y() - 0.45F);
		mIconTransform->setPosition(position);
		mIconTransform->setScale(Vector3(0.5F, 0.5F, 1.0F));
		graphicsSystem->drawMesh(mFrames[7], mIconTransform);
		mIconTransform->setScale(Vector3(2.0F, 2.0F, 1.0F));
	}
	
	for (int heartCount(0); heartCount < mHealth / 10; ++heartCount) {
		Vector3 position;
		mIconTransform->getPosition(&position);
		position.x() = (mLastPosition.x() + 0.4F) - (heartCount * 0.01F);
		position.y() = (mLastPosition.y() - 0.4F);
		mIconTransform->setPosition(position);
		graphicsSystem->drawMesh(mFrames[6], mIconTransform);
	}
	
	if (gameComplete) {
		Matrix3 rotation;
		mTransform->getRotation(&rotation);
			rotation(0, 0) = 1.0F;
			rotation(0, 1) = 0.0F;
			rotation(1, 0) = 0.0F;
			rotation(1, 1) = 1.0F;
		mTransform->setRotation(rotation);
		graphicsSystem->drawMesh(mFrames[8], mTransform);
	}
	
	if (gameLost) {
		Matrix3 rotation;
		mTransform->getRotation(&rotation);
			rotation(0, 0) = 1.0F;
			rotation(0, 1) = 0.0F;
			rotation(1, 0) = 0.0F;
			rotation(1, 1) = 1.0F;
		mTransform->setRotation(rotation);
		graphicsSystem->drawMesh(mFrames[9], mTransform);
	}
}

