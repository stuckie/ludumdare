#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <Resources/Resource.h>
#include <Graphics/Mesh.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <Maths/Matrix4.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/Material.h>

#include "../Resources/Entities.h"

/// Common entity for Fingers... very hacky...
/// The Type describes to the EntityManager which list(s) to throw this in.. one can collide, one can draw.
/// Also, when doing collision checks, if it finds two sphere collision checks, it can perform a faster check.
/// The Tag is effectively the means which I can check in the Collision Callback what Entity has been hit and deal with it appropriately.
class Entity
{
	public:
		enum Type
		{
			RENDER_ONLY
		,	SPHERE_COLLIDE
		,	BOX_COLLIDE
		,	RENDER_SPHERE_COLLIDE
		,	RENDER_BOX_COLLIDE
		};
		
		virtual ~Entity();
		
		/// Requires a Mesh to act with
		Entity(const GLESGAE::Resources::Locator& mesh, const Type type, const Fingers::Entities::Tag tag);
		
		/// Set the position directly
		virtual void setPosition(const GLESGAE::Vector2& position);
		
		/// Get the position
		GLESGAE::Vector2 getPosition() const;
		
		/// Rotate the entity
		void rotate(const float radians);
		
		/// Translate
		void translate(const GLESGAE::Vector2& translate);
		
		/// Check collision
		bool collide(const GLESGAE::Resource<Entity>& entity);
		
		/// Set sphere collision size
		void setSphereSize(const float size) { mSphereSize = size; }
		
		/// Get sphere collision size
		float getSphereSize() const { return mSphereSize; }
		
		/// Set box collision size
		void setBoxSize(const GLESGAE::Vector2& size) { mBoxSize = size; }
		
		/// Get box collision size
		const GLESGAE::Vector2& getBoxSize() const { return mBoxSize; }
		
		/// Const access to the Mesh
		const GLESGAE::Resource<GLESGAE::Mesh>& getMesh() const { return mMesh; }
		
		/// Const access to the Transform
		const GLESGAE::Resource<GLESGAE::Matrix4>& getTransform() const { return mTransform; }
		
		/// Overloadable render function
		virtual void render();
		
		/// Overloadable update function
		virtual void update(const float delta);
		
		/// Get the type of Entity
		Type getType() const { return mType; }
		
		/// Get the tag
		Fingers::Entities::Tag getTag() const { return mTag; }
	
		// Move back
		void moveBack();
		
	protected:
		GLESGAE::Resource<GLESGAE::Mesh> mMesh;
		GLESGAE::Resource<GLESGAE::Matrix4> mTransform;
		Type mType;
		float mSphereSize;
		GLESGAE::Vector2 mBoxSize;
		Fingers::Entities::Tag mTag;
		GLESGAE::Vector3 mLastPosition;
		
};

#endif

