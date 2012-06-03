#ifndef _PROCESS_H_
#define _PROCESS_H_

class Process
{
	public:
		Process() {}
		virtual ~Process() {}
		
		enum Return {
			SUCCESS
		,	BLOCKING
		,	ONCE
		,	STOP
		};
		
		//! Pure Virtual Update
		virtual const Return update(const float deltaTime) = 0;
};

#endif
