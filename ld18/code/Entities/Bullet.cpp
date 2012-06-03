#include "Bullet.h"

#include <cstdio>
#include <cmath>
#include "../Objects/Math.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::fire()
{
	writeVelocity().x_ += cos(deg2rad(getAngle())) * getSpeed();
	writeVelocity().y_ += sin(deg2rad(getAngle())) * getSpeed();
}
