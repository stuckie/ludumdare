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

#ifndef _SDLENTITY2D_H_
#define _SDLENTITY2D_H_

#include "../../../common/entities/IEntity.h"
#include "../../../arch.h"
#include "../../../client/renderer/texture/OTexture.h"
#include "../../../common/data/CSLinkedlist.h"
#include "../../../common/debug/CDebug.h"
#include "../../../common/engine/CInterpret.h"
#include "../../../common/data/CTimer.h"

struct AnimGroup
{
	std::string AnimName;
	int AnimNum;
	int CurAnim;
	SLinkedList<OTexture*> TEXList;		 //!< List of SFX
	SListIterator<OTexture*> TEXListITR;	//!< Iterator to the SFX List
};

class SDLEntity2D : public SGZ::IEntity
{
	private:
	std::string entityName;
	/** Our Name */

	std::string CurrentAnim;
	/** Currently Playing Animation */

	SGZ::VECTOR3 position;
	/** Our Position in the world! */

	SGZ::VECTOR3 looking;
	/** Where we're looking */

	SGZ::VECTOR3 velocity;
	/** The direction we're travelling */

	SGZ::SCALER entitySpeed, entityAccel, maxEntityAccel, maxEntitySpeed;
	/** Our speed and acceleration */

	SGZ::VECTOR3 size;
	/** Our size */

	SGZ::RGBCOLOUR col, oldColour, newColour;

	SDL_Rect offset, frame;

	SGZ::SCALER angle, zoomX, zoomY;

	SGZ::SCALER smooth, entityDepth, entityWidth, entityHeight;

	SDL_Surface *CurrentFrame, *TempFrame;				  //!< Current Frame to Render

	SLinkedList<SGZAnimGroup2D*> AnimList;		 //!< List of Animations
	SLinkedList<SGZVarGroup*> VarList;		 //!< list of custom variables for this entity

	float mDeltaTime;

	public:

	SDLEntity2D()
	:   entityName(),
		CurrentAnim(),
		position(),
		looking(),
		velocity(),
		entitySpeed(),
		entityAccel(),
		maxEntityAccel(),
		maxEntitySpeed(),
		size(),
		col(),
		oldColour(),
		newColour(),
		offset(),
		frame(),
		angle(),
		zoomX(),
		zoomY(),
		smooth(),
		entityDepth(),
		entityWidth(),
		entityHeight(),
		CurrentFrame(),
		TempFrame(),
		AnimList(),
		VarList(),
		mDeltaTime(0)
	{
		/* nope */
	}

	SDLEntity2D(const std::string &pName)
	:   entityName(pName),
		CurrentAnim(),
		position(),
		looking(),
		velocity(),
		entitySpeed(0.0f),
		entityAccel(0.0f),
		maxEntityAccel(),
		maxEntitySpeed(),
		size(),
		col(),
		oldColour(),
		newColour(),
		offset(),
		frame(),
		angle(0),
		zoomX(1),
		zoomY(1),
		smooth(),
		entityDepth(0),
		entityWidth(32),
		entityHeight(32),
		CurrentFrame(),
		TempFrame(),
		AnimList(),
		VarList(),
		mDeltaTime(0)
	{
		/* nope */
	}

	SDLEntity2D( const SDLEntity2D& )
	:   entityName(),
		CurrentAnim(),
		position(),
		looking(),
		velocity(),
		entitySpeed(),
		entityAccel(),
		maxEntityAccel(),
		maxEntitySpeed(),
		size(),
		col(),
		oldColour(),
		newColour(),
		offset(),
		frame(),
		angle(),
		zoomX(),
		zoomY(),
		smooth(),
		entityDepth(),
		entityWidth(),
		entityHeight(),
		CurrentFrame(),
		TempFrame(),
		AnimList(),
		VarList(),
		mDeltaTime(0)
	{
		/* nope */
	}

	SDLEntity2D operator=( const SDLEntity2D& )
	{
		throw("");
	}


	~SDLEntity2D()
	{
		Cleanup();
	}

	bool Update ( float deltaTime );
	/** Update our beloved entity */

	bool Cleanup ( void );
	/** Clean up our entity mess! */

	bool MoveTo ( SGZ::VECTOR3 vector );
	/** Move to direct co-ordinates */

	bool LookTo ( SGZ::VECTOR3 vector );
	/** Direction to look at ( move towards ) */

	bool MoveDelta  ( SGZ::VECTOR3 vector );
	bool MoveDeltaX ( SGZ::SCALER amount );
	bool MoveDeltaY ( SGZ::SCALER amount );
	bool MoveDeltaZ ( SGZ::SCALER amount );
	/** Move a certain amount in a certain axis */

	SGZ::SCALER GetWidth( void );
	SGZ::SCALER GetHeight( void );
	SGZ::SCALER GetDepth( void );
	bool SetWidth ( SGZ::SCALER value );
	bool SetHeight( SGZ::SCALER value );
	bool SetDepth ( SGZ::SCALER value );
	/** Grab the width/height of current frame */

	SGZ::SCALER GetX ( void );
	SGZ::SCALER GetY ( void );
	SGZ::SCALER GetZ ( void );
	/** Return position data */

	SGZ::SCALER GetLookX ( void );
	SGZ::SCALER GetLookY ( void );
	SGZ::SCALER GetLookZ ( void );

	bool Scale ( SGZ::SCALER value );
	bool ScaleX ( SGZ::SCALER value );
	bool ScaleY ( SGZ::SCALER value );
	bool ScaleZ ( SGZ::SCALER value );
	bool ScaleXYZ ( SGZ::VECTOR3 vector );
	/** Scale overall or in a specified axis */

	bool RotateX ( SGZ::SCALER value );
	bool RotateY ( SGZ::SCALER value );
	bool RotateZ ( SGZ::SCALER value );
	bool Rotate  ( SGZ::VECTOR3 vector );
	/** Rotate on a specific axis */

	bool MaxAccel ( SGZ::SCALER value );
	bool MaxSpeed ( SGZ::SCALER value );
	bool SetSpeed ( SGZ::SCALER value );
	SGZ::SCALER GetSpeed ( void );
	SGZ::SCALER GetAccel ( void );
	bool SetAccel ( SGZ::SCALER value );
	/** Accelerate a certain value "forward" */

	bool Stop ( void );
	/** Stop moving/rotating/scaling immediately */

	bool SetCollisionGeom ( int type );
	/** Set the collision type */

	std::string GetAnimation( void );
	bool SetAnimation( std::string Name );
	bool CreateAnimation( std::string Name );
	bool DeleteAnimation( std::string Name );
	bool LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int x, int y, SGZ::RGBCOLOUR ColourKey );
	/** Load up a Texture into an Animation*/

	bool SetName( std::string Name );
	std::string GetName ( void );
	/** Reset Name, or Return the Name */

	bool Colour(SGZ::RGBCOLOUR colour);
	bool ChangeColour(SGZ::RGBCOLOUR oldColour, SGZ::RGBCOLOUR newColour);
	std::string CheckVar ( std::string VarName );
	bool NewVar( std::string VarName );
	bool DeleteVar( std::string VarName );
	bool ChangeVar( std::string VarName, std::string Value );


};

#endif
