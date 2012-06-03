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

#include "SGZControl.h"

#include "../../../common/engine/CInterpret.h"
#include "../../../client/OClient.h"
#include "../../../client/input/OControl.h"

int SGZControl_Proxy::updateControls(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessController()->updateControls();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZControl_Proxy::getKey(lua_State *Lua)
{
	std::string key = lua_tostring(Lua, -1);

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->keyPress(key));
	return 1;
}

int SGZControl_Proxy::getJoysticks( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZControl_Proxy::getJoystickButton( lua_State *Lua)
{
	bool value = SGZ::Interpret.accessClient()->accessController()->getPadButton((int)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2));
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, value);

	return 1;
}

int SGZControl_Proxy::getJoystickAxis( lua_State *Lua)
{
	int value = SGZ::Interpret.accessClient()->accessController()->getPadAxis((int)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2));
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);

	return 1;
}

int SGZControl_Proxy::getJoystickHat( lua_State *Lua)
{
	int value = SGZ::Interpret.accessClient()->accessController()->getPadHat((int)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2));
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, value);

	return 1;
}

int SGZControl_Proxy::getJoystickDetails( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZControl_Proxy::getLEFT( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getLeft());
	return 1;
}

int SGZControl_Proxy::getRIGHT( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getRight());
	return 1;
}

int SGZControl_Proxy::getUP( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getUp());
	return 1;
}

int SGZControl_Proxy::getDOWN( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getDown());
	return 1;
}

int SGZControl_Proxy::getFire1( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getFire1());
	return 1;
}

int SGZControl_Proxy::getFire2( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getFire2());
	return 1;
}

int SGZControl_Proxy::getFire3( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getFire3());
	return 1;
}

int SGZControl_Proxy::getFire4( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getFire4());
	return 1;
}

int SGZControl_Proxy::getSTART( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getSTART());
	return 1;
}

int SGZControl_Proxy::getSELECT( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getSELECT());
	return 1;
}

int SGZControl_Proxy::getL1( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getL1());
	return 1;
}

int SGZControl_Proxy::getR1( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getR1());
	return 1;
}

#ifdef PLAT_PC

int SGZControl_Proxy::get1( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get1());
	return 1;
}

int SGZControl_Proxy::get2( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get2());
	return 1;
}

int SGZControl_Proxy::get3( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get3());
	return 1;
}

int SGZControl_Proxy::get4( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get4());
	return 1;
}

int SGZControl_Proxy::get5( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get5());
	return 1;
}

int SGZControl_Proxy::get6( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get6());
	return 1;
}

int SGZControl_Proxy::get7( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get7());
	return 1;
}

int SGZControl_Proxy::get8( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get8());
	return 1;
}

int SGZControl_Proxy::get9( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get9());
	return 1;
}

int SGZControl_Proxy::get0( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->get0());
	return 1;
}

int SGZControl_Proxy::getQ( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getQ());
	return 1;
}

int SGZControl_Proxy::getW( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getW());
	return 1;
}

int SGZControl_Proxy::getE( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getE());
	return 1;
}

int SGZControl_Proxy::getR( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getR());
	return 1;
}

int SGZControl_Proxy::getT( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getT());
	return 1;
}

int SGZControl_Proxy::getY( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getY());
	return 1;
}

int SGZControl_Proxy::getU( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getU());
	return 1;
}

int SGZControl_Proxy::getI( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getI());
	return 1;
}

int SGZControl_Proxy::getO( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getO());
	return 1;
}

int SGZControl_Proxy::getP( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getP());
	return 1;
}

int SGZControl_Proxy::getA( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getA());
	return 1;
}

int SGZControl_Proxy::getS( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getS());
	return 1;
}

int SGZControl_Proxy::getD( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getD());
	return 1;
}

int SGZControl_Proxy::getF( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF());
	return 1;
}

int SGZControl_Proxy::getG( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getG());
	return 1;
}

int SGZControl_Proxy::getH( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getH());
	return 1;
}

int SGZControl_Proxy::getJ( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getJ());
	return 1;
}

int SGZControl_Proxy::getK( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getK());
	return 1;
}

int SGZControl_Proxy::getL( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getL());
	return 1;
}

int SGZControl_Proxy::getZ( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getZ());
	return 1;
}

int SGZControl_Proxy::getX( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getX());
	return 1;
}

int SGZControl_Proxy::getC( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getC());
	return 1;
}

int SGZControl_Proxy::getV( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getV());
	return 1;
}

int SGZControl_Proxy::getB( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getB());
	return 1;
}

int SGZControl_Proxy::getN( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getN());
	return 1;
}

int SGZControl_Proxy::getM( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getM());
	return 1;
}

int SGZControl_Proxy::getLShift( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getLShift());
	return 1;
}

int SGZControl_Proxy::getLAlt( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getLAlt());
	return 1;
}

int SGZControl_Proxy::getLCtrl( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getLCtrl());
	return 1;
}

int SGZControl_Proxy::getSpace( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getSpace());
	return 1;
}

int SGZControl_Proxy::getReturn( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getReturn());
	return 1;
}

int SGZControl_Proxy::getRAlt( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getRAlt());
	return 1;
}

int SGZControl_Proxy::getRShift( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getRShift());
	return 1;
}

int SGZControl_Proxy::getRCtrl( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getRCtrl());
	return 1;
}

int SGZControl_Proxy::getF1( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF1());
	return 1;
}

int SGZControl_Proxy::getF2( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF2());
	return 1;
}

int SGZControl_Proxy::getF3( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF3());
	return 1;
}

int SGZControl_Proxy::getF4( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF4());
	return 1;
}

int SGZControl_Proxy::getF5( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF5());
	return 1;
}

