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
	\file LuaScript.cpp
	\brief LuaScript Object

	The Lua Script Object is for communicating with the Scripting Language Lua
*/

#include "LuaScript.h"
#include "LuaProxies.h"
#include "lunar.h"
#include <cstring>
#include <ctime>

int LuaScript::createInterface()
{
	/** Create a script interface */
	mLua = lua_open();
	if ( mLua == NULL )
	{
		SGZ::Logger.log( SGZLOG::Warning, "Error Initializing lua\n" );
		return false;
	}
	else
		SGZ::Logger.log( SGZLOG::Debug, "Lua Initialised\n" );

	luaL_openlibs( mLua );
	Lunar<SGZRender_Proxy>::Register( mLua );
	Lunar<SGZControl_Proxy>::Register( mLua );
	Lunar<SGZInterpret_Proxy>::Register( mLua );
	Lunar<SGZAudio_Proxy>::Register( mLua );
	Lunar<SGZEntityMan_Proxy>::Register( mLua );
	Lunar<SGZTextureMan_Proxy>::Register( mLua );
	Lunar<SGZLevelMan_Proxy>::Register( mLua );
	Lunar<SGZTimer_Proxy>::Register( mLua );
	#if defined(REND_HORDE) || defined(REND_SDLHORDE)
	Lunar<SGZHorde_Proxy>::Register( mLua );
	#endif

	return true;
}

int LuaScript::destroyInterface()
{
	/** Destroy a script interface */
	lua_close( mLua );

	SGZ::Logger.log( SGZLOG::Debug, "Lua DeInitialised\n" );

	return true;
}

int LuaScript::loadExternalScript( const std::string &pScriptFile )
{
	/** Let's us load an external script file */
	if ( luaL_loadfile( mLua, pScriptFile.c_str() ) || lua_pcall( mLua, 0, 0, 0 ) )
	{
		SGZ::Logger.log( SGZLOG::Debug, "Cannot read file: " + std::string( lua_tostring( mLua, -1 ) ) );
		return false;
	}

	return true;
}

int LuaScript::loadConfigScript()
{
	// TODO: ReWrite the loadConfigScript function!
	/** Let's load up our configuration script */
	std::string WindowName = "",
				MainScript = "";
				//MainFunc;

	int WindowWidth = 0,
		WindowHeight = 0,
		WindowBPP = 0;

	if (luaL_loadfile(mLua, "data/scripts/config.sgz"))
	{
		SGZ::Logger.log( SGZLOG::Warning, "Cannot read configuration file: " + std::string(lua_tostring(mLua, -1)));
		return false;
	}

	if (lua_pcall(mLua, 0, 0, 0))
	{
		SGZ::Logger.log( SGZLOG::Warning, "Cannot parse configuration file: " + std::string(lua_tostring(mLua, -1)));
		return false;
	}

	lua_getglobal(mLua, "MainScript");
	lua_getglobal(mLua, "MainFunc");

	lua_getglobal(mLua, "WindowName");
	lua_getglobal(mLua, "WindowWidth");
	lua_getglobal(mLua, "WindowHeight");
	lua_getglobal(mLua, "WindowBPP");

	if (!lua_isstring(mLua, -6))
	{
		SGZ::Logger.log( SGZLOG::Warning, "'MainScript' in main.sgz should be a string\n");
		return false;
	}
	if (!lua_isstring(mLua, -5))
	{
		SGZ::Logger.log( SGZLOG::Warning, "'MainFunc' in main.sgz should be a string\n");
		return false;
	}
	if (!lua_isstring(mLua, -4))
		SGZ::Logger.log( SGZLOG::Warning, "'WindowName' in main.sgz should be a string\n");
	if (!lua_isnumber(mLua, -3))
		SGZ::Logger.log( SGZLOG::Warning, "'WindowWidth' in main.sgz should be a number\n");
	if (!lua_isnumber(mLua, -2))
		SGZ::Logger.log( SGZLOG::Warning, "'WindowHeight' in main.sgz should be a number\n");
	if (!lua_isnumber(mLua, -1))
		SGZ::Logger.log( SGZLOG::Warning, "'WindowBPP' in main.sgz should be a number\n");

	MainScript.insert(0, lua_tostring(mLua, -6));
	mMainFunc.insert(0, lua_tostring(mLua, -5));

	WindowName.insert(0, lua_tostring(mLua, -4));
	WindowWidth = (int)lua_tonumber(mLua, -3);
	WindowHeight = (int)lua_tonumber(mLua, -2);
	WindowBPP = (int)lua_tonumber(mLua, -1);

	SGZ::Logger.log( SGZLOG::Debug, "Game Function: " + mMainFunc + "in " + MainScript + "\n");

	loadExternalScript(MainScript);

	return true;
}

