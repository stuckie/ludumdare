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
*//*
    SGZEngine
    Copyright (C) 2008 Steven Campbell

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
    \file HordeEntity2D.h
    \brief Horde's 2D Entity Layer

*/

#include "../../../arch.h"

#if defined(REND_HORDE) || defined(REND_SDLHORDE)
#ifndef _HORDE_ENTITY2D_
#define _HORDE_ENTITY2D_

#include "../../../common/entities/IEntity.h"

class HordeEntity2D : public IEntity
{
    public:
    HordeEntity2D();
    ~HordeEntity2D();

    bool Update ( void );
    /** Update our beloved entity */

    bool Cleanup ( void );
    /** Cleanup our mess */

    bool MoveTo ( SGZ::VECTOR3 move );
    /** Move to direct co-ordinates */

    bool LookTo ( SGZ::VECTOR3 look );
    /** Move towards co-ordinates */

    bool MoveDelta  ( SGZ::VECTOR3 amount );
    bool MoveDeltaX ( SGZ::SCALER amount );
    bool MoveDeltaY ( SGZ::SCALER amount );
    bool MoveDeltaZ ( SGZ::SCALER amount );
    /** Move a certain amount in a certain axis */

    SGZ::SCALER GetX ( void );
    SGZ::SCALER GetY ( void );
    SGZ::SCALER GetZ ( void );
    /** Return position data */

    SGZ::SCALER GetWidth  ( void );
    SGZ::SCALER GetHeight ( void );
    SGZ::SCALER GetDepth  ( void );
    bool SetWidth  ( SGZ::SCALER value );
    bool SetHeight ( SGZ::SCALER value );
    bool SetDepth  ( SGZ::SCALER value );
    /** Get some basic width/height info */

    SGZ::SCALER GetLookX ( void );
    SGZ::SCALER GetLookY ( void );
    SGZ::SCALER GetLookZ ( void );
    /** Return what we're looking at on specific axis */

    bool Scale ( SGZ::SCALER value );
    bool ScaleX ( SGZ::SCALER value );
    bool ScaleY ( SGZ::SCALER value );
    bool ScaleZ ( SGZ::SCALER value );
    bool ScaleXYZ( SGZ::VECTOR3 value );
    /** Scale overall or in a specified axis */

    bool RotateX ( SGZ::SCALER value );
    bool RotateY ( SGZ::SCALER value );
    bool RotateZ ( SGZ::SCALER value );
    bool Rotate  ( SGZ::VECTOR3 value );
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

    bool LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int u, int v, SGZ::RGBCOLOUR ColourKey );
    /** Load in a Texture */

    bool CreateAnimation( std::string Name );
    bool SetAnimation( std::string Name );
    bool DeleteAnimation( std::string Name );
    std::string GetAnimation( void );

    bool SetName( std::string Name );
    std::string GetName ( void );

    bool Colour ( SGZ::RGBCOLOUR col );

    std::string CheckVar ( std::string VarName );
    bool NewVar( std::string VarName );
    bool DeleteVar( std::string VarName );
    bool ChangeVar( std::string VarName, std::string Value );

    private:

    std::string entityName, animName;

    SGZ::SCALER entitySpeed, entityMaxSpeed, entityAccel, entityMaxAccel, entityWidth, entityDepth, entityHeight;

    SGZ::VECTOR3 position, looking, scale, rotation;

    int entityType;

    SGZ::RGBCOLOUR colkey;

};

#endif // _HORDE_ENTITY2D_

#endif // REND_HORDE
