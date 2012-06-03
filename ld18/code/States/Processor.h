#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

// Inlined for speed... though it does look nasty..

#include "Process.h"

#include <vector>

class Processor : public Process
{
	public:
		Processor(const std::vector<Process*> processList) : processList_(processList) {}
		~Processor() { for (std::vector<Process*>::iterator itr(processList_.begin()); itr != processList_.end(); ++itr) delete (*itr); }
		
		//! Update all Processes
		const Process::Return update(const float deltaTime)
		{
			Process::Return returnValue(Process::SUCCESS);
			bool allProcessesSuccessful(false);
			while (false == allProcessesSuccessful) {
				bool success(true);
				for (std::vector<Process*>::iterator process(processList_.begin()); process != processList_.end(); ++process) {
					Process::Return currentProcess((*process)->update(deltaTime));
					switch (currentProcess) {
						case Process::BLOCKING:
							returnValue = currentProcess;
							success = false;
							break;
						case Process::STOP:
							returnValue = currentProcess;
							success = true;
							allProcessesSuccessful = true;
							break;
						default:
							break;
					}
					allProcessesSuccessful = success;
					if (returnValue == Process::STOP)
						break;
				}
			}
			
			return returnValue;
		}
		
	private:
		std::vector<Process*> processList_;
};

#endif
