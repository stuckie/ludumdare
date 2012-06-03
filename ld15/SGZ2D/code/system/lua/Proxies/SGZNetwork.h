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

#ifndef _SGZNETWORK_PROXY_H_
#define _SGZNETWORK_PROXY_H_

#ifdef pedanticGCC
extern "C" {
#endif
	#include "lualib.h"
#ifdef pedanticGCC
}
#endif

#include "../lunar.h"
#include "../../../arch.h"
#include "../../../common/debug/CDebug.h"
#include "../../../common/engine/CInterpret.h"

class SGZNetwork_Proxy
{
	public:
		static const char className[];
		static Lunar<SGZNetwork_Proxy>::RegType methods[];

		int OpenConnection(lua_State *Lua);
		int CloseConnection(lua_State *Lua);

		SGZNetwork_Proxy(lua_State *L)
		{
			for (int cnt=1; cnt<=lua_gettop(L); cnt++)
				lua_pop(L, cnt);
		}
		~SGZNetwork_Proxy() {}


	private:
};

#endif
