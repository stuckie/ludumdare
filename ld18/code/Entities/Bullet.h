#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"

class Bullet : public Entity
{
	public:
		Bullet();
		~Bullet();
		
		void fire();
};

#endif
