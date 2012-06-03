#ifndef _MENU_LOADING_PROCESS_H_
#define _MENU_LOADING_PROCESS_H_

#include "../Process.h"

class MenuLoadingProcess : public Process
{
	public:
		MenuLoadingProcess() {}
		
		const Process::Return update(const float deltaTime) { return Process::SUCCESS; }
};

#endif
