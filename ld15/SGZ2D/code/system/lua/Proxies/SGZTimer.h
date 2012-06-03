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

/**
	\file SGZTimer.h
	\brief The Timer Proxy

*/


#ifndef _SGZTIMER_H_
#define _SGZTIMER_H_

#ifdef pedanticGCC
extern "C" {
#endif
	#include "lualib.h"
#ifdef pedanticGCC
}
#endif

#include "../lunar.h"
#include "../../../common/data/CTimer.h"

class SGZTimer_Proxy
{
	public:
		static const char className[];
		static Lunar<SGZTimer_Proxy>::RegType methods[];

		int Start(lua_State *L);
		int Stop(lua_State *L);
		int Reset(lua_State *L);
		int Running(lua_State *L);
		int Time(lua_State *L);

		SGZTimer_Proxy(lua_State *L)
		: mTimer()
		{
			for (int cnt=1; cnt<=lua_gettop(L); cnt++)
				lua_pop(L, cnt);
		}
		~SGZTimer_Proxy() {}

	private:

	SGZ::Timer mTimer;

};

#endif

