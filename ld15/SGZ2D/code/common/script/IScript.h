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
 \file IScript.h
 \brief The Script Interface

	Although I'm only really going to be supporting Lua, if I create a generic Interface from the outset,
	it means that I might be able to support other scripting languages later.

	Would be useful if I have time to do a look at differences between Lua and Python, for instance.
*/

#ifndef _ISCRIPT_H_
#define _ISCRIPT_H_

#include <string>

namespace SGZ
{
	class IScript
	{
		public:
			virtual ~IScript() {}

			virtual int createInterface() = 0;
			/** Create a script interface */

			virtual int destroyInterface() = 0;
			/** Destroy a script interface */

			virtual int updateScripts() = 0;
			/** Update the Script interface */

			virtual int loadExternalScript( const std::string &pScriptFile ) = 0;
			/** Let's us load an external script file */

			virtual int loadConfigScript() = 0;
			/** Let's load up our configuration script */

			virtual int saveConfigScript( const std::string &pConfig ) = 0;
			/** Save the configuration script */

			virtual int callFunction ( const std::string &pFunction ) = 0;
			virtual int callFunctionNoError ( const std::string &pFunction ) = 0;
			virtual int callFunction ( const std::string &pFunction, const char* pParamVars, ... ) = 0;
			/** Call a specific Function */

	};
}

#endif
