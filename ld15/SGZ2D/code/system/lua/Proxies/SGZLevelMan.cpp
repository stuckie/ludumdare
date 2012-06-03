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

#include "SGZLevelMan.h"
#include "../../../server/OServer.h"
#include "../../../server/gameServer/GameServer.h"
#include "../../../server/managers/levelManager/MLevel.h"

int SGZLevelMan_Proxy::SetSize( lua_State *Lua )
{
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->SetSize((int)lua_tonumber(Lua, -3),(int)lua_tonumber(Lua, -2),(int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::AddTile( lua_State *Lua )
{
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->AddTile( lua_tostring(Lua, -5), lua_tostring(Lua, -4), (int)lua_tonumber(Lua, -3), (int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::TexTile( lua_State *Lua )
{
	SGZ::RGBCOLOUR Colour;
	Colour.r = (SGZ::COLOURVAL)lua_tonumber(Lua,8);
	Colour.g = (SGZ::COLOURVAL)lua_tonumber(Lua,9);
	Colour.b = (SGZ::COLOURVAL)lua_tonumber(Lua,10);
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->TexTile( lua_tostring(Lua, 1), lua_tostring(Lua, 2), lua_tostring(Lua, 3),
																		(SGZ::SCALER)lua_tonumber(Lua, 4), (SGZ::SCALER)lua_tonumber(Lua, 5),
																		(SGZ::SCALER)lua_tonumber(Lua, 6), (SGZ::SCALER)lua_tonumber(Lua, 7),
																		Colour);

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::DelTile( lua_State *Lua )
{
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->DelTile( lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::NewVar (lua_State *Lua)
{
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->NewVar( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::CheckVar (lua_State *Lua)
{
	std::string value = SGZ::Interpret.accessServer()->World()->accessLevelManager()->CheckVar( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, value.c_str());
	return 1;

}

int SGZLevelMan_Proxy::DeleteVar (lua_State *Lua)
{
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->DeleteVar ( lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::ChangeVar (lua_State *Lua)
{
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->ChangeVar ( lua_tostring(Lua, -3), lua_tostring(Lua, -2), lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::CheckExist( lua_State *Lua )
{
	bool value = SGZ::Interpret.accessServer()->World()->accessLevelManager()->CheckExist ( lua_tostring(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, value);

	return 1;
}

int SGZLevelMan_Proxy::Clear (lua_State *Lua)
{
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->Clear();

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::Render (lua_State *Lua)
{
	SGZ::Interpret.accessServer()->World()->accessLevelManager()->RenderLevel((int)lua_tonumber(Lua, -7), 
	(int)lua_tonumber(Lua, -6), (int)lua_tonumber(Lua, -5), (int)lua_tonumber(Lua, -4), (int)lua_tonumber(Lua, -3),
	(SGZ::SCALER)lua_tonumber(Lua, -2), (SGZ::SCALER)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZLevelMan_Proxy::GetType (lua_State *Lua)
{
	std::string value = SGZ::Interpret.accessServer()->World()->accessLevelManager()->GetType((int)lua_tonumber(Lua, -3), (int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); ++cnt)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, value.c_str());
	return 1;
}

const char SGZLevelMan_Proxy::className[] = "SGZLevelManager";
Lunar<SGZLevelMan_Proxy>::RegType SGZLevelMan_Proxy::methods[] =
{
	{"newVar",		&SGZLevelMan_Proxy::NewVar},
	{"checkVar",		&SGZLevelMan_Proxy::CheckVar},
	{"deleteVar",		&SGZLevelMan_Proxy::DeleteVar},
	{"changeVar",		&SGZLevelMan_Proxy::ChangeVar},
	{"checkExist",		&SGZLevelMan_Proxy::CheckExist},
	{"setSize",		&SGZLevelMan_Proxy::SetSize},
	{"addTile",		&SGZLevelMan_Proxy::AddTile},
	{"texTile",		&SGZLevelMan_Proxy::TexTile},
	{"delTile",		&SGZLevelMan_Proxy::DelTile},
	{"clear",		&SGZLevelMan_Proxy::Clear},
	{"render",		&SGZLevelMan_Proxy::Render},
	{"getTileType",		&SGZLevelMan_Proxy::GetType},
	{0,0}
};


