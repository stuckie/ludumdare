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
	\file OControl.h
	\brief The Controller Object
*/

#ifndef _OCONTROL_H_
#define _OCONTROL_H_

#include "IControl.h"

/* API dependant thingies from hell! */
#ifdef IN_SDL
	#include "../../system/sdl/input/SDLControl.h"
#endif
#ifdef IN_OIS
	#include "../../system/ois/OISControl.h"
#endif
#ifdef IN_WINAPI
	#include "../../system/winapi/input/WINControl.h"
#endif
#ifdef IN_DIRECTX
	#include "../../system/directx/input/DXControl.h"
#endif

/** Now onto the consoles... */
#ifdef PLAT_PS2LINUX
	#include "../../system/ps2linux/input/PS2LControl.h"
#endif

class OControl : public SGZ::IControl
{
	private:
	/* API dependant thingies from hell! */
	#ifdef IN_SDL
		SDLControl  mControlObject;
	#endif
	#ifdef IN_OIS
		OISControl  mControlObject;
	#endif
	#ifdef IN_WINAPI
		WINControl  mControlObject;
	#endif
	#ifdef IN_DIRECTX
		DXControl   mControlObject;
	#endif

	/* Now onto the consoles... */
	#ifdef PLAT_PS2LINUX
		PS2LControl mControlObject;
	#endif

	#ifdef IN_PSPDEV
		PSPDEVControl mControlObject;
	#endif

	#ifdef IN_WII
		WIIControl mControlObject;
	#endif

	public:
		OControl()
		: mControlObject()
		{
			/*nope*/
		}

		~OControl()
		{
			/*nope*/
		}

		bool createInterface()
			{ return mControlObject.createInterface(); }

		bool destroyInterface()
			{ return mControlObject.destroyInterface(); }

		bool updateControls()
			{ return mControlObject.updateControls(); }

		bool keyPress( const std::string &pKey)
			{ return mControlObject.keyPress( pKey ); }

		bool getUp(  )
			{ return mControlObject.getUp(); }

		bool getDown(  )
			{ return mControlObject.getDown(); }

		bool getLeft(  )
			{ return mControlObject.getLeft(); }

		bool getRight(  )
			{ return mControlObject.getRight(); }

		bool getFire1(  )
			{ return mControlObject.getFire1(); }

		bool getFire2(  )
			{ return mControlObject.getFire2(); }

		bool getFire3(  )
			{ return mControlObject.getFire3(); }

		bool getFire4(  )
			{ return mControlObject.getFire4(); }

		bool getL1(  )
			{ return mControlObject.getL1(); }

		bool getR1(  )
			{ return mControlObject.getR1(); }

		bool getSELECT(  )
			{ return mControlObject.getSELECT(); }

		bool getSTART(  )
			{ return mControlObject.getSTART(); }

		int  getPadAxis( const int pPad, const int pAxis )
			{ return mControlObject.getPadAxis( pPad, pAxis ); }

		bool getPadButton ( const int pPad, const int pButton )
			{ return mControlObject.getPadButton( pPad, pButton ); }

		int  getPadHat ( const int pPad, const int pHat )
			{ return mControlObject.getPadHat( pPad, pHat ); }

		bool get1(  )
			{ return mControlObject.get1(); }

		bool get2(  )
			{ return mControlObject.get2(); }

		bool get3(  )
			{ return mControlObject.get3(); }

		bool get4(  )
			{ return mControlObject.get4(); }

		bool get5(  )
			{ return mControlObject.get5(); }

		bool get6(  )
			{ return mControlObject.get6(); }

		bool get7(  )
			{ return mControlObject.get7(); }

		bool get8(  )
			{ return mControlObject.get8(); }

		bool get9(  )
			{ return mControlObject.get9(); }

		bool get0(  )
			{ return mControlObject.get0(); }

		bool getQ(  )
			{ return mControlObject.getQ(); }

		bool getW(  )
			{ return mControlObject.getW(); }

		bool getE(  )
			{ return mControlObject.getE(); }

		bool getR(  )
			{ return mControlObject.getR(); }

		bool getT(  )
			{ return mControlObject.getT(); }

		bool getY(  )
			{ return mControlObject.getY(); }

		bool getU(  )
			{ return mControlObject.getU(); }

		bool getI(  )
			{ return mControlObject.getI(); }

		bool getO(  )
			{ return mControlObject.getO(); }

		bool getP(  )
			{ return mControlObject.getP(); }

		bool getA(  )
			{ return mControlObject.getA(); }

		bool getS(  )
			{ return mControlObject.getS(); }

		bool getD(  )
			{ return mControlObject.getD(); }

		bool getF(  )
			{ return mControlObject.getF(); }

		bool getG(  )
			{ return mControlObject.getG(); }

		bool getH(  )
			{ return mControlObject.getH(); }

		bool getJ(  )
			{ return mControlObject.getJ(); }

		bool getK(  )
			{ return mControlObject.getK(); }

		bool getL(  )
			{ return mControlObject.getL(); }

		bool getZ(  )
			{ return mControlObject.getZ(); }

		bool getX(  )
			{ return mControlObject.getX(); }

		bool getC(  )
			{ return mControlObject.getC(); }

		bool getV(  )
			{ return mControlObject.getV(); }

		bool getB(  )
			{ return mControlObject.getB(); }

		bool getN(  )
			{ return mControlObject.getN(); }

		bool getM(  )
			{ return mControlObject.getM(); }

		bool getLShift(  )
			{ return mControlObject.getLShift(); }

		bool getLCtrl(  )
			{ return mControlObject.getLCtrl(); }

		bool getLAlt(  )
			{ return mControlObject.getLAlt(); }

		bool getRShift(  )
			{ return mControlObject.getRShift(); }

		bool getRCtrl(  )
			{ return mControlObject.getRCtrl(); }

		bool getRAlt(  )
			{ return mControlObject.getRAlt(); }

		bool getSpace(  )
			{ return mControlObject.getSpace(); }

		bool getReturn(  )
			{ return mControlObject.getReturn(); }

		bool getBackspace(  )
			{ return mControlObject.getBackspace(); }

		bool getPlus(  )
			{ return mControlObject.getPlus(); }

		bool getMinus(  )
			{ return mControlObject.getMinus(); }

		bool getF1(  )
			{ return mControlObject.getF1(); }

		bool getF2(  )
			{ return mControlObject.getF2(); }

		bool getF3(  )
			{ return mControlObject.getF3(); }

		bool getF4(  )
			{ return mControlObject.getF4(); }

		bool getF5(  )
			{ return mControlObject.getF5(); }

		bool getF6(  )
			{ return mControlObject.getF6(); }

		bool getF7(  )
			{ return mControlObject.getF7(); }

		bool getF8(  )
			{ return mControlObject.getF8(); }

		bool getF9(  )
			{ return mControlObject.getF9(); }

		bool getF10(  )
			{ return mControlObject.getF10(); }

		bool getF11(  )
			{ return mControlObject.getF11(); }

		bool getF12(  )
			{ return mControlObject.getF12(); }

		bool getESC(  )
			{ return mControlObject.getESC(); }

}; // End of OControl

#endif
