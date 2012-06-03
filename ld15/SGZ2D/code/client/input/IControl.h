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
	\file IControl.h
	\brief The Controller Interface
*/

#ifndef _ICONTROL_H_
#define _ICONTROL_H_

#include <string>

namespace SGZ
{
	class IControl
	{
		public:
			virtual ~IControl()
			{
				/* nope */
			}

			virtual bool createInterface(void) = 0;
			/* Create a client interface to talk on */

			virtual bool destroyInterface(void) = 0;
			/* Destroy a client interface */

			virtual bool updateControls(void) = 0;
			/* Update The Controls */

			virtual bool keyPress( const std::string &pKey ) = 0;
			/* Check for KeyPress */

			virtual bool getUp( void ) = 0;
			virtual bool getDown( void ) = 0;
			virtual bool getLeft( void ) = 0;
			virtual bool getRight( void ) = 0;
			virtual bool getFire1( void ) = 0;
			virtual bool getFire2( void ) = 0;
			virtual bool getFire3( void ) = 0;
			virtual bool getFire4( void ) = 0;
			virtual bool getL1( void ) = 0;
			virtual bool getR1( void ) = 0;
			virtual bool getSELECT( void ) = 0;
			virtual bool getSTART( void ) = 0;
			virtual int  getPadAxis( const int pPad, const int pAxis ) = 0;
			virtual bool getPadButton ( const int pPad, const int pButton ) = 0;
			virtual int  getPadHat ( const int pPad, const int pHat ) = 0;

			virtual bool get1( void ) = 0;
			virtual bool get2( void ) = 0;
			virtual bool get3( void ) = 0;
			virtual bool get4( void ) = 0;
			virtual bool get5( void ) = 0;
			virtual bool get6( void ) = 0;
			virtual bool get7( void ) = 0;
			virtual bool get8( void ) = 0;
			virtual bool get9( void ) = 0;
			virtual bool get0( void ) = 0;

			virtual bool getQ( void ) = 0;
			virtual bool getW( void ) = 0;
			virtual bool getE( void ) = 0;
			virtual bool getR( void ) = 0;
			virtual bool getT( void ) = 0;
			virtual bool getY( void ) = 0;
			virtual bool getU( void ) = 0;
			virtual bool getI( void ) = 0;
			virtual bool getO( void ) = 0;
			virtual bool getP( void ) = 0;
			virtual bool getA( void ) = 0;
			virtual bool getS( void ) = 0;
			virtual bool getD( void ) = 0;
			virtual bool getF( void ) = 0;
			virtual bool getG( void ) = 0;
			virtual bool getH( void ) = 0;
			virtual bool getJ( void ) = 0;
			virtual bool getK( void ) = 0;
			virtual bool getL( void ) = 0;
			virtual bool getZ( void ) = 0;
			virtual bool getX( void ) = 0;
			virtual bool getC( void ) = 0;
			virtual bool getV( void ) = 0;
			virtual bool getB( void ) = 0;
			virtual bool getN( void ) = 0;
			virtual bool getM( void ) = 0;

			virtual bool getLShift( void ) = 0;
			virtual bool getLCtrl( void ) = 0;
			virtual bool getLAlt( void ) = 0;
			virtual bool getRShift( void ) = 0;
			virtual bool getRCtrl( void ) = 0;
			virtual bool getRAlt( void ) = 0;
			virtual bool getSpace( void ) = 0;
			virtual bool getReturn( void ) = 0;
			virtual bool getBackspace( void ) = 0;
			virtual bool getPlus( void ) = 0;
			virtual bool getMinus( void ) = 0;

			virtual bool getF1( void ) = 0;
			virtual bool getF2( void ) = 0;
			virtual bool getF3( void ) = 0;
			virtual bool getF4( void ) = 0;
			virtual bool getF5( void ) = 0;
			virtual bool getF6( void ) = 0;
			virtual bool getF7( void ) = 0;
			virtual bool getF8( void ) = 0;
			virtual bool getF9( void ) = 0;
			virtual bool getF10( void ) = 0;
			virtual bool getF11( void ) = 0;
			virtual bool getF12( void ) = 0;

			virtual bool getESC( void ) = 0;

	}; // End of IControl

} // End of Namespace

#endif
