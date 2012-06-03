#ifndef _PHYSICS_SYSTEM_H_
#define _PHYSICS_SYSTEM_H_

// I suppose "Physics System" is a bit of a stretch...

class PhysicsSystem
{
	public:
		~PhysicsSystem();
	
		//! Creates or returns the current active instance.
		static PhysicsSystem& instance();
		
		//! Update the Physics System
		void update(const float deltaTime);
		
	private:
		PhysicsSystem();
		
		static PhysicsSystem* instance_;	//!< Active instance
};

#endif
