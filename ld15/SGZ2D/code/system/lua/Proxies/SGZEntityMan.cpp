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

#include "SGZEntityMan.h"
#include "../../../typedefs.h"
#include "../../../common/debug/CDebug.h"
#include "../../../common/engine/CInterpret.h"
#include "../../../common/entities/OEntity2D.h"
#include "../../../common/entities/OEntity3D.h"
#include "../../../server/OServer.h"
#include "../../../server/gameServer/GameServer.h"
#include "../../../server/managers/entityManager/MEntity.h"

#if defined (SGZ2D)
int SGZEntityMan_Proxy::add2DEntity( lua_State *Lua )
{
	int values = lua_gettop(Lua);
	if (manEntities->getEntityCount() < manEntities->getCurrentMaxEntities())
	{
		if (values>0)
		{
			OEntity2D *NewEntity = new OEntity2D(lua_tostring(Lua, -1) );
			manEntities->addEntity(NewEntity);
		}
	}
	else SGZ::Logger.log( SGZLOG::Warning, "Max Entities Reached!\n");

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}
#endif

#if defined (SGZ3D) && defined (somethingelse)
int SGZEntityMan_Proxy::add3DEntity( lua_State *Lua )
{
	int values = lua_gettop(Lua);
	if (values>0)
	{
		OEntity3D *NewEntity = new OEntity3D(lua_tostring(Lua, -1) );
		manEntities->AddEntity(NewEntity);

		for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	}

	return 0;
}
#endif

