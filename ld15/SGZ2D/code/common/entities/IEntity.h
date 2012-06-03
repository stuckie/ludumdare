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

/**
	\file IEntity.h
	\brief The Entity Interface

*/

#ifndef _IENTITY_H_
#define _IENTITY_H_

#include <string>
#include "../../arch.h"
#include "../debug/CDebug.h"
#include "../data/CTimer.h"
#include "../data/CSLinkedlist.h"

class SGZAnimFrame2D
{
	public:
	SGZAnimFrame2D()
	:   frameNum(0),
		delay(0),
		u(),
		v(),
		colkey(),
		TextureName(),
		MaskName()
	{

	}

	~SGZAnimFrame2D()
	{
	}

	int frameNum,
		delay,
		u,
		v;

	SGZ::RGBCOLOUR colkey;

	std::string TextureName;
	std::string MaskName;
};

class SGZAnimGroup2D
{
	public:
	SGZAnimGroup2D()
	:   AnimName(),
		AnimNum(),
		CurAnim(),
		AnimTimer(),
		FrameList(),
		FrameITR()
	{
	}

	~SGZAnimGroup2D()
	{
	}

	std::string AnimName;
	int AnimNum;
	int CurAnim;
	SGZ::Timer AnimTimer;
	SLinkedList<SGZAnimFrame2D*> FrameList;
	SListIterator<SGZAnimFrame2D*> FrameITR;
};

class SGZVarGroup
{
	public:
		SGZVarGroup()
		:   Name(),
			Variable()
		{
		}

		~SGZVarGroup()
		{
		}

		std::string Name,
					Variable;
};

namespace SGZ {
class IEntity
{
	public:
	virtual ~IEntity() {}

	virtual bool Update ( float deltaTime ) = 0;
	/** Update our beloved entity */

	virtual bool Cleanup ( void ) = 0;
	/** Cleanup our mess */

	virtual bool MoveTo ( SGZ::VECTOR3 move ) = 0;
	/** Move to direct co-ordinates */

	virtual bool LookTo ( SGZ::VECTOR3 look ) = 0;
	/** Move towards co-ordinates */

	virtual bool MoveDelta  ( SGZ::VECTOR3 amount ) = 0;
	virtual bool MoveDeltaX ( SGZ::SCALER amount ) = 0;
	virtual bool MoveDeltaY ( SGZ::SCALER amount ) = 0;
	virtual bool MoveDeltaZ ( SGZ::SCALER amount ) = 0;
	/** Move a certain amount in a certain axis */

	virtual SGZ::SCALER GetX ( void ) = 0;
	virtual SGZ::SCALER GetY ( void ) = 0;
	virtual SGZ::SCALER GetZ ( void ) = 0;
	/** Return position data */

	virtual SGZ::SCALER GetWidth  ( void ) = 0;
	virtual SGZ::SCALER GetHeight ( void ) = 0;
	virtual SGZ::SCALER GetDepth  ( void ) = 0;
	virtual bool SetWidth  ( SGZ::SCALER value ) = 0;
	virtual bool SetHeight ( SGZ::SCALER value ) = 0;
	virtual bool SetDepth  ( SGZ::SCALER value ) = 0;
	/** Get some basic width/height info */

	virtual SGZ::SCALER GetLookX ( void ) = 0;
	virtual SGZ::SCALER GetLookY ( void ) = 0;
	virtual SGZ::SCALER GetLookZ ( void ) = 0;
	/** Return what we're looking at on specific axis */

	virtual bool Scale ( SGZ::SCALER value ) = 0;
	virtual bool ScaleX ( SGZ::SCALER value ) = 0;
	virtual bool ScaleY ( SGZ::SCALER value ) = 0;
	virtual bool ScaleZ ( SGZ::SCALER value ) = 0;
	virtual bool ScaleXYZ( SGZ::VECTOR3 value ) = 0;
	/** Scale overall or in a specified axis */

	virtual bool RotateX ( SGZ::SCALER value ) = 0;
	virtual bool RotateY ( SGZ::SCALER value ) = 0;
	virtual bool RotateZ ( SGZ::SCALER value ) = 0;
	virtual bool Rotate  ( SGZ::VECTOR3 value ) = 0;
	/** Rotate on a specific axis */

	virtual bool MaxAccel ( SGZ::SCALER value ) = 0;
	virtual bool MaxSpeed ( SGZ::SCALER value ) = 0;
	virtual bool SetSpeed ( SGZ::SCALER value ) = 0;
	virtual SGZ::SCALER GetSpeed ( void ) = 0;
	virtual SGZ::SCALER GetAccel ( void ) = 0;
	virtual bool SetAccel ( SGZ::SCALER value ) = 0;
	/** Accelerate a certain value "forward" */

	virtual bool Stop ( void ) = 0;
	/** Stop moving/rotating/scaling immediately */

	virtual bool SetCollisionGeom ( int type ) = 0;
	/** Set the collision type */

	virtual bool LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int u, int v, SGZ::RGBCOLOUR ColourKey ) = 0;
	/** Load in a Texture */

	virtual bool CreateAnimation( std::string Name ) = 0;
	virtual bool SetAnimation( std::string Name ) = 0;
	virtual bool DeleteAnimation( std::string Name ) = 0;
	virtual std::string GetAnimation( void ) = 0;

	virtual bool SetName( std::string Name ) = 0;
	virtual std::string GetName ( void ) = 0;

	virtual bool Colour ( SGZ::RGBCOLOUR col ) = 0;
	virtual bool ChangeColour( SGZ::RGBCOLOUR oldColour, SGZ::RGBCOLOUR newColour ) = 0;

	virtual std::string CheckVar ( std::string VarName ) = 0;
	virtual bool NewVar( std::string VarName ) = 0;
	virtual bool DeleteVar( std::string VarName ) = 0;
	virtual bool ChangeVar( std::string VarName, std::string Value ) = 0;
};
}
#endif
