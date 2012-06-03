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

#ifndef _SGZLEVELMAN_PROXY_H_
#define _SGZLEVELMAN_PROXY_H_

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

class SGZLevelMan_Proxy
{
	public:
		static const char className[];
		static Lunar<SGZLevelMan_Proxy>::RegType methods[];

		int	 SetSize( lua_State *Lua );
		int	 AddTile( lua_State *Lua );
		int	 TexTile( lua_State *Lua );
		int	 DelTile( lua_State *Lua );

		int	 NewVar (lua_State *Lua);
		int	 CheckVar (lua_State *Lua);
		int	 DeleteVar (lua_State *Lua);
		int	 ChangeVar (lua_State *Lua);

		int	 CheckExist( lua_State *Lua );
		int	 Clear( lua_State *Lua );
		int	 Render( lua_State *Lua );
		int	 GetType(lua_State *Lua);

		SGZLevelMan_Proxy(lua_State *L)
		{
			for (int cnt=1; cnt<=lua_gettop(L); cnt++)
				lua_pop(L, cnt);
		}
		~SGZLevelMan_Proxy() {};

};

#endif




