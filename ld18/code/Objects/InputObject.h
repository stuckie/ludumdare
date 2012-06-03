#ifndef _INPUT_OBJECT_H_
#define _INPUT_OBJECT_H_

class Entity;
class InputObject
{
	public:
		InputObject(Entity* const entity) : entity_(entity) {}
		virtual ~InputObject() {}
		
		//! Setup the Controls
		virtual void setup() = 0;
		
		//! Update the Controls
		virtual void update() = 0;
		
		//! Read Access to Entity
		template <typename T_Entity>
		const T_Entity* const readEntity() const { return static_cast<T_Entity*>(entity_); }
		
		//! Write Access to Entity
		template <typename T_Entity>
		T_Entity* const writeEntity() { return static_cast<T_Entity*>(entity_); }
		
	private:
		Entity* entity_;
};

#endif
