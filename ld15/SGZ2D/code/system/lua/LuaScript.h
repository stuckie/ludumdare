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
 \file LUAScript.h
 \brief The Lua Script Object


	The Lua Script Object is for communicating and reading scripts.
	Specifically dealing with Lua
*/

#ifndef _LUASCRIPT_H_
#define _LUASCRIPT_H_

#include "../../common/script/IScript.h"

#ifdef pedanticGCC
// sometimes, Lua is compiled inside the engine
// this define is for when GCC decides to make it C code rather than C++
extern "C"
{
#endif
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
#ifdef pedanticGCC
}
#endif

class LuaScript : public SGZ::IScript
{
	private:
		lua_State *mLua;
		std::string mMainFunc;

	public:

		LuaScript()
		:   mLua(0),
			mMainFunc()
		{
			/* nope */
		}

		LuaScript( const LuaScript& )
		:   mLua(0),
			mMainFunc()
		{
			throw( "There can be only one LuaScript!\n" );
		}

		LuaScript operator=( const LuaScript& )
		{
			throw( "There can be only one LuaScript!\n" );
		}

		~LuaScript()
		{
			/* nope */
		}

		int createInterface();
		/** Create a script interface */

		int destroyInterface();
		/** Destroy a script interface */

		int updateScripts();
		/** Update the Scripts */

		int loadExternalScript( const std::string &pScriptFile );
		/** Let's us load an external script file */

		int loadConfigScript();
		/** Let's load up our configuration script */

		int saveConfigScript( const std::string &pConfig );
		/** Save the configuration script */

		int callFunction ( const std::string &pFunction );
		int callFunctionNoError ( const std::string &pFunction );
		int callFunction ( const std::string &pFunction, const char* pParamVars, ... );
		/** Call Specific Function from File */

};

#endif