int SGZControl_Proxy::getF6( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF6());
	return 1;
}

int SGZControl_Proxy::getF7( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF7());
	return 1;
}

int SGZControl_Proxy::getF8( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF8());
	return 1;
}

int SGZControl_Proxy::getF9( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF9());
	return 1;
}

int SGZControl_Proxy::getF10( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF10());
	return 1;
}

int SGZControl_Proxy::getF11( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF11());
	return 1;
}

int SGZControl_Proxy::getF12( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getF12());
	return 1;
}

int SGZControl_Proxy::getPlus( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getPlus());
	return 1;
}

int SGZControl_Proxy::getMinus( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getMinus());
	return 1;
}

int SGZControl_Proxy::getESC( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getESC());
	return 1;
}

int SGZControl_Proxy::getBackspace( lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessController()->getBackspace());
	return 1;
}

#endif


const char SGZControl_Proxy::className[] = "SGZControlManager";
Lunar<SGZControl_Proxy>::RegType SGZControl_Proxy::methods[] =
{
	{"updateControls",  &SGZControl_Proxy::updateControls},
	{"getKey", &SGZControl_Proxy::getKey},
	{"getPads", &SGZControl_Proxy::getJoysticks},
	{"getPadButton", &SGZControl_Proxy::getJoystickButton},
	{"getPadAxis", &SGZControl_Proxy::getJoystickAxis},
	{"getPadDetails", &SGZControl_Proxy::getJoystickDetails},
	{"getPadHat", &SGZControl_Proxy::getJoystickHat},
	{"getLeft", &SGZControl_Proxy::getLEFT},
	{"getRight", &SGZControl_Proxy::getRIGHT},
	{"getUp", &SGZControl_Proxy::getUP},
	{"getDown", &SGZControl_Proxy::getDOWN},
	{"getSTART", &SGZControl_Proxy::getSTART},
	{"getSELECT", &SGZControl_Proxy::getSELECT},
	{"getFire1", &SGZControl_Proxy::getFire1},
	{"getFire2", &SGZControl_Proxy::getFire2},
	{"getFire3", &SGZControl_Proxy::getFire3},
	{"getFire4", &SGZControl_Proxy::getFire4},
	#ifdef PLAT_PC
	{"get1", &SGZControl_Proxy::get1},
	{"get2", &SGZControl_Proxy::get2},
	{"get3", &SGZControl_Proxy::get3},
	{"get4", &SGZControl_Proxy::get4},
	{"get5", &SGZControl_Proxy::get5},
	{"get6", &SGZControl_Proxy::get6},
	{"get7", &SGZControl_Proxy::get7},
	{"get8", &SGZControl_Proxy::get8},
	{"get9", &SGZControl_Proxy::get9},
	{"get0", &SGZControl_Proxy::get0},
	{"getQ", &SGZControl_Proxy::getQ},
	{"getW", &SGZControl_Proxy::getW},
	{"getE", &SGZControl_Proxy::getE},
	{"getR", &SGZControl_Proxy::getR},
	{"getT", &SGZControl_Proxy::getT},
	{"getY", &SGZControl_Proxy::getY},
	{"getU", &SGZControl_Proxy::getU},
	{"getI", &SGZControl_Proxy::getI},
	{"getO", &SGZControl_Proxy::getO},
	{"getP", &SGZControl_Proxy::getP},
	{"getA", &SGZControl_Proxy::getA},
	{"getS", &SGZControl_Proxy::getS},
	{"getD", &SGZControl_Proxy::getD},
	{"getF", &SGZControl_Proxy::getF},
	{"getG", &SGZControl_Proxy::getG},
	{"getH", &SGZControl_Proxy::getH},
	{"getJ", &SGZControl_Proxy::getJ},
	{"getK", &SGZControl_Proxy::getK},
	{"getL", &SGZControl_Proxy::getL},
	{"getZ", &SGZControl_Proxy::getZ},
	{"getX", &SGZControl_Proxy::getX},
	{"getC", &SGZControl_Proxy::getC},
	{"getV", &SGZControl_Proxy::getV},
	{"getB", &SGZControl_Proxy::getB},
	{"getN", &SGZControl_Proxy::getN},
	{"getM", &SGZControl_Proxy::getM},
	{"getLShift", &SGZControl_Proxy::getLShift},
	{"getLCtrl", &SGZControl_Proxy::getLCtrl},
	{"getLAlt", &SGZControl_Proxy::getLAlt},
	{"getSpace", &SGZControl_Proxy::getSpace},
	{"getRAlt", &SGZControl_Proxy::getRAlt},
	{"getRCtrl", &SGZControl_Proxy::getRCtrl},
	{"getRShift", &SGZControl_Proxy::getRShift},
	{"getReturn", &SGZControl_Proxy::getReturn},
	{"getBackspace", &SGZControl_Proxy::getBackspace},
	{"getF1", &SGZControl_Proxy::getF1},
	{"getF2", &SGZControl_Proxy::getF2},
	{"getF3", &SGZControl_Proxy::getF3},
	{"getF4", &SGZControl_Proxy::getF4},
	{"getF5", &SGZControl_Proxy::getF5},
	{"getF6", &SGZControl_Proxy::getF6},
	{"getF7", &SGZControl_Proxy::getF7},
	{"getF8", &SGZControl_Proxy::getF8},
	{"getF9", &SGZControl_Proxy::getF9},
	{"getF10", &SGZControl_Proxy::getF10},
	{"getF11", &SGZControl_Proxy::getF11},
	{"getF12", &SGZControl_Proxy::getF12},
	{"getMinus", &SGZControl_Proxy::getMinus},
	{"getPlus", &SGZControl_Proxy::getPlus},
	#endif
	{0,0}
};
