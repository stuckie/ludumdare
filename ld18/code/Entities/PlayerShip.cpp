#include "PlayerShip.h"

#include <cstdio>
#include <cmath>
#include "Bullet.h"
#include "../Objects/Math.h"
#include "../Objects/SDLGraphicObject.h"
#include "../Systems/Entity/EntitySystem.h"

PlayerShip::PlayerShip()
{
	
}

PlayerShip::~PlayerShip()
{

}

void PlayerShip::accelerate()
{
	if (getSpeed() < 5.0F)
		setSpeed(getSpeed() + 1.0F);
	writeVelocity().x_ += cos(deg2rad(getAngle())) * getSpeed();
	writeVelocity().y_ += sin(deg2rad(getAngle())) * getSpeed();
}

void PlayerShip::decelerate()
{
	if (getSpeed() > -5.0F)
		setSpeed(getSpeed() - 3.0F);
	
	writeVelocity().x_ += cos(deg2rad(getAngle())) * getSpeed();
	writeVelocity().y_ += sin(deg2rad(getAngle())) * getSpeed();
}

void PlayerShip::rotateLeft()
{
	setAngle(getAngle() + 2.5F);
}

void PlayerShip::rotateRight()
{
	setAngle(getAngle() - 2.5F);
}

void PlayerShip::grappleLeft()
{
	
}

void PlayerShip::grappleRight()
{
	
}

void PlayerShip::fire()
{
	Vector2D position(readPosition());
	position.x_ += 16.0F + (cos(deg2rad(getAngle())));
	position.y_ -= (sin(deg2rad(getAngle())));
	
	EntitySystem& entitySystem(EntitySystem::instance());
	Bullet* const bullet(entitySystem.add<Bullet>("Movable"));
	entitySystem.addToList(bullet, "Renderable");
	bullet->setGraphicObject(new SDLGraphicObject);
	bullet->writePosition() = position;
	bullet->writeGraphicObject<SDLGraphicObject>().load("data/shot.bmp");
	bullet->setAngle(getAngle());
	bullet->setSpeed(600.0F);
	bullet->fire();
}
