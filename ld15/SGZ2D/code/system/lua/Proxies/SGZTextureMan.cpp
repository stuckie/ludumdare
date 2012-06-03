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

#include "SGZTextureMan.h"
#include "../../../typedefs.h"
#include "../../../server/OServer.h"
#include "../../../server/gameServer/GameServer.h"
#include "../../../server/managers/textureManager/MTexture.h"

using namespace SGZ;

int SGZTextureMan_Proxy::addTexture( lua_State *Lua )
{
	manTextures->addTexture( lua_tostring(Lua, 1), lua_tostring(Lua, 2) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZTextureMan_Proxy::addTexMask( lua_State *Lua )
{
	manTextures->addTexMask( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZTextureMan_Proxy::delTexture( lua_State *Lua )
{
	manTextures->delTexture( lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZTextureMan_Proxy::setColour( lua_State *Lua )
{
	SGZ::RGBCOLOUR col;
	col.r = (SGZ::COLOURVAL)lua_tonumber(Lua, -3);
	col.g = (SGZ::COLOURVAL)lua_tonumber(Lua, -2);
	col.b = (SGZ::COLOURVAL)lua_tonumber(Lua, -1);
	manTextures->setColour ( lua_tostring(Lua, -4), col );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZTextureMan_Proxy::checkExist( lua_State *Lua )
{
	bool value = manTextures->checkExist(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, value);

	return 1;
}

int SGZTextureMan_Proxy::blitTexture( lua_State *Lua )
{
	int values = lua_gettop(Lua);
	if (values>8)
	{
		 manTextures->blitTexture(lua_tostring(Lua, 1),
		 (float)lua_tonumber(Lua, 2), (float)lua_tonumber(Lua, 3), (float)lua_tonumber(Lua, 4), (float)lua_tonumber(Lua, 5),
		 (float)lua_tonumber(Lua, 6), (float)lua_tonumber(Lua, 7), (float)lua_tonumber(Lua, 8), (float)lua_tonumber(Lua, 9),
		 (float)lua_tonumber(Lua,10), (float)lua_tonumber(Lua,11), (float)lua_tonumber(Lua,12), (float)lua_tonumber(Lua,13),
		 (float)lua_tonumber(Lua,14), (float)lua_tonumber(Lua,15), (float)lua_tonumber(Lua,16), (float)lua_tonumber(Lua,17),
		 (int)lua_tonumber(Lua,18));

	}
	else
	{

		SGZ::VECTOR3 position;
		position.x = (SGZ::SCALER)lua_tonumber(Lua, 2);
		position.y = (SGZ::SCALER)lua_tonumber(Lua, 3);
		position.z = (SGZ::SCALER)lua_tonumber(Lua, 4);
		manTextures->blitTexture(lua_tostring(Lua, 1), position,
			(SGZ::SCALER)lua_tonumber(Lua, 5), (SGZ::SCALER)lua_tonumber(Lua, 6), (SGZ::SCALER)lua_tonumber(Lua, 7), (SGZ::SCALER)lua_tonumber(Lua, 8));

	}

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

const char SGZTextureMan_Proxy::className[] = "SGZTextureManager";
Lunar<SGZTextureMan_Proxy>::RegType SGZTextureMan_Proxy::methods[] =
{
	{"addTexture",		  &SGZTextureMan_Proxy::addTexture},
	{"addTexMask",		  &SGZTextureMan_Proxy::addTexMask},
	{"delTexture",		  &SGZTextureMan_Proxy::delTexture},
	{"setColour",		   &SGZTextureMan_Proxy::setColour},
	{"checkExist",		  &SGZTextureMan_Proxy::checkExist},
	{"blitTexture",		 &SGZTextureMan_Proxy::blitTexture},
	{0,0}
};
