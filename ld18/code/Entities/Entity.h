#ifndef _ENTITY_H_
#define _ENTITY_H_

// Ah, the wonderous Base Entity class...
// This defines anything that MOVES.

#include <cassert>

#include "../Objects/Math.h"
#include "../Objects/GraphicObject.h"
#include "../Objects/SoundObject.h"
#include "../Objects/InputObject.h"

class Entity
{
	public:
		Entity();
		virtual ~Entity();
		
		const Vector2D& readPosition() const { return position_; }
		Vector2D& writePosition() { return position_; }
		
		const Vector2D& readVelocity() const { return velocity_; }
		Vector2D& writeVelocity() { return velocity_; }
		
		const float getMass() const { return mass_; }
		void setMass(const float mass) { mass_ = mass; }
		
		const float getRadius() const { return radius_; }
		void setRadius(const float radius) { radius_ = radius; }
		
		const Uint getHealth() const { return health_; }
		void setHealth(const Uint health) { health_ = health; }
		
		void setGraphicObject(GraphicObject* const graphicObject) { graphicObject_ = graphicObject; }
		
		template <typename T_Object>
		const T_Object& readGraphicObject() const;
		
		template <typename T_Object>
		T_Object& writeGraphicObject();
		
		void setSoundObject(SoundObject* const soundObject) { soundObject_ = soundObject; }
		
		template <typename T_Object>
		const T_Object& readSoundObject() const;
		
		template <typename T_Object>
		T_Object& writeSoundObject();
		
		void setInputObject(InputObject* const inputObject) { inputObject_ = inputObject; }
		
		template <typename T_Object>
		const T_Object& readInputObject() const;
		
		template <typename T_Object>
		T_Object& writeInputObject();
		
		const bool checkCollision(Entity* const entity);
		
		const float getAngle() const { return angle_; }
		void setAngle(const float angle) { angle_ = angle; }
		
		const float getSpeed() const { return speed_; }
		void setSpeed(const float speed) { speed_ = speed; }
		
	private:
		Vector2D position_;		//!< Position of this Entity.
		Vector2D velocity_;		//!< Velocity of this Entity.
		float speed_;			//!< Speed of this Entity.
		float mass_;			//!< Mass of this entity for dealing with the Grappling Hook.
		float radius_;			//!< We're using circle collisions for speed and simplicity.
		float health_;			//!< Health of this Entity.
		float angle_;			//!< Angle of this Entity ( in degrees )
		
		GraphicObject* graphicObject_; 	//!< Pointer to a Graphics Object
		SoundObject* soundObject_;		//!< Pointer to a Sound Object
		InputObject* inputObject_;		//!< Pointer to an Input Object
};

template <typename T_Object>
const T_Object& Entity::readGraphicObject() const
{
	assert(graphicObject_);
	return (*(static_cast<T_Object*>(graphicObject_)));
}

template <typename T_Object>
T_Object& Entity::writeGraphicObject()
{
	assert(graphicObject_);
	return (*(static_cast<T_Object*>(graphicObject_)));
}

template <typename T_Object>
const T_Object& Entity::readSoundObject() const
{
	assert(soundObject_);
	return (*(static_cast<T_Object*>(soundObject_)));
}

template <typename T_Object>
T_Object& Entity::writeSoundObject()
{
	assert(soundObject_);
	return (*(static_cast<T_Object*>(soundObject_)));
}

template <typename T_Object>
const T_Object& Entity::readInputObject() const
{
	assert(inputObject_);
	return (*(static_cast<T_Object*>(inputObject_)));
}

template <typename T_Object>
T_Object& Entity::writeInputObject()
{
	assert(inputObject_);
	return (*(static_cast<T_Object*>(inputObject_)));
}

#endif
