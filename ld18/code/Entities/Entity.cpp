#include "Entity.h"

Entity::Entity()
: position_(0.0F, 0.0F)
, velocity_(0.0F, 0.0F)
, speed_(0.0F)
, mass_(1.0F)
, radius_(16.0F)
, health_(100U)
, angle_(0.0F)
, graphicObject_(0)
, soundObject_(0)
, inputObject_(0)
{
	
}

Entity::~Entity()
{
	delete graphicObject_;
	graphicObject_ = 0;
	
	delete soundObject_;
	soundObject_ = 0;
	
	delete inputObject_;
	inputObject_ = 0;
}

const bool Entity::checkCollision(Entity* const entity)
{
	const Vector2D centreA(position_.x_ + 16.0F, position_.y_ + 16.0F);
	const Vector2D centreB(entity->readPosition().x_ + 16.0F, entity->readPosition().y_ + 16.0F);
	const float radiusA(radius_);
	const float radiusB(entity->getRadius());
	
	if ((((centreA.x_ + radiusA) > (centreB.x_ - radiusB)) && ((centreA.y_ + radiusA) > (centreB.y_ - radiusB)))
		&& (((centreA.x_ - radiusA) < (centreB.x_ + radiusB)) && ((centreA.y_ - radiusA) < (centreB.y_ + radiusB))))
		return true;
	else
		return false;
}
