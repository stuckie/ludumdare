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

#include "OEntity3D.h"

#if defined(REND_OGRE) || defined (REND_SDLORGRE) || defined (REND_OPENGL) || defined (REND_SDLGL)

bool OEntity3D::Update ( float deltaTime )
{
	/** Update our beloved entity */
	return Entity.Update(deltaTime);
}

bool OEntity3D::Cleanup ( void )
{
	/** Clean up our entity mess! */
	return Entity.Cleanup();
}

bool OEntity3D::MoveTo ( SGZ::VECTOR3 move )
{
	/** Move to direct co-ordinates */
	return Entity.MoveTo(move);
}

bool OEntity3D::LookTo ( SGZ::VECTOR3 look )
{
	/** Direction to look at ( move towards ) */
	return Entity.LookTo(look);
}

bool OEntity3D::MoveDeltaX ( SGZ::SCALER amount )
{
	/** Move a certain amount in X axis */
	return Entity.MoveDeltaX(amount);
}

bool OEntity3D::MoveDeltaY ( SGZ::SCALER amount )
{
	/** Move a certain amount in Y axis */
	return Entity.MoveDeltaY(amount);
}

bool OEntity3D::MoveDeltaZ ( SGZ::SCALER amount )
{
	/** Move a certain amout in Z axis */
	return Entity.MoveDeltaZ(amount);
}

bool OEntity3D::MoveDelta ( SGZ::VECTOR3 vector )
{
	return Entity.MoveDelta(vector);
}

bool OEntity3D::Scale ( SGZ::SCALER value )
{
	/** Scale the entity overall */
	return Entity.Scale(value);
}

bool OEntity3D::ScaleX ( SGZ::SCALER value )
{
	/** Scale in X-axis */
	return Entity.ScaleX(value);
}

bool OEntity3D::ScaleY ( SGZ::SCALER value )
{
	/** Scale in Y-Axis */
	return Entity.ScaleY(value);
}

bool OEntity3D::ScaleZ ( SGZ::SCALER value )
{
	/** Scale in Z axis */
	return Entity.ScaleZ(value);
}

bool OEntity3D::ScaleXYZ( SGZ::VECTOR3 vector )
{
	return Entity.ScaleXYZ(vector);
}

bool OEntity3D::RotateX ( SGZ::SCALER value )
{
	/** Rotate in X Axis */
	return Entity.RotateX(value);
}

bool OEntity3D::RotateY ( SGZ::SCALER value )
{
	/** Rotate in Y axis */
	return Entity.RotateY(value);
}

bool OEntity3D::RotateZ ( SGZ::SCALER value )
{
	return Entity.RotateZ(value);
}

bool OEntity3D::Rotate( SGZ::VECTOR3 vector)
{
	return Entity.Rotate(vector);
}

bool OEntity3D::MaxAccel ( SGZ::SCALER value )
{
	return Entity.MaxAccel(value);
}

bool OEntity3D::SetAccel ( SGZ::SCALER value )
{
	return Entity.SetAccel(value);
}

bool OEntity3D::MaxSpeed ( SGZ::SCALER value )
{
	return Entity.MaxSpeed(value);
}

bool OEntity3D::SetSpeed ( SGZ::SCALER value )
{
	return Entity.SetSpeed(value);
}

bool OEntity3D::SetWidth ( SGZ::SCALER value )
{
	return Entity.SetWidth(value);
}

bool OEntity3D::SetHeight ( SGZ::SCALER value )
{
	return Entity.SetHeight(value);
}

bool OEntity3D::SetDepth ( SGZ::SCALER value )
{
	return Entity.SetDepth(value);
}

bool OEntity3D::Stop ( void )
{
	/** Stop moving/rotating/scaling immediately */
	return Entity.Stop();
}

bool OEntity3D::SetCollisionGeom ( int type )
{
	/** Set the collision type */
	return Entity.SetCollisionGeom(type);
}

bool OEntity3D::SetAnimation( std::string Name )
{
	return Entity.SetAnimation(Name);
}

bool OEntity3D::CreateAnimation( std::string Name )
{
	return Entity.CreateAnimation(Name);
}

bool OEntity3D::DeleteAnimation( std::string Name )
{
	return Entity.DeleteAnimation(Name);
}

bool OEntity3D::LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int u, int v, SGZ::RGBCOLOUR ColourKey )
{
	return Entity.LoadFrame(Name,TexName,MaskName,FrameDelay,u,v,ColourKey);
}


bool OEntity3D::Colour ( SGZ::RGBCOLOUR col )
{
	return Entity.Colour(col);
}

std::string OEntity3D::CheckVar(std::string VarName)
{
	return Entity.CheckVar(VarName);
}

bool OEntity3D::NewVar(std::string VarName)
{
	return Entity.NewVar(VarName);
}

bool OEntity3D::DeleteVar(std::string VarName)
{
	return Entity.DeleteVar(VarName);
}

bool OEntity3D::ChangeVar(std::string VarName, std::string Value)
{
	return Entity.ChangeVar(VarName,Value);
}

#endif
