#ifndef _STATE_H_
#define _STATE_H_

#include "Processor.h"
#include <cassert>

class State
{
	public:
		State() : processor_(0) {}
		virtual ~State() { delete processor_; }
		
		//! Pure Virtual Update
		virtual void update(const float deltaTime) = 0;
		
		//! Set Processor
		void setProcessor(Processor* const processor) { delete processor_; processor_ = processor; }
		
		//! Update Processor
		void updateProcessor(const float deltaTime) { assert(processor_); processor_->update(deltaTime); }
		
	private:
		Processor* processor_;
};

#endif
