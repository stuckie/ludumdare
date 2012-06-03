#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
	public:
		Timer();
				
		//! Return delta of process
		const float processDelta();
		
	private:
		int currentTime_;
};

#endif
