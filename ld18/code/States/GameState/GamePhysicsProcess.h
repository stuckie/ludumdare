#ifndef _GAME_PHYSICS_PROCESS_H_
#define _GAME_PHYSICS_PROCESS_H_

#include "../Process.h"

class GamePhysicsProcess : public Process
{
	public:
		GamePhysicsProcess() {}
		
		const Process::Return update(const float deltaTime);
};

#endif
