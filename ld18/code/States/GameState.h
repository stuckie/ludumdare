#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "State.h"

class GraphicsCamera;
class GameState : public State
{
	public:
		GameState();
		
		void update(const float deltaTime);
		
		GraphicsCamera* const readGraphicsCamera() const { return graphicsCamera_; }
		GraphicsCamera* const writeGraphicsCamera() { return graphicsCamera_; }
		
	private:
		GraphicsCamera* graphicsCamera_;

};

#endif
