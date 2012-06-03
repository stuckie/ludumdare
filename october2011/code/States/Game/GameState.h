#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <States/State.h>

class GameState : public GLESGAE::State
{
	public:
		//! Starts the state
		GameState();
		
		//! Update the state
		bool update(const float deltaTime);
		
		//! Pulls down the state
		~GameState();
};

#endif

