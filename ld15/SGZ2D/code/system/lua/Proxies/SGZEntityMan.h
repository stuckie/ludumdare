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

#ifndef _SGZENTITYMAN_PROXY_H_
#define _SGZENTITYMAN_PROXY_H_

#ifdef pedanticGCC
extern "C" {
#endif
	#include "lualib.h"
#ifdef pedanticGCC
}
#endif

#include "../lunar.h"

class SGZEntityMan_Proxy
{
	public:
		static const char className[];
		static Lunar<SGZEntityMan_Proxy>::RegType methods[];

		int update(lua_State *Lua);
		/** Update our Entity */

		int moveTo (lua_State *Lua);
		/** Move to direct co-ordinates */

		int lookTo (lua_State *Lua);
		/** Direction to look at ( move towards ) */

		int moveDelta (lua_State *Lua);
		/** Move a certain amount in a certain axis */

		int getHeight(lua_State *Lua);
		int getWidth(lua_State *Lua);
		int getDepth(lua_State *Lua);
		int setDimensions(lua_State *Lua);
		/** Grab some entity info */

		int getX (lua_State *Lua);
		int getY (lua_State *Lua);
		int getZ (lua_State *Lua);
		/** Return position data */

		int getLookX (lua_State *Lua);
		int getLookY (lua_State *Lua);
		int getLookZ (lua_State *Lua);
		/** Get Where the entity is Looking */

		int scale (lua_State *Lua);
		int scaleXYZ (lua_State *Lua);
		/** Scale overall or in a specified axis */

		int rotate (lua_State *Lua);
		/** Rotate on a specific axis */

		int setMaxAccel (lua_State *Lua);
		int setSpeed (lua_State *Lua);
		int setMaxSpeed (lua_State *Lua);
		int getSpeed (lua_State *Lua);
		int getAccel (lua_State *Lua);
		int setAccel (lua_State *Lua);
		/** Accelerate a certain value "forward" */

		int stop (lua_State *Lua);
		/** Stop moving/rotating/scaling immediately */

		int setCollisionGeom (lua_State *Lua);
		/** Set the collision type */

		int getAnimation (lua_State *Lua);
		int setAnimation (lua_State *Lua);
		int createAnimation (lua_State *Lua);
		int deleteAnimation (lua_State *Lua);
		int loadTexture (lua_State *Lua);
		/** Load up a Texture into an Animation */

		int add2DEntity (lua_State *Lua);
		int add3DEntity (lua_State *Lua);
		int delEntity (lua_State *Lua);
		/** Add a new entity to the Manager */

		int setColour (lua_State *Lua);
		int changeColour (lua_State *Lua);
		int newVar (lua_State *Lua);
		int checkVar (lua_State *Lua);
		int deleteVar (lua_State *Lua);
		int changeVar (lua_State *Lua);
		int checkExist (lua_State *Lua);

		int setMaxEntities (lua_State *Lua);
		int getMaxEntities (lua_State *Lua);
		int countEntities (lua_State *Lua);

		SGZEntityMan_Proxy(lua_State *L)
		{
			for (int cnt=1; cnt<=lua_gettop(L); cnt++)
				lua_pop(L, cnt);
		}
		~SGZEntityMan_Proxy() {};

};

#endif

