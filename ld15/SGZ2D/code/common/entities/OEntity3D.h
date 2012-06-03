/*
	SGZEngine
	Copyright (C) 2008 - 2009 Steven Campbell

	This engine is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this engine; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

	Steven Campbell
	stuckie@stuckiegamez.co.uk
*/

#ifndef _3DENTITY_H_
#define _3DENTITY_H_

#ifdef SGZ3D

#include "../../arch.h"
#include "../../common/entities/IEntity.h"

#if defined(REND_OGRE) || defined (REND_SDLORGRE) || defined (REND_OPENGL) || defined (REND_SDLGL)

#if defined(REND_OGRE) || defined(REND_SDLOGRE)
	#include "OGREEntity3D.h"
#endif

#if defined(REND_OPENGL) || defined(REND_SDLGL)
	#include "GLEntity3D.h"
#endif

class OEntity3D : public SGZ::IEntity
{
	public:
	OEntity3D() { };
	OEntity3D( std::string Name ) { Entity.SetName(Name); };
	~OEntity3D() { Cleanup(); };

	bool Update ( float deltaTime );
	/** Update our beloved entity */

	bool Cleanup ( void );
	/** Clean up our entity mess! */

	bool MoveTo ( SGZ::VECTOR3 move );
	/** Move to direct co-ordinates */

	bool LookTo ( SGZ::VECTOR3 look );
	/** Direction to look at ( move towards ) */

	bool MoveDelta  ( SGZ::VECTOR3 amount );
	bool MoveDeltaX ( SGZ::SCALER amount );
	bool MoveDeltaY ( SGZ::SCALER amount );
	bool MoveDeltaZ ( SGZ::SCALER amount );
	/** Move a certain amount in a certain axis */

	SGZ::SCALER GetX ( void ) { return Entity.GetX(); };
	SGZ::SCALER GetY ( void ) { return Entity.GetY(); };
	SGZ::SCALER GetZ ( void ) { return Entity.GetZ(); };
	/** Return position data */

	SGZ::SCALER GetWidth  ( void ) { return Entity.GetWidth(); };
	SGZ::SCALER GetHeight ( void ) { return Entity.GetHeight(); };
	SGZ::SCALER GetDepth  ( void ) { return Entity.GetDepth(); };

	bool SetWidth ( SGZ::SCALER value );
	bool SetHeight ( SGZ::SCALER value );
	bool SetDepth ( SGZ::SCALER value );

	SGZ::SCALER GetLookX ( void ) { return Entity.GetLookX(); };
	SGZ::SCALER GetLookY ( void ) { return Entity.GetLookY(); };
	SGZ::SCALER GetLookZ ( void ) { return Entity.GetLookZ(); };

	bool Scale ( SGZ::SCALER value );
	bool ScaleX ( SGZ::SCALER value );
	bool ScaleY ( SGZ::SCALER value );
	bool ScaleZ ( SGZ::SCALER value );
	bool ScaleXYZ ( SGZ::VECTOR3 value );
	/** Scale overall or in a specified axis */

	bool Rotate  ( SGZ::VECTOR3 value );
	bool RotateX ( SGZ::SCALER value );
	bool RotateY ( SGZ::SCALER value );
	bool RotateZ ( SGZ::SCALER value );
	/** Rotate on a specific axis */

	bool MaxAccel ( SGZ::SCALER value );
	bool MaxSpeed ( SGZ::SCALER value );
	bool SetSpeed ( SGZ::SCALER value );
	SGZ::SCALER GetSpeed ( void ) { return Entity.GetSpeed(); };
	SGZ::SCALER GetAccel ( void ) { return Entity.GetAccel(); };
	bool SetAccel ( SGZ::SCALER value );
	/** Accelerate a certain value "forward" */

	bool Stop ( void );
	/** Stop moving/rotating/scaling immediately */

	bool SetCollisionGeom ( int type );
	/** Set the collision type */

	std::string GetAnimation( void ) { return Entity.GetAnimation(); };
	bool SetAnimation( std::string Name );
	bool CreateAnimation( std::string Name );
	bool DeleteAnimation( std::string Name );
	bool LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int u, int v, SGZ::RGBCOLOUR ColourKey );
	/** Load up a Texture into an Animation*/

	bool SetName( std::string Name ) { return Entity.SetName(Name); };
	std::string GetName ( void ) { return Entity.GetName(); };
	/** Reset Name, or Return the Name */

	bool Colour ( SGZ::RGBCOLOUR col );

	std::string CheckVar ( std::string VarName );
	bool NewVar( std::string VarName );
	bool DeleteVar( std::string VarName );
	bool ChangeVar( std::string VarName, std::string Value );


	private:
	#if defined(REND_OGRE) || defined(REND_SDLOGRE)
		OGREEntity3D Entity;
	#endif

	#if defined(REND_OPENGL) || defined(REND_SDLGL)
		GLEntity3D Entity;
	#endif


};

#endif
#endif
#endif
