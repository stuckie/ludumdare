#include "Entity.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>
#include <Maths/Matrix4.h>
#include <Maths/Matrix3.h>
#include <Maths/Vector3.h>
#include <Maths/Vector2.h>

#include "../Resources/Transforms.h"

#include <cmath>

using namespace GLESGAE;

Entity::Entity(const Resources::Locator& mesh, const Type type, const Fingers::Entities::Tag tag)
: mMesh()
, mTransform()
, mType(type)
, mSphereSize(1.0F)
, mBoxSize(1.0F, 1.0F)
, mTag(tag)
, mLastPosition(0.0F, 0.0F, 0.0F)
{
	ResourceManager* resourceManager(Application::getInstance()->getResourceManager());
	mMesh = resourceManager->getBank<Mesh>(mesh.bank, Resources::Mesh).get(mesh.group, mesh.resource);
	
	mTransform = resourceManager->getBank<Matrix4>(Fingers::Transforms::Bank, Resources::Matrix4).add(Fingers::Transforms::Group, Resources::Matrix4, new Matrix4);
}

Entity::~Entity()
{
}

Vector2 Entity::getPosition() const
{
	Vector3 position;
	mTransform->getPosition(&position);
	
	return Vector2(position.x(), position.y());
}

void Entity::setPosition(const GLESGAE::Vector2& position)
{
	mTransform->getPosition(&mLastPosition);
	mTransform->setPosition(Vector3(position.x(), position.y(), 0.0F));
}

void Entity::rotate(const float radians)
{
	Matrix3 rotation;
	rotation(0, 0) = cosf(radians);
	rotation(0, 1) = sinf(radians);
	rotation(1, 0) = -sinf(radians);
	rotation(1, 1) = cosf(radians);
	mTransform->setRotation(rotation);
}

void Entity::translate(const GLESGAE::Vector2& translate)
{
	Vector3 position;
	mTransform->getPosition(&position);
	position.x() += translate.x();
	position.y() += translate.y();
	mTransform->setPosition(position);
}

bool Entity::collide(const GLESGAE::Resource<Entity>& entity)
{
	// No colliding with your bad self!
	if (&(*entity) == this)
		return false;
		
	const float theirSize(entity->getSphereSize());
	Vector3 myPosition;
	Vector3 theirPosition;
	
	mTransform->getPosition(&myPosition);
	entity->getTransform()->getPosition(&theirPosition);
	
	// Fast Circle collision - hot spot is centre of sprite.
	const float dX = theirPosition.x() - myPosition.x();
	const float dY = theirPosition.y() - myPosition.y();
	const float radii = mSphereSize + theirSize;
	
	// If distance is way out, ignore.. don't need to do anything else
	if (((dX * dX) + (dY * dY)) > (radii * radii))
		return false;
	else { // IF we're just a circle collision, we're done.. else we need to actually check the box bounds
		if (((mType == RENDER_SPHERE_COLLIDE) || (mType == SPHERE_COLLIDE))
		&& ((entity->getType() == RENDER_SPHERE_COLLIDE) || (entity->getType() == RENDER_SPHERE_COLLIDE)))
			return true;
		else { // Must do Box Collisions - hot spot is centre of sprite.
			const Vector2& theirBox(entity->getBoxSize());
			const float leftA = myPosition.x() - (mBoxSize.x() * 0.5F); 
			const float rightA = myPosition.x() + (mBoxSize.x() * 0.5F);
			const float topA = myPosition.y() - (mBoxSize.y() * 0.5F);
			const float bottomA = myPosition.y() + (mBoxSize.y() * 0.5F);
		
			const float leftB = theirPosition.x() - (theirBox.x() * 0.5F); 
			const float rightB = theirPosition.x() + (theirBox.x() * 0.5F);
			const float topB = theirPosition.y() - (theirBox.y() * 0.5F);
			const float bottomB = theirPosition.y() + (theirBox.y() * 0.5F);
	
			if ((bottomA <= topB)
			|| (topA >= bottomB)
			|| (rightA <= leftB)
			|| (leftA >= rightB))
				return false;
			else
				return true;
		}
	}
}

void Entity::update(const float /*delta*/)
{
}

void Entity::moveBack()
{
	mTransform->setPosition(mLastPosition);
}

void Entity::render()
{
	GraphicsSystem* graphicsSystem(Application::getInstance()->getGraphicsSystem());
	graphicsSystem->drawMesh(mMesh, mTransform);
}


