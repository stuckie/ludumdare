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

#ifndef __SGZCONTROL_H_
#define __SGZCONTROL_H_

#ifdef pedanticGCC
extern "C"
{
#endif
	#include "lualib.h"
#ifdef pedanticGCC
}
#endif

#include "../lunar.h"

class SGZControl_Proxy
{
	public:
		static const char className[];
		static Lunar<SGZControl_Proxy>::RegType methods[];

		SGZControl_Proxy(lua_State *L)
		{
			for (int cnt=1; cnt<=lua_gettop(L); cnt++)
				lua_pop(L, cnt);
		}
		~SGZControl_Proxy() {}

		int updateControls(lua_State *Lua);
		int getKey(lua_State *Lua);
		int getJoysticks(lua_State *Lua);
		int getJoystickDetails(lua_State *Lua);
		int getJoystickAxis(lua_State *Lua);
		int getJoystickButton(lua_State *Lua);
		int getJoystickHat(lua_State *Lua);

		int getUP(lua_State *Lua);
		int getDOWN(lua_State *Lua);
		int getLEFT(lua_State *Lua);
		int getRIGHT(lua_State *Lua);
		int getFire1(lua_State *Lua);
		int getFire2(lua_State *Lua);
		int getFire3(lua_State *Lua);
		int getFire4(lua_State *Lua);
		int getL1(lua_State *Lua);
		int getR1(lua_State *Lua);
		int getSELECT(lua_State *Lua);
		int getSTART(lua_State *Lua);

		#ifdef PLAT_PC

		int get1( lua_State *Lua );
		int get2( lua_State *Lua );
		int get3( lua_State *Lua );
		int get4( lua_State *Lua );
		int get5( lua_State *Lua );
		int get6( lua_State *Lua );
		int get7( lua_State *Lua );
		int get8( lua_State *Lua );
		int get9( lua_State *Lua );
		int get0( lua_State *Lua );

		int getQ( lua_State *Lua );
		int getW( lua_State *Lua );
		int getE( lua_State *Lua );
		int getR( lua_State *Lua );
		int getT( lua_State *Lua );
		int getY( lua_State *Lua );
		int getU( lua_State *Lua );
		int getI( lua_State *Lua );
		int getO( lua_State *Lua );
		int getP( lua_State *Lua );
		int getA( lua_State *Lua );
		int getS( lua_State *Lua );
		int getD( lua_State *Lua );
		int getF( lua_State *Lua );
		int getG( lua_State *Lua );
		int getH( lua_State *Lua );
		int getJ( lua_State *Lua );
		int getK( lua_State *Lua );
		int getL( lua_State *Lua );
		int getZ( lua_State *Lua );
		int getX( lua_State *Lua );
		int getC( lua_State *Lua );
		int getV( lua_State *Lua );
		int getB( lua_State *Lua );
		int getN( lua_State *Lua );
		int getM( lua_State *Lua );

		int getLShift( lua_State *Lua );
		int getLCtrl( lua_State *Lua );
		int getLAlt( lua_State *Lua );
		int getRShift( lua_State *Lua );
		int getRCtrl( lua_State *Lua );
		int getRAlt( lua_State *Lua );
		int getSpace( lua_State *Lua );
		int getReturn( lua_State *Lua );
		int getBackspace( lua_State *Lua );
		int getPlus( lua_State *Lua );
		int getMinus( lua_State *Lua );

		int getF1( lua_State *Lua );
		int getF2( lua_State *Lua );
		int getF3( lua_State *Lua );
		int getF4( lua_State *Lua );
		int getF5( lua_State *Lua );
		int getF6( lua_State *Lua );
		int getF7( lua_State *Lua );
		int getF8( lua_State *Lua );
		int getF9( lua_State *Lua );
		int getF10( lua_State *Lua );
		int getF11( lua_State *Lua );
		int getF12( lua_State *Lua );

		int getESC( lua_State *Lua );

		#endif

		#ifdef PLAT_GP2X
			int getUPLEFT(lua_State *Lua);
			int getUPRIGHT(lua_State *Lua);
			int getDOWNLEFT(lua_State *Lua);
			int getDOWNRIGHT(lua_State *Lua);
			int getVOLUP(lua_State *Lua);
			int getVOLDOWN(lua_State *Lua);
			int getA(lua_State *Lua);
			int getB(lua_State *Lua);
			int getX(lua_State *Lua);
			int getY(lua_State *Lua);
			int getCLICK(lua_State *Lua);
		#endif

		#ifdef PLAT_PSPDEV
			int getTRI(lua_State *Lua);
			int getSQUARE(lua_State *Lua);
			int getCROSS(lua_State *Lua);
			int getCIRCLE(lua_State *Lua);
			int getVOLUP(lua_State *Lua);
			int getVOLDOWN(lua_State *Lua);
			int getHOME(lua_State *Lua);
			int getSTICK_X(lua_State *Lua);
			int getSTICK_Y(lua_State *Lua);
		#endif

		#if defined(PLAT_PS2LINUX) || defined (PLAT_PS2DEV) || defined(PLAT_PS3LINUX) || defined(PLAT_PS3DEV)
			int getL1(lua_State *Lua);
			int getR1(lua_State *Lua);
			int getL2(lua_State *Lua);
			int getR2(lua_State *Lua);
			int getL3(lua_State *Lua);
			int getR3(lua_State *Lua);
			int getTRI(lua_State *Lua);
			int getSQUARE(lua_State *Lua);
			int getCROSS(lua_State *Lua);
			int getCIRCLE(lua_State *Lua);
			int getLSTICK_X(lua_State *Lua);
			int getLSTICK_Y(lua_State *Lua);
			int getLSTICK_X(lua_State *Lua);
			int getLSTICK_Y(lua_State *Lua);
		#endif

		#ifdef PLAT_DS
			int getA(lua_State *Lua);
			int getB(lua_State *Lua);
			int getX(lua_State *Lua);
			int getY(lua_State *Lua);
		#endif

		#ifdef PLAT_GP32
			int getA(lua_State *Lua);
			int getB(lua_State *Lua);
		#endif

/*
		#ifdef PLAT_WII
			int getButton1(lua_State *Lua);
			int getButton2(lua_State *Lua);
			int getPLUS(lua_State *Lua);
			int getMINUS(lua_State *Lua);
			int getButtonA(lua_State *Lua);
			int getButtonB(lua_State *Lua);
			int getNUN_Z(lua_State *Lua);
			int getNUN_C(lua_State *Lua);
			int getNUN_X(lua_State *Lua);
			int getNUN_Y(lua_State *Lua);
		#endif
*/
	private:
};

#endif