int SGZEntityMan_Proxy::delEntity( lua_State *Lua )
{
	manEntities->delEntity(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::update(lua_State *Lua)
{
	/** Update our beloved entity */
//	manEntities->updateEntities();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::moveTo (lua_State *Lua)
{
	/** Move to direct co-ordinates */
	SGZ::VECTOR3 move;
	move.x = (SGZ::SCALER)lua_tonumber(Lua, -3);
	move.y = (SGZ::SCALER)lua_tonumber(Lua, -2);
	move.z = (SGZ::SCALER)lua_tonumber(Lua, -1);
	manEntities->moveTo( lua_tostring(Lua, -4), move );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::lookTo (lua_State *Lua)
{
	/** Direction to look at ( move towards ) */
	SGZ::VECTOR3 look;
	look.x = (SGZ::SCALER)lua_tonumber(Lua, -3);
	look.y = (SGZ::SCALER)lua_tonumber(Lua, -2);
	look.z = (SGZ::SCALER)lua_tonumber(Lua, -1);
	manEntities->lookTo( lua_tostring(Lua, -4), look );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);
	return 0;
}

int SGZEntityMan_Proxy::moveDelta (lua_State *Lua)
{
	/** Move a certain amount in a certain axis */
	SGZ::VECTOR3 delta;
	delta.x = (SGZ::SCALER)lua_tonumber(Lua, -3);
	delta.y = (SGZ::SCALER)lua_tonumber(Lua, -2);
	delta.z = (SGZ::SCALER)lua_tonumber(Lua, -1);
	manEntities->moveDelta( lua_tostring(Lua, -4), delta );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::getWidth ( lua_State *Lua )
{
	/** Get the Width of the entity */

	SGZ::SCALER value = manEntities->getDimensions(lua_tostring(Lua, -1)).x;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getHeight ( lua_State *Lua )
{
	/** Get the Width of the entity */

	SGZ::SCALER value = manEntities->getDimensions(lua_tostring(Lua, -1)).y;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getDepth ( lua_State *Lua )
{
	/** Get the Width of the entity */

	SGZ::SCALER value = manEntities->getDimensions(lua_tostring(Lua, -1)).z;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getX ( lua_State *Lua )
{
	/** Return position data */
	SGZ::SCALER value = manEntities->getPosition(lua_tostring(Lua, -1)).x;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getY ( lua_State *Lua )
{
	/** Return position data */
	SGZ::SCALER value = manEntities->getPosition(lua_tostring(Lua, -1)).y;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getZ ( lua_State *Lua )
{
	/** Return position data */
	SGZ::SCALER value = manEntities->getPosition(lua_tostring(Lua, -1)).z;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getLookX ( lua_State *Lua )
{
	/** Return look data */
	SGZ::SCALER value = manEntities->getLooking(lua_tostring(Lua, -1)).x;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getLookY ( lua_State *Lua )
{
	/** Return look data */
	SGZ::SCALER value = manEntities->getLooking(lua_tostring(Lua, -1)).y;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getLookZ ( lua_State *Lua )
{
	/** Return look data */
	SGZ::SCALER value = manEntities->getLooking(lua_tostring(Lua, -1)).z;

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::scale ( lua_State *Lua )
{
	/** Scale overall */
	manEntities->scale( lua_tostring(Lua, -2), (SGZ::SCALER)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::scaleXYZ ( lua_State *Lua )
{
	/** Scale in a specified axis */
	SGZ::VECTOR3 value;
	value.x = (SGZ::SCALER)lua_tonumber(Lua, -3);
	value.y = (SGZ::SCALER)lua_tonumber(Lua, -2);
	value.z = (SGZ::SCALER)lua_tonumber(Lua, -1);
	manEntities->scaleXYZ( lua_tostring(Lua, -4), value);

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);


	return 0;
}

int SGZEntityMan_Proxy::rotate ( lua_State *Lua )
{
	/** Rotate in a specified axis */
	SGZ::VECTOR3 value;
	value.x = (SGZ::SCALER)lua_tonumber(Lua, -3);
	value.y = (SGZ::SCALER)lua_tonumber(Lua, -2);
	value.z = (SGZ::SCALER)lua_tonumber(Lua, -1);
	manEntities->rotate( lua_tostring(Lua, -4), value);

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);


	return 0;
}

int SGZEntityMan_Proxy::setMaxAccel(lua_State *Lua )
{
	/** Set Max Accel */
	manEntities->setMaxAccel ( lua_tostring(Lua, -2), (SGZ::SCALER)lua_tonumber(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::setSpeed(lua_State *Lua )
{
	/** Set Max Accel */
	manEntities->setSpeed ( lua_tostring(Lua, -2), (SGZ::SCALER)lua_tonumber(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::setMaxSpeed(lua_State *Lua )
{
	/** Set Max Accel */
	manEntities->setMaxSpeed ( lua_tostring(Lua, -2), (SGZ::SCALER)lua_tonumber(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::getSpeed(lua_State *Lua )
{
	/** Return Current Speed */
	SGZ::SCALER value = manEntities->getSpeed(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::getAccel(lua_State *Lua )
{
	/** Return Current Accel */
	SGZ::SCALER value = manEntities->getAccel(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::setAccel(lua_State *Lua )
{
	/** Set Accel */
	manEntities->setAccel ( lua_tostring(Lua, -2), (SGZ::SCALER)lua_tonumber(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::stop ( lua_State *Lua )
{
	/** Stop moving/rotating/scaling immediately */
	manEntities->stop(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::setCollisionGeom ( lua_State *Lua )
{
	/** Set the collision type */
	manEntities->setCollisionGeom( lua_tostring(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::getAnimation( lua_State *Lua )
{
	/** Get Current Animation Name */
	std::string AnimName = manEntities->getAnimation(lua_tostring(Lua,-1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, AnimName.c_str());
	return 1;
}

int SGZEntityMan_Proxy::setAnimation( lua_State *Lua )
{
	/** Set the current Animation */
	manEntities->setAnimation( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::createAnimation( lua_State *Lua )
{
	/** Create a new Animation Group */
	manEntities->createAnimation( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::deleteAnimation( lua_State *Lua )
{
	/** Delete an Animation Group */
	manEntities->deleteAnimation( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::loadTexture ( lua_State *Lua )
{
	/** Load an Animation Frame */
	if(luaL_checkstring(Lua, -10)==NULL)
	{
		SGZ::Logger.log( SGZLOG::Warning, "SCRIPT ERROR! Call to SGZEntityMan:LoadFrame FAILED!\n");
		return 0;
	}
	SGZ::RGBCOLOUR col;
	col.r = (SGZ::COLOURVAL)lua_tonumber(Lua, -3);
	col.g = (SGZ::COLOURVAL)lua_tonumber(Lua, -2);
	col.b = (SGZ::COLOURVAL)lua_tonumber(Lua, -1);
	manEntities->loadFrame( lua_tostring(Lua, -10), lua_tostring(Lua, -9), lua_tostring(Lua, -8), lua_tostring(Lua, -7), (int)lua_tonumber(Lua, -6), (int)lua_tonumber(Lua, -5), (int)lua_tonumber(Lua, -4), col );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::setColour ( lua_State *Lua )
{
	SGZ::RGBCOLOUR col;
	col.r = (SGZ::COLOURVAL)lua_tonumber(Lua, -3);
	col.g = (SGZ::COLOURVAL)lua_tonumber(Lua, -2);
	col.b = (SGZ::COLOURVAL)lua_tonumber(Lua, -1);
	manEntities->setColour( lua_tostring(Lua, -4), col );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::changeColour(lua_State *Lua)
{
	SGZ::RGBCOLOUR oldColour, newColour;
	newColour.b = (SGZ::COLOURVAL)lua_tonumber(Lua, -1);
	newColour.g = (SGZ::COLOURVAL)lua_tonumber(Lua, -2);
	newColour.r = (SGZ::COLOURVAL)lua_tonumber(Lua, -3);
	oldColour.b = (SGZ::COLOURVAL)lua_tonumber(Lua, -4);
	oldColour.g = (SGZ::COLOURVAL)lua_tonumber(Lua, -5);
	oldColour.r = (SGZ::COLOURVAL)lua_tonumber(Lua, -6);
	
	manEntities->changeColour( lua_tostring(Lua, -7), oldColour, newColour);
	
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::newVar ( lua_State *Lua )
{
	manEntities->newVar( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::deleteVar ( lua_State *Lua )
{
	manEntities->deleteVar( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::changeVar ( lua_State *Lua )
{
	manEntities->changeVar( lua_tostring(Lua, -3), lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::checkVar ( lua_State *Lua )
{
	std::string value = manEntities->checkVar( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, value.c_str());

	return 1;
}

int SGZEntityMan_Proxy::checkExist(lua_State *Lua)
{
	bool value = manEntities->checkExist( lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::countEntities(lua_State *Lua)
{
	int value = manEntities->getEntityCount( );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);
	return 1;
}

int SGZEntityMan_Proxy::setMaxEntities(lua_State *Lua)
{
	manEntities->setMaxEntities( (int)lua_tonumber(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZEntityMan_Proxy::getMaxEntities(lua_State *Lua)
{
	int value = manEntities->getCurrentMaxEntities( );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);

	return 1;
}

int SGZEntityMan_Proxy::setDimensions(lua_State *Lua)
{
	SGZ::VECTOR3 value;
	value.x = (SGZ::SCALER)lua_tonumber(Lua, -3);
	value.y = (SGZ::SCALER)lua_tonumber(Lua, -2);
	value.z = (SGZ::SCALER)lua_tonumber(Lua, -1);
	manEntities->setDimensions( lua_tostring(Lua, -4) , value );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

const char SGZEntityMan_Proxy::className[] = "SGZEntityManager";
Lunar<SGZEntityMan_Proxy>::RegType SGZEntityMan_Proxy::methods[] =
{
	#ifdef SGZ2D
	{"add2DEntity",		 &SGZEntityMan_Proxy::add2DEntity},
	#endif
	#if defined (SGZ3D) && defined(somethingelse)
	{"add3DEntity",		 &SGZEntityMan_Proxy::add3DEntity},
	#endif
	{"setColour",		   &SGZEntityMan_Proxy::setColour},
	{"changeColour",		&SGZEntityMan_Proxy::changeColour},
	{"delEntity",		   &SGZEntityMan_Proxy::delEntity},
	{"update",			  &SGZEntityMan_Proxy::update},
	{"moveTo",			  &SGZEntityMan_Proxy::moveTo},
	{"lookTo",			  &SGZEntityMan_Proxy::lookTo},
	{"moveDelta",		   &SGZEntityMan_Proxy::moveDelta},
	{"getLookX",			&SGZEntityMan_Proxy::getLookX},
	{"getLookY",			&SGZEntityMan_Proxy::getLookY},
	{"getLookZ",			&SGZEntityMan_Proxy::getLookZ},
	{"getX",				&SGZEntityMan_Proxy::getX},
	{"getY",				&SGZEntityMan_Proxy::getY},
	{"getZ",				&SGZEntityMan_Proxy::getZ},
	{"getWidth",			&SGZEntityMan_Proxy::getWidth},
	{"getHeight",		   &SGZEntityMan_Proxy::getHeight},
	{"getDepth",			&SGZEntityMan_Proxy::getDepth},
	{"scale",			   &SGZEntityMan_Proxy::scale},
	{"scaleXYZ",			&SGZEntityMan_Proxy::scaleXYZ},
	{"rotate",			  &SGZEntityMan_Proxy::rotate},
	{"setMaxAccel",		 &SGZEntityMan_Proxy::setMaxAccel},
	{"setAccel",			&SGZEntityMan_Proxy::setAccel},
	{"setMaxSpeed",		 &SGZEntityMan_Proxy::setMaxSpeed},
	{"setSpeed",			&SGZEntityMan_Proxy::setSpeed},
	{"getSpeed",			&SGZEntityMan_Proxy::getSpeed},
	{"getAccel",			&SGZEntityMan_Proxy::getAccel},
	{"stop",				&SGZEntityMan_Proxy::stop},
	{"setCollisionGeom",	&SGZEntityMan_Proxy::setCollisionGeom},
	{"getAnimation",		&SGZEntityMan_Proxy::getAnimation},
	{"setAnimation",		&SGZEntityMan_Proxy::setAnimation},
	{"createAnimation",	 &SGZEntityMan_Proxy::createAnimation},
	{"deleteAnimation",	 &SGZEntityMan_Proxy::deleteAnimation},
	{"loadFrame",		   &SGZEntityMan_Proxy::loadTexture},
	{"newVar",			  &SGZEntityMan_Proxy::newVar},
	{"checkVar",			&SGZEntityMan_Proxy::checkVar},
	{"deleteVar",		   &SGZEntityMan_Proxy::deleteVar},
	{"changeVar",		   &SGZEntityMan_Proxy::changeVar},
	{"checkExist",		  &SGZEntityMan_Proxy::checkExist},
	{"countEntities",	   &SGZEntityMan_Proxy::countEntities},
	{"getMaxEntities",	  &SGZEntityMan_Proxy::getMaxEntities},
	{"setMaxEntities",	  &SGZEntityMan_Proxy::setMaxEntities},
	{"setDimensions",	   &SGZEntityMan_Proxy::setDimensions},
	{0,0}
};
