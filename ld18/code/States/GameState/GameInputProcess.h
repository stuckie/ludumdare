#ifndef _GAME_INPUT_PROCESS_H_
#define _GAME_INPUT_PROCESS_H_

#include "../Process.h"

class GameInputProcess : public Process
{
	public:
		GameInputProcess() {}
		
		const Process::Return update(const float deltaTime);
};

#endif
