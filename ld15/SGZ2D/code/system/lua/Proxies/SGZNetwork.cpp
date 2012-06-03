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

#include "SGZNetwork.h"

int SGZNetwork_Proxy::OpenConnection(lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZNetwork_Proxy::CloseConnection(lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

const char SGZNetwork_Proxy::className[] = "SGZNetwork";
Lunar<SGZNetwork_Proxy>::RegType SGZNetwork_Proxy::methods[] =
{
	{"OpenConnection", &SGZNetwork_Proxy::OpenConnection},
	{"CloseConnection",  &SGZNetwork_Proxy::CloseConnection},
	{0,0}
};
