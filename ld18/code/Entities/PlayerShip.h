#ifndef _PLAYER_SHIP_H_
#define _PLAYER_SHIP_H_

#include "Entity.h"

class PlayerShip : public Entity
{
	public:
		PlayerShip();
		~PlayerShip();
		
		void accelerate();
		void decelerate();
		void rotateLeft();
		void rotateRight();
		void grappleLeft();
		void grappleRight();
		void fire();
};

#endif
