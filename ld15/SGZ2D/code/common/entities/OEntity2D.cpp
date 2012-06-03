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

#include "OEntity2D.h"

#if defined (REND_SDL) || defined(REND_SDLOGRE) || defined(REND_SDLGL) || defined(REND_OPENGL) || defined(REND_OGRE)

bool OEntity2D::Update ( float deltaTime )
{
	/** Update our beloved entity */
	return Entity.Update(deltaTime);
}

bool OEntity2D::Cleanup ( void )
{
	/** Clean up our entity mess! */
	return Entity.Cleanup();
}

bool OEntity2D::MoveTo ( SGZ::VECTOR3 move )
{
	/** Move to direct co-ordinates */
	return Entity.MoveTo(move);
}

bool OEntity2D::LookTo ( SGZ::VECTOR3 look )
{
	/** Direction to look at ( move towards ) */
	return Entity.LookTo(look);
}

bool OEntity2D::MoveDeltaX ( SGZ::SCALER amount )
{
	/** Move a certain amount in X axis */
	return Entity.MoveDeltaX(amount);
}

bool OEntity2D::MoveDeltaY ( SGZ::SCALER amount )
{
	/** Move a certain amount in Y axis */
	return Entity.MoveDeltaY(amount);
}

bool OEntity2D::MoveDeltaZ ( SGZ::SCALER amount )
{
	/** Move a certain amout in Z axis */
	return Entity.MoveDeltaZ(amount);
}

bool OEntity2D::MoveDelta ( SGZ::VECTOR3 vector )
{
	return Entity.MoveDelta(vector);
}

bool OEntity2D::Scale ( SGZ::SCALER value )
{
	/** Scale the entity overall */
	return Entity.Scale(value);
}

bool OEntity2D::ScaleX ( SGZ::SCALER value )
{
	/** Scale in X-axis */
	return Entity.ScaleX(value);
}

bool OEntity2D::ScaleY ( SGZ::SCALER value )
{
	/** Scale in Y-Axis */
	return Entity.ScaleY(value);
}

bool OEntity2D::ScaleZ ( SGZ::SCALER value )
{
	/** Scale in Z axis */
	return Entity.ScaleZ(value);
}

bool OEntity2D::ScaleXYZ( SGZ::VECTOR3 vector )
{
	return Entity.ScaleXYZ(vector);
}

bool OEntity2D::RotateX ( SGZ::SCALER value )
{
	/** Rotate in X Axis */
	return Entity.RotateX(value);
}

bool OEntity2D::RotateY ( SGZ::SCALER value )
{
	/** Rotate in Y axis */
	return Entity.RotateY(value);
}

bool OEntity2D::RotateZ ( SGZ::SCALER value )
{
	return Entity.RotateZ(value);
}

bool OEntity2D::Rotate( SGZ::VECTOR3 vector)
{
	return Entity.Rotate(vector);
}

bool OEntity2D::MaxAccel ( SGZ::SCALER value )
{
	return Entity.MaxAccel(value);
}

bool OEntity2D::SetAccel ( SGZ::SCALER value )
{
	return Entity.SetAccel(value);
}

bool OEntity2D::MaxSpeed ( SGZ::SCALER value )
{
	return Entity.MaxSpeed(value);
}

bool OEntity2D::SetSpeed ( SGZ::SCALER value )
{
	return Entity.SetSpeed(value);
}

bool OEntity2D::SetWidth ( SGZ::SCALER value )
{
	return Entity.SetWidth(value);
}

bool OEntity2D::SetHeight ( SGZ::SCALER value )
{
	return Entity.SetHeight(value);
}

bool OEntity2D::SetDepth ( SGZ::SCALER value )
{
	return Entity.SetDepth(value);
}

bool OEntity2D::Stop ( void )
{
	/** Stop moving/rotating/scaling immediately */
	return Entity.Stop();
}

bool OEntity2D::SetCollisionGeom ( int type )
{
	/** Set the collision type */
	return Entity.SetCollisionGeom(type);
}

bool OEntity2D::SetAnimation( std::string Name )
{
	return Entity.SetAnimation(Name);
}

bool OEntity2D::CreateAnimation( std::string Name )
{
	return Entity.CreateAnimation(Name);
}

bool OEntity2D::DeleteAnimation( std::string Name )
{
	return Entity.DeleteAnimation(Name);
}

bool OEntity2D::LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int u, int v, SGZ::RGBCOLOUR ColourKey )
{
	return Entity.LoadFrame(Name,TexName,MaskName,FrameDelay,u,v,ColourKey);
}


bool OEntity2D::Colour ( SGZ::RGBCOLOUR col )
{
	return Entity.Colour(col);
}

bool OEntity2D::ChangeColour( SGZ::RGBCOLOUR oldColour, SGZ::RGBCOLOUR newColour )
{
	return Entity.ChangeColour(oldColour, newColour);
}

std::string OEntity2D::CheckVar(std::string VarName)
{
	return Entity.CheckVar(VarName);
}

bool OEntity2D::NewVar(std::string VarName)
{
	return Entity.NewVar(VarName);
}

bool OEntity2D::DeleteVar(std::string VarName)
{
	return Entity.DeleteVar(VarName);
}

bool OEntity2D::ChangeVar(std::string VarName, std::string Value)
{
	return Entity.ChangeVar(VarName,Value);
}

#endif
