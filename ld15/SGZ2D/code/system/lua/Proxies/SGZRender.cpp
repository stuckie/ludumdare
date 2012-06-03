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
	\file SGZRender.cpp
	\brief Render Proxy Methods for Lua
*/

#include "SGZRender.h"

#include "../../../common/engine/CInterpret.h"
#include "../../../client/OClient.h"
#include "../../../client/renderer/ORender.h"

int SGZRender_Proxy::createWindow(lua_State* Lua)
{
	const std::string WindowName = lua_tostring(Lua, -4);
	const int WindowWidth = (int)lua_tonumber(Lua, -3);
	const int WindowHeight = (int)lua_tonumber(Lua, -2);
	const int WindowBPP = (int)lua_tonumber(Lua, -1);

	SGZ::Interpret.accessClient()->createWindow(WindowName, WindowWidth, WindowHeight, WindowBPP);

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZRender_Proxy::closeWindow(lua_State* Lua)
{
	SGZ::Interpret.accessClient()->closeWindow();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZRender_Proxy::startRenderer(lua_State* Lua)
{
	SGZ::Interpret.accessClient()->accessRenderer()->startRenderer();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZRender_Proxy::stopRenderer(lua_State* Lua)
{
	SGZ::Interpret.accessClient()->accessRenderer()->stopRenderer();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZRender_Proxy::updateScreen(lua_State* Lua)
{
	SGZ::Interpret.accessClient()->accessRenderer()->updateScreen();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZRender_Proxy::setFullscreen ( lua_State *Lua )
{
	SGZ::Interpret.accessClient()->accessRenderer()->setFullscreen( lua_toboolean(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

const char SGZRender_Proxy::className[] = "SGZRenderer";
Lunar<SGZRender_Proxy>::RegType SGZRender_Proxy::methods[] =
{
	{"createWindow",  &SGZRender_Proxy::createWindow},
	{"closeWindow",  &SGZRender_Proxy::closeWindow},
	{"updateScreen",  &SGZRender_Proxy::updateScreen},
	{"setFullscreen", &SGZRender_Proxy::setFullscreen},
	{"startRenderer", &SGZRender_Proxy::startRenderer},
	{"stopRenderer", &SGZRender_Proxy::stopRenderer},
	{0,0}
};
