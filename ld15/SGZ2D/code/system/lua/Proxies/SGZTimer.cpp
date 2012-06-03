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

#include "SGZTimer.h"

int SGZTimer_Proxy::Start(lua_State *Lua)
{
	mTimer.start();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZTimer_Proxy::Stop(lua_State *Lua)
{
	mTimer.stop();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZTimer_Proxy::Reset(lua_State *Lua)
{
	mTimer.reset();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZTimer_Proxy::Running(lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, !mTimer.stopped());

	return 1;
}

int SGZTimer_Proxy::Time(lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, mTimer.currenttime());

	return 1;
}

const char SGZTimer_Proxy::className[] = "SGZTimer";
Lunar<SGZTimer_Proxy>::RegType SGZTimer_Proxy::methods[] =
{
	{"Start", &SGZTimer_Proxy::Start},
	{"Stop", &SGZTimer_Proxy::Stop},
	{"Reset", &SGZTimer_Proxy::Reset},
	{"Running", &SGZTimer_Proxy::Running},
	{"Time", &SGZTimer_Proxy::Time},
	{0,0}
};


