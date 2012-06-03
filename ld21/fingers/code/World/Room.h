#ifndef _ROOM_H_
#define _ROOM_H_

/// A Room is, in effect, a bunch of tiles.
/// It also may contain a trap or two.. just to get it done, we're hacking everything as an Entity here.
/// Each room also has at least one exit.

#include <Resources/Resource.h>
#include "../Entities/EntityManager.h"
#include <Maths/Vector2.h>
#include <Resources/ResourceManager.h>
#include <Platform/Application.h>
#include "../Resources/Meshes.h"
#include "../Resources/Entities.h"

class CollisionCallback;
class Room
{
	public:
		Room(const unsigned int floorId, CollisionCallback* const collisionCallback);
		virtual ~Room();
		
		/// Update the Room
		virtual void update(const float delta) = 0;
		
		/// Render the Room
		virtual void render() = 0;
		
		/// Move an Entity into this room
		virtual void addEntity(const GLESGAE::Resource<Entity>& entity) = 0;
		
		/// Remove an Entity from this room
		virtual void removeEntity(const GLESGAE::Resource<Entity>& entity) = 0;
		
		/// Get the floor this room belongs on
		unsigned int getFloor() const { return mFloorId; }
		
		/// Get whether this room is visible
		bool isVisible() const { return mVisible; }
		
		/// Set visibility
		void setVisible(const bool visible) { mVisible = visible; }
		
	protected:
		/// Helper function to create the floor
		void createFloor();
		
		/// Helper function to create a wall of a given size
		void createWall(const GLESGAE::Vector2& centre, const GLESGAE::Vector2& size);
		
		/// Helper function to create a generic item
		GLESGAE::Resource<Entity>& createItem(const GLESGAE::Vector2& centre, const GLESGAE::Vector2& size, const GLESGAE::Resources::Group group, const GLESGAE::Resources::Id id, const Fingers::Entities::Tag tag);
		
		/// Helper function to create a door
		void createDoor(const GLESGAE::Vector2& position, const Fingers::Entities::Tag tag);
		
		/// Helper function to create a trap
		template <typename T_Entity> GLESGAE::Resource<Entity>& createTrap(const GLESGAE::Vector2& centre, const GLESGAE::Vector2& size, const GLESGAE::Resources::Group group, const GLESGAE::Resources::Id id);
		
		EntityManager mEntityManager;
		bool mVisible;
		GLESGAE::Vector2 mOffset;
				
	private:
		unsigned int mFloorId;
};

	template <typename T_Entity>
	GLESGAE::Resource<Entity>& Room::createTrap(const GLESGAE::Vector2& centre, const GLESGAE::Vector2& size, const GLESGAE::Resources::Group group, const GLESGAE::Resources::Id id)
	{
		GLESGAE::ResourceManager* resourceManager(GLESGAE::Application::getInstance()->getResourceManager());
		GLESGAE::ResourceBank<Entity>& entityBank(resourceManager->getBank<Entity>(Fingers::Entities::Bank, Fingers::Entities::Type));
	
		GLESGAE::Resources::Locator locator;
		locator.bank = Fingers::Meshes::Bank;
		locator.group = group;
		locator.resource = id;
	
		GLESGAE::Resource<Entity>& entity(entityBank.add(Fingers::Entities::Group, Fingers::Entities::Type, new T_Entity(locator)));
		entity->setPosition(GLESGAE::Vector2(centre.x() + mOffset.x(), centre.y() + mOffset.y()));
		entity->getTransform()->setScale(GLESGAE::Vector3(size.x(), size.y(), 1.0F));
		
		if (Fingers::Entities::Camera == entity->getTag()) {
			entity->setBoxSize(GLESGAE::Vector2(0.2F * size.x(), 0.2F * size.y()));
			if (size.x() > size.y())
				entity->setSphereSize(2.0F + (size.x() * 0.01F));
			else
				entity->setSphereSize(2.0F + (size.y() * 0.01F));
		}
		else {
			entity->setBoxSize(GLESGAE::Vector2(0.1F * size.x(), 0.1F * size.y()));
			if (size.x() > size.y())
				entity->setSphereSize(1.0F + (size.x() * 0.01F));
			else
				entity->setSphereSize(1.0F + (size.y() * 0.01F));
		}
		
		mEntityManager.add(entity);
	
		return entity;
	}

#endif

