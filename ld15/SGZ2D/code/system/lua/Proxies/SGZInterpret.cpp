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

#include "SGZInterpret.h"
#include "../../../typedefs.h"
#include "../../../server/OServer.h"
#include "../../../server/gameServer/GameServer.h"
#include <fstream>

int SGZInterpret_Proxy::Quit(lua_State *Lua)
{
	SGZ::Logger.log( SGZLOG::Debug, "Quit Received from Lua\n");
	SGZ::Interpret.quit();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZInterpret_Proxy::UpdateInterfaces(lua_State *Lua)
{
	SGZ::Interpret.updateInterfaces();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZInterpret_Proxy::Running(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.isRunning());

	return 1;
}

int SGZInterpret_Proxy::GetFps(lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, (int)SGZ::Interpret.accessServer()->World()->getFps());

	return 1;
}

int SGZInterpret_Proxy::RenderInfo(lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	#if (defined(REND_SDL))
	lua_pushstring(Lua, "REND_SDL");
	#endif
	#if (defined(REND_SDLGL))
	lua_pushstring(Lua, "REND_SDLGL");
	#endif
	#if (defined(REND_HORDE))
	std::string HordeDetails;
	HordeDetails.insert(0,"REND_");
	HordeDetails.insert(5,Horde3D::getVersionString());
	lua_pushstring(Lua, HordeDetails.c_str());
	#endif
	#if (defined(REND_SDLHORDE))
	std::string HordeDetails;
	HordeDetails.insert(0,"REND_SDL");
	HordeDetails.insert(8,Horde3D::getVersionString());
	lua_pushstring(Lua, HordeDetails.c_str());
	#endif
	#if (defined(REND_OGRE))
	lua_pushstring(Lua, "REND_OGRE");
	#endif
	#if (defined(REND_SDLDX))
	lua_pushstring(Lua, "REND_SDLDX");
	#endif
	#if (defined(REND_DIRECTX))
	lua_pushstring(Lua, "REND_DIRECTX");
	#endif
	#if (defined(REND_SPS2))
	lua_pushstring(Lua, "REND_SPS2");
	#endif
	#if (defined(REND_WINAPI))
	lua_pushstring(Lua, "REND_WINAPI");
	#endif

	return 1;
}

int SGZInterpret_Proxy::SystemInfo(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	#if (defined(PLAT_GP32))
	lua_pushstring(Lua, "PLAT_GP32");
	#endif
	#if (defined(PLAT_GP2X))
	lua_pushstring(Lua, "PLAT_GP2X");
	#endif
	#if (defined(PLAT_GBA))
	lua_pushstring(Lua, "PLAT_GBA");
	#endif
	#if (defined(PLAT_DS))
	lua_pushstring(Lua, "PLAT_DS");
	#endif
	#if (defined(PLAT_GC))
	lua_pushstring(Lua, "PLAT_GC");
	#endif
	#if (defined(PLAT_WII))
	lua_pushstring(Lua, "PLAT_WII");
	#endif
	#if (defined(PLAT_DC))
	lua_pushstring(Lua, "PLAT_DC");
	#endif
	#if (defined(PLAT_PSX))
	lua_pushstring(Lua, "PLAT_PSX");
	#endif
	#if (defined(PLAT_PS2LINUX))
	lua_pushstring(Lua, "PLAT_PS2LINUX");
	#endif
	#if (defined(PLAT_PS3LINUX))
	lua_pushstring(Lua, "PLAT_PS3LINUX");
	#endif
	#if (defined(PLAT_PS2DEV))
	lua_pushstring(Lua, "PLAT_PS2DEV");
	#endif
	#if (defined(PLAT_PS3DEV))
	lua_pushstring(Lua, "PLAT_PS3DEV");
	#endif
	#if (defined(PLAT_PSPDEV))
	lua_pushstring(Lua, "PLAT_PSPDEV");
	#endif
	#if (defined(PLAT_MACOSX))
	lua_pushstring(Lua, "PLAT_MACOSX");
	#endif
	#if (defined(PLAT_MACOSCLASSIC))
	lua_pushstring(Lua, "PLAT_MACOSCLASSIC");
	#endif
	#if (defined(PLAT_PC))
	lua_pushstring(Lua, "PLAT_PC");
	#endif

	return 1;
}

int SGZInterpret_Proxy::LogWarning ( lua_State *Lua )
{
	SGZ::Logger.log( SGZLOG::Warning, "LUA: " + std::string(lua_tostring(Lua, -1)));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZInterpret_Proxy::LogDebug ( lua_State *Lua )
{
	SGZ::Logger.log( SGZLOG::Debug, "LUA: " +  std::string(lua_tostring(Lua, -1)));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZInterpret_Proxy::LogError ( lua_State *Lua )
{
	SGZ::Logger.log( SGZLOG::Error, "LUA: " + std::string(lua_tostring(Lua, -1)));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZInterpret_Proxy::Debug ( lua_State *Lua )
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	#ifdef DEBUG_ON
		lua_pushboolean(Lua, true);
	#else
		lua_pushboolean(Lua, false);
	#endif

	return 1;
}

int SGZInterpret_Proxy::WriteIngameConfig ( lua_State *Lua )
{
	using namespace std;
	fstream file;

	file.open ("data/scripts/ingameConfig.lua", fstream::out);
	file << "musicVolume = " << (float)lua_tonumber(Lua, 1) << ";" << endl;
	file << "soundVolume = " << (float)lua_tonumber(Lua, 2) << ";" << endl;
	file << flush;
	file.close();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

const char SGZInterpret_Proxy::className[] = "SGZInterpreter";
Lunar<SGZInterpret_Proxy>::RegType SGZInterpret_Proxy::methods[] =
{
	{"isRunning", &SGZInterpret_Proxy::Running},
	{"quit", &SGZInterpret_Proxy::Quit},
	{"update", &SGZInterpret_Proxy::UpdateInterfaces},
	{"systemInfo", &SGZInterpret_Proxy::SystemInfo},
	{"renderInfo", &SGZInterpret_Proxy::RenderInfo},
	{"logWarning", &SGZInterpret_Proxy::LogWarning},
	{"logError", &SGZInterpret_Proxy::LogError},
	{"logDebug", &SGZInterpret_Proxy::LogDebug},
	{"isDebug", &SGZInterpret_Proxy::Debug},
	{"getFps", &SGZInterpret_Proxy::GetFps},
	{"writeIngameConfig", &SGZInterpret_Proxy::WriteIngameConfig},
	{0,0}
};
