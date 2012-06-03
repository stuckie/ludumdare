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
	\file OScript.h
	\brief The Script Object

	The Script Object is for communicating and reading scripts.

	We're hardcoding to Lua for quickness just now
*/

#ifndef _OSCRIPT_H_
#define _OSCRIPT_H_

#include "../../arch.h"
#include "IScript.h"

#ifdef SCRIPT_LUA
	#include "../../system/lua/LuaScript.h"
#endif
#ifdef SCRIPT_PYTHON
	#include "../../system/python/PythonScript.h"
#endif
#ifdef SCRIPT_RUBY
	#include "../../system/ruby/RubyScript.h"
#endif

class OScript : public SGZ::IScript
{
	private:

		/** Depending on what scripting language we use depends on what we call here */
		#ifdef SCRIPT_LUA
			LuaScript mScript;
		#endif
		#ifdef SCRIPT_PYTHON
			PythonScript mScript;
		#endif
		#ifdef SCRIPT_RUBY
			RubyScript mScript;
		#endif

	public:
		OScript()
		: mScript()
		{
			/* nope */
		}

		~OScript()
		{
			/* nope */
		}

		int createInterface()
		{
			return mScript.createInterface();
		}
		/** Create a script interface */

		int destroyInterface()
		{
			return mScript.destroyInterface();
		}
		/** Destroy a script interface */

		int updateScripts()
		{
			return mScript.updateScripts();
		}
		/** Update the Scripts */

		int loadExternalScript( const std::string &pScriptFile )
		{
			return mScript.loadExternalScript( pScriptFile );
		}
		/** Let's us load an external script file */

		int loadConfigScript()
		{
			return mScript.loadConfigScript();
		}
		/** Let's load up our configuration script */

		int saveConfigScript( const std::string &pConfig )
		{
			return mScript.saveConfigScript( pConfig );
		}
		/** Save the configuration script */

		int callFunction ( const std::string &pFunction )
		{
			return mScript.callFunction( pFunction );
		}
		/** Call a Specific function */

		int callFunctionNoError ( const std::string &pFunction )
		{
			return mScript.callFunctionNoError( pFunction );
		}
		/** Call a Specific function and ignore errors */

		int callFunction ( const std::string &pFunction, const char* pParamVars, ... )
		{
			va_list vars;
			va_start( vars, pParamVars );
			int returnVal = mScript.callFunction( pFunction, pParamVars, vars );
			va_end ( vars );
			return returnVal;
		}
		/** Call a Specific function with variables */
};

#endif
