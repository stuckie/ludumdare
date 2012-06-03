#ifndef _GAME_RENDER_PROCESS_H_
#define _GAME_RENDER_PROCESS_H_

#include "../Process.h"

class GameRenderProcess : public Process
{
	public:
		GameRenderProcess() {}
		
		const Process::Return update(const float deltaTime);
};

#endif
