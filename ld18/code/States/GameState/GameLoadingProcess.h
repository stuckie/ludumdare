#ifndef _GAME_LOADING_PROCESS_H_
#define _GAME_LOADING_PROCESS_H_

#include "../Process.h"

class GameLoadingProcess : public Process
{
	public:
		GameLoadingProcess() {}
		
		const Process::Return update(const float deltaTime);
};

#endif