int LuaScript::saveConfigScript( const std::string &pConfig )
{
	// TODO: Rewrite saveConfigScript function! very nasty!
	/** Save the configuration script */
	FILE *configscript;
	const char delimiters[] = ":";
	char *token, *cp;

	configscript = fopen ("data/scripts/config.sgz","w");
	if (configscript==NULL)
	{
		SGZ::Logger.log( SGZLOG::Warning, "Can't create data/scripts/main.sgz config file!\n");
		return false;
	}

	fprintf(configscript,"-- This is the main SGZEngine script file \n-- We basically just set some things up and call our \"main function\" from here\n\n");

	cp = strdup (pConfig.c_str());				   /** store a writable copy of the C-String
														reason for this is that token has the habit
														of mangling the original stream.
														If we only feed it the copy of the string,
														we still retain the original incase we need it.

														WE don't, but it's good practice, and might need it later...
													*/

		/***************** Window Configuration ****************/
	fprintf(configscript,"--Window Creation\n");

	token = strtok (cp, delimiters);			  /** WindowWidth */
	if(token)
		fprintf(configscript,"WindowWidth = %s\n",token);
	else
	{
		SGZ::Logger.log( SGZLOG::Warning, "Problem creating the config script -- WindowWidth is mangled.\n");
		fclose(configscript);
		return false;
	}

	token = strtok (NULL, delimiters);				/** WindowHeight */
	if(token)
		fprintf(configscript,"WindowHeight = %s\n",token);
	else
	{
		SGZ::Logger.log( SGZLOG::Warning, "Problem creating the config script -- WindowHeight is mangled.\n");
		fclose(configscript);
		return false;
	}

	token = strtok (NULL, delimiters);			  /** WindowBPP */
	if(token)
		fprintf(configscript,"WindowBPP = %s\n",token);
	else
	{
		SGZ::Logger.log( SGZLOG::Warning, "Problem creating the config script -- WindowBPP is mangled.\n");
		fclose(configscript);
		return false;
	}

	token = strtok (NULL, delimiters);			  /** WindowName */
	if(token)
		fprintf(configscript,"WindowName = %s\n",token);
	else
	{
		SGZ::Logger.log( SGZLOG::Warning, "Problem creating the config script -- WindowName is mangled.\n");
		fclose(configscript);
		return false;
	}

		/***************** Script Configuration ****************/

	fprintf(configscript,"--Script Configuration\n");

	token = strtok (NULL, delimiters);			  /** MainScript */
	if(token)
		fprintf(configscript,"MainScript = \"%s\"\n",token);
	else
	{
		SGZ::Logger.log( SGZLOG::Warning, "Problem creating the config script -- MainScript is mangled.\n");
		return false;
	}

	token = strtok (NULL, delimiters);			  /** MainFunc */
	if(token)
		fprintf(configscript,"MainFunc = \"%s\"\n",token);
	else
	{
		SGZ::Logger.log( SGZLOG::Warning, "Problem creating the config script -- MainFunc is mangled.\n");
		return false;
	}

	time_t curtime;									 //!< To hold the Current Time
	struct tm *loctime;								 //!< Structure for the Local System Time

	curtime = time (NULL);							  //!< This grabs the current time
	loctime = localtime (&curtime);					 //!< Changes it to Local System Time

	fprintf (configscript, "--Last edited on %s ",	  //!< Prints the current time to the config script
				asctime(loctime));

	fclose(configscript);

	SGZ::Logger.log( SGZLOG::Warning, "Config file data/scripts/config.sgz was (re)created.\n");

	return true;
}

int LuaScript::updateScripts()
{
	lua_getglobal ( mLua, "main" );
	if( lua_pcall( mLua, 0, 0, 0 ) )
	{
		SGZ::Logger.log( SGZLOG::Warning, "LUA: " + std::string( lua_tostring( mLua, -1 ) ) + "\n" );
		return false;
	}
	return true;
}

int LuaScript::callFunction( const std::string &pFunction )
{
	lua_getglobal( mLua, pFunction.c_str() );
	if( lua_pcall( mLua, 0, 0, 0 ) )
	{
		SGZ::Logger.log( SGZLOG::Warning, "LUA: " + std::string( lua_tostring( mLua, -1 ) ) + "\n" );
		return false;
	}
	return true;
}

int LuaScript::callFunctionNoError( const std::string &pFunction )
{
	lua_getglobal( mLua, pFunction.c_str() );
	if( lua_pcall( mLua, 0, 0, 0 ) )
		return false;
	return true;
}

int LuaScript::callFunction( const std::string &pFunction, const char* pVarList, ... )
{
	va_list vars;
	int numArgs, numRes;

	va_start( vars, pVarList );
	lua_getglobal( mLua, pFunction.c_str() );

	for( numArgs = 0; *pVarList; numArgs++ )
	{
		luaL_checkstack( mLua, 1, "Too Many Arguments" );

		switch(*pVarList++)
		{
			case 'd':
				lua_pushnumber( mLua, va_arg( vars, double ) );
				break;

			case 'i':
				lua_pushinteger( mLua, va_arg( vars, int ) );
				break;

			case 's':
				lua_pushstring( mLua, va_arg( vars, char * ) );
				break;

			case '>':
				goto endargs;

			default:
			   SGZ::Logger.log( SGZLOG::Warning, "Invalid option passed into LuaScript::CallFunction\n" );
		}
	}
	endargs:

	numRes = strlen( pVarList );

	if ( lua_pcall( mLua, numArgs, numRes, 0 ) != 0 )
		SGZ::Logger.log( SGZLOG::Warning, "Error calling '" + pFunction + "': " + std::string( lua_tostring( mLua, -1 ) ) );

	numRes = -numRes;
	while (*pVarList)
	{
		switch (*pVarList++)
		{
			case 'd':
				if( !lua_isnumber( mLua, numRes ) )
					SGZ::Logger.log( SGZLOG::Warning, "Wrong Result Type" );

				*va_arg( vars, double * ) = lua_tonumber( mLua, numRes );
				break;

			case 'i':
				if( !lua_isnumber( mLua, numRes ) )
					SGZ::Logger.log( SGZLOG::Warning, "Wrong Result Type");

				*va_arg( vars, int * ) = (int)lua_tonumber( mLua, numRes );
				break;

			case 's':
				if( !lua_isstring( mLua, numRes ) )
					SGZ::Logger.log( SGZLOG::Warning, "Wrong Result Type" );

				*va_arg( vars, const char ** ) = lua_tostring( mLua, numRes );
				break;

			default:
				SGZ::Logger.log( SGZLOG::Warning, "Invalid option passed into LuaScript::CallFunction\n" );
		}

		numRes++;
	}

	va_end(vars);

	return true;
}
