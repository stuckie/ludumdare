#ifndef _FRONTEND_STATE_H_
#define _FRONTEND_STATE_H_

#include <States/State.h>

class FrontendState : public GLESGAE::State
{
	public:
		/// Constructor - sets up the state
		FrontendState();
		
		/// Update the state
		bool update(const float delta);
		
		/// Destructor - pulls down the state
		~FrontendState();
};

#endif

