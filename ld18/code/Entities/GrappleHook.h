#ifndef _GRAPPLE_HOOK_H_
#define _GRAPPLE_HOOK_H_

#include "Entity.h"
#include <vector>

class GrappleHook : public Entity
{
	public:
		GrappleHook();
		~GrappleHook();
		
		void addSegment(Entity* const segment) { segments_.push_back(segment); }
		void setSource(Entity* const source) { source_ = source; }
		void setTarget(Entity* const target) { target_ = target; }
		
		void setLength(const float length) { length_ = length; }
		const float getLength() const { return length_; }
		
		void attach(Entity* const target);
		void fire();
		void update(const float deltaTime);
		
	private:
		std::vector<Entity*> segments_;
		Entity* source_;
		Entity* target_;
		float length_;
};

#endif
