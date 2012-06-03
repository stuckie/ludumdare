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
*/#include "HordeEntity3D.h"

#if defined(REND_HORDE) || defined(REND_SDLHORDE)
HordeEntity3D::HordeEntity3D()
{
}

HordeEntity3D::~HordeEntity3D()
{
}

bool HordeEntity3D::Update ( void )
{
    /** Update our beloved entity */
    return true;
}

bool HordeEntity3D::Cleanup ( void )
{
    /** Clean up our entity mess! */
    return true;
}

bool HordeEntity3D::MoveTo ( SGZ::VECTOR3 move )
{
    /** Move to direct co-ordinates */
    position = move;
    return true;
}

bool HordeEntity3D::LookTo ( SGZ::VECTOR3 look )
{
    /** Direction to look at ( move towards ) */
    looking = look;
    return true;
}

bool HordeEntity3D::MoveDeltaX ( SGZ::SCALER amount )
{
    /** Move a certain amount in X axis */
    position.x += amount;
    return true;
}

bool HordeEntity3D::MoveDeltaY ( SGZ::SCALER amount )
{
    /** Move a certain amount in Y axis */
    position.y += amount;
    return true;
}

bool HordeEntity3D::MoveDeltaZ ( SGZ::SCALER amount )
{
    /** Move a certain amout in Z axis */
    position.z += amount;
    return true;
}

bool HordeEntity3D::MoveDelta ( SGZ::VECTOR3 vector )
{
    position.x += vector.x;
    position.y += vector.y;
    position.z += vector.z;

    return true;
}

bool HordeEntity3D::Scale ( SGZ::SCALER value )
{
    /** Scale the entity overall */
    scale.x = value;
    scale.y = value;
    scale.z = value;

    return true;
}

bool HordeEntity3D::ScaleX ( SGZ::SCALER value )
{
    /** Scale in X-axis */
    scale.x = value;

    return true;
}

bool HordeEntity3D::ScaleY ( SGZ::SCALER value )
{
    /** Scale in Y-Axis */
    scale.y = value;

    return true;
}

bool HordeEntity3D::ScaleZ ( SGZ::SCALER value )
{
    /** Scale in Z axis */
    scale.z = value;

    return true;
}

bool HordeEntity3D::ScaleXYZ( SGZ::VECTOR3 vector )
{
    scale = vector;

    return true;
}

bool HordeEntity3D::RotateX ( SGZ::SCALER value )
{
    /** Rotate in X Axis */
    rotation.x += value;

    return true;
}

bool HordeEntity3D::RotateY ( SGZ::SCALER value )
{
    /** Rotate in Y axis */
    rotation.y += value;

    return true;
}

bool HordeEntity3D::RotateZ ( SGZ::SCALER value )
{
    rotation.z += value;

    return true;
}

bool HordeEntity3D::Rotate( SGZ::VECTOR3 vector)
{
    rotation = vector;

    return true;
}

bool HordeEntity3D::MaxAccel ( SGZ::SCALER value )
{
    entityMaxAccel = value;

    return true;
}

bool HordeEntity3D::SetAccel ( SGZ::SCALER value )
{
    entityAccel = value;

    return true;
}

bool HordeEntity3D::MaxSpeed ( SGZ::SCALER value )
{
    entityMaxSpeed = value;

    return true;
}

bool HordeEntity3D::SetSpeed ( SGZ::SCALER value )
{
    entitySpeed = value;

    return true;
}

bool HordeEntity3D::SetWidth ( SGZ::SCALER value )
{
    entityWidth = value;

    return true;
}

bool HordeEntity3D::SetHeight ( SGZ::SCALER value )
{
    entityHeight = value;

    return true;
}

bool HordeEntity3D::SetDepth ( SGZ::SCALER value )
{
    entityDepth = value;

    return true;
}

bool HordeEntity3D::Stop ( void )
{
    /** Stop moving/rotating/scaling immediately */
    entitySpeed = 0;

    return true;
}

bool HordeEntity3D::SetCollisionGeom ( int type )
{
    /** Set the collision type */
    entityType = type;

    return true;
}

bool HordeEntity3D::SetAnimation( std::string Name )
{
    animName = Name;

    return true;
}

bool HordeEntity3D::CreateAnimation( std::string Name )
{
    Logger.log( SGZLOG::Warning, "CreateAnim in 3D Entity not created.. anim name would've been %s\n", Name.c_str());

    return true;
}

bool HordeEntity3D::DeleteAnimation( std::string Name )
{
    Logger.log( SGZLOG::Warning, "DelAnim in 3D Entity not created.. anim name would've been %s\n", Name.c_str());
    return true;
}

bool HordeEntity3D::LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int u, int v, SGZ::RGBCOLOUR ColourKey )
{
    Logger.log( SGZLOG::Warning, "LoadFrame in 3D Entity not created..\n%s %s %s %d %d %d %f %f %f", Name.c_str(), TexName.c_str(), MaskName.c_str(), FrameDelay, u, v, ColourKey.r, ColourKey.g, ColourKey.b);
    return true;
}


bool HordeEntity3D::Colour ( SGZ::RGBCOLOUR col )
{
    colkey = col;
    return true;
}

std::string HordeEntity3D::CheckVar(std::string VarName)
{
    Logger.log( SGZLOG::Warning, "CheckVar in 3D Entity not created.. val would've been %s\n", VarName.c_str());
    return "none";
}

bool HordeEntity3D::NewVar(std::string VarName)
{
    Logger.log( SGZLOG::Warning, "NewVar in 3D Entity not created.. val would've been %s\n", VarName.c_str());
    return true;
}

bool HordeEntity3D::DeleteVar(std::string VarName)
{
    Logger.log( SGZLOG::Warning, "DeleteVar in 3D Entity not created.. val would've been %s\n", VarName.c_str());
    return true;
}

bool HordeEntity3D::ChangeVar(std::string VarName, std::string Value)
{
    Logger.log( SGZLOG::Warning, "ChangeVar in 3D Entity not created.. val would've been %s as %s\n", VarName.c_str(), Value.c_str());
    return true;
}

std::string HordeEntity3D::GetName( void )
{
    return entityName;
}

bool HordeEntity3D::SetName(std::string Name)
{
    entityName = Name;
    return true;
}

std::string HordeEntity3D::GetAnimation( void )
{
    return animName;
}

SGZ::SCALER HordeEntity3D::GetAccel( void )
{
    return entityAccel;
}

SGZ::SCALER HordeEntity3D::GetSpeed( void )
{
    return entitySpeed;
}

SGZ::SCALER HordeEntity3D::GetLookX( void )
{
    return looking.x;
}

SGZ::SCALER HordeEntity3D::GetLookY( void )
{
    return looking.y;
}

SGZ::SCALER HordeEntity3D::GetLookZ( void )
{
    return looking.z;
}

SGZ::SCALER HordeEntity3D::GetDepth( void )
{
    return entityDepth;
}

SGZ::SCALER HordeEntity3D::GetWidth( void )
{
    return entityWidth;
}


SGZ::SCALER HordeEntity3D::GetHeight( void )
{
    return entityHeight;
}

SGZ::SCALER HordeEntity3D::GetX( void )
{
    return position.x;
}

SGZ::SCALER HordeEntity3D::GetY( void )
{
    return position.y;
}

SGZ::SCALER HordeEntity3D::GetZ( void )
{
    return position.z;
}

#endif
