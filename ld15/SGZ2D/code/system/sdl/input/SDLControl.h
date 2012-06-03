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
	\file SDLControl.h
	\brief The SDL Controller Interface
*/

#ifndef _SDLCONTROL_H_
#define _SDLCONTROL_H_

#include "../../../client/input/IControl.h"
#include <SDL/SDL.h>

class SDLControl : public SGZ::IControl
{
	public:
	SDLControl()
	:   mEvent(),
		mButtons(SDL_GetKeyState(0)),
		mLastKey(),
		#ifndef PLAT_A320
			mJoypad1(NULL),
			mJoypad2(NULL),
		#endif
		mMouseX(0), mMouseY(0)
	{
		/* nope */
	}

	SDLControl operator=(const SDLControl&)
	{
		throw("nope");
	}

	SDLControl (const SDLControl&)
	:   mEvent(),
		mButtons(SDL_GetKeyState(0)),
		mLastKey(),
		#ifndef PLAT_A320
			mJoypad1(NULL),
			mJoypad2(NULL),
		#endif
		mMouseX(0), mMouseY(0)
	{
	}

	~SDLControl()
	{
		/* nope */
	}

	/* Create a client interface to talk on */
	bool createInterface(void);

	/* Destroy a client interface */
	bool destroyInterface(void);

	/* Update The Controls */
	bool updateControls(void);

	/* Checks for a Key Press */
	inline bool keyPress( const std::string &pKey)
	{   return (mLastKey.compare(pKey)==0) ? true : false; }

	inline bool getPadButton ( const int pPad, const int pButton )
	{
		#ifndef PLAT_A320
			if (pPad == 1)
				return SDL_JoystickGetButton(mJoypad1, pButton);
			else if (pPad == 2)
				return SDL_JoystickGetButton(mJoypad2, pButton);
			else return false;
		#else
			return false;
		#endif
	}

	inline int getPadAxis ( const int pPad, const int pAxis )
	{
		#ifndef PLAT_A320
			if (pPad == 1)
				return SDL_JoystickGetAxis(mJoypad1, pAxis);
			else if (pPad == 2)
				return SDL_JoystickGetAxis(mJoypad2, pAxis);
			else return false;
		#else
			return false;
		#endif
	}

	inline int getPadHat ( const int pPad, const int pHat )
	{
		#ifndef PLAT_A320
			if (pPad == 1)
				return SDL_JoystickGetHat(mJoypad1, pHat);
			else if (pPad == 2)
				return SDL_JoystickGetHat(mJoypad2, pHat);
			else return false;
		#else
			return false;
		#endif
	}


	inline bool getLeft( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_LEFT();
		#elif PLAT_GP2X
			return GP2X_LEFT();
		#endif

		return (mButtons[SDLK_LEFT]==1) ? true : false;
	}

	inline bool getRight( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_RIGHT();
		#elif PLAT_GP2X
			return GP2X_RIGHT();
		#endif

		return (mButtons[SDLK_RIGHT]==1) ? true : false;
	}

	inline bool getUp( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_UP();
		#elif PLAT_GP2X
			return GP2X_UP();
		#endif

		return (mButtons[SDLK_UP]==1) ? true : false;
	}

	inline bool getDown( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_DOWN();
		#elif PLAT_GP2X
			return GP2X_DOWN();
		#endif

		return (mButtons[SDLK_DOWN]==1) ? true : false;
	}

	inline bool getFire1( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_TRIANGLE();
		#elif PLAT_GP2X
			return GP2X_Y();
		#endif

		return (mButtons[SDLK_w]==1) ? true : false;
	}

	inline bool getFire2( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_CIRCLE();
		#elif PLAT_GP2X
			return GP2X_B();
		#endif

		return (mButtons[SDLK_d]==1) ? true : false;
	}

	inline bool getFire3( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_CROSS();
		#elif PLAT_GP2X
			return GP2X_X();
		#endif

		return (mButtons[SDLK_s]==1) ? true : false;
	}

	inline bool getFire4( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_SQUARE();
		#elif PLAT_GP2X
			return GP2X_A();
		#endif

		return (mButtons[SDLK_a]==1) ? true : false;
	}

	inline bool getSTART( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_START();
		#elif PLAT_GP2X
			return GP2X_START();
		#endif

		return (mButtons[SDLK_RETURN]==1) ? true : false;
	}

	inline bool getSELECT( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_SELECT();
		#elif PLAT_GP2X
			return GP2X_SELECT();
		#endif

		return (mButtons[SDLK_SPACE]==1) ? true : false;
	}

	inline bool getL1( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_L();
		#elif PLAT_GP12X
			return GP2X_L();
		#endif

		return (mButtons[SDLK_q]==1) ? true : false;
	}

	inline bool getR1( void )
	{
		#ifdef PLAT_PSPDEV
			return PSP_R();
		#elif PLAT_GP2X
			return GP2X_R();
		#endif

		return (mButtons[SDLK_e]==1) ? true : false;
	}

	inline bool get1( void )
		{ return mButtons[SDLK_1]; }

	inline bool get2( void )
		{ return mButtons[SDLK_2]; }

	inline bool get3( void )
		{ return mButtons[SDLK_3]; }

	inline bool get4( void )
		{ return mButtons[SDLK_4]; }

	inline bool get5( void )
		{ return mButtons[SDLK_5]; }

	inline bool get6( void )
		{ return mButtons[SDLK_6]; }

	inline bool get7( void )
		{ return mButtons[SDLK_7]; }

	inline bool get8( void )
		{ return mButtons[SDLK_8]; }

	inline bool get9( void )
		{ return mButtons[SDLK_9]; }

	inline bool get0( void )
		{ return mButtons[SDLK_0]; }

	inline bool getQ( void )
		{ return mButtons[SDLK_q]; }

	inline bool getW( void )
		{ return mButtons[SDLK_w]; }

	inline bool getE( void )
		{ return mButtons[SDLK_e]; }

	inline bool getR( void )
		{ return mButtons[SDLK_r]; }

	inline bool getT( void )
		{ return mButtons[SDLK_t]; }

	inline bool getY( void )
		{ return mButtons[SDLK_y]; }

	inline bool getU( void )
		{ return mButtons[SDLK_u]; }

	inline bool getI( void )
		{ return mButtons[SDLK_i]; }

	inline bool getO( void )
		{ return mButtons[SDLK_o]; }

	inline bool getP( void )
		{ return mButtons[SDLK_p]; }

	inline bool getA( void )
		{ return mButtons[SDLK_a]; }

	inline bool getS( void )
		{ return mButtons[SDLK_s]; }

	inline bool getD( void )
		{ return mButtons[SDLK_d]; }

	inline bool getF( void )
		{ return mButtons[SDLK_f]; }

	inline bool getG( void )
		{ return mButtons[SDLK_g]; }

	inline bool getH( void )
		{ return mButtons[SDLK_h]; }

	inline bool getJ( void )
		{ return mButtons[SDLK_j]; }

	inline bool getK( void )
		{ return mButtons[SDLK_k]; }

	inline bool getL( void )
		{ return mButtons[SDLK_l]; }

	inline bool getZ( void )
		{ return mButtons[SDLK_z]; }

	inline bool getX( void )
		{ return mButtons[SDLK_x]; }

	inline bool getC( void )
		{ return mButtons[SDLK_c]; }

	inline bool getV( void )
		{ return mButtons[SDLK_v]; }

	inline bool getB( void )
		{ return mButtons[SDLK_b]; }

	inline bool getN( void )
		{ return mButtons[SDLK_n]; }

	inline bool getM( void )
		{ return mButtons[SDLK_m]; }

	inline bool getLShift( void )
		{ return mButtons[SDLK_LSHIFT]; }

	inline bool getLCtrl( void )
		{ return mButtons[SDLK_LCTRL]; }

	inline bool getLAlt( void )
		{ return mButtons[SDLK_LALT]; }

	inline bool getRShift( void )
		{ return mButtons[SDLK_RSHIFT]; }

	inline bool getRCtrl( void )
		{ return mButtons[SDLK_RCTRL]; }

	inline bool getRAlt( void )
		{ return mButtons[SDLK_RALT]; }

	inline bool getSpace( void )
		{ return mButtons[SDLK_SPACE]; }

	inline bool getReturn( void )
		{ return mButtons[SDLK_RETURN]; }

	inline bool getBackspace( void )
		{ return mButtons[SDLK_BACKSPACE]; }

	inline bool getPlus( void )
		{ return mButtons[SDLK_PLUS]; }

	inline bool getMinus( void )
		{ return mButtons[SDLK_MINUS]; }

	inline bool getF1( void )
		{ return mButtons[SDLK_F1]; }

	inline bool getF2( void )
		{ return mButtons[SDLK_F2]; }

	inline bool getF3( void )
		{ return mButtons[SDLK_F3]; }

	inline bool getF4( void )
		{ return mButtons[SDLK_F4]; }

	inline bool getF5( void )
		{ return mButtons[SDLK_F5]; }

	inline bool getF6( void )
		{ return mButtons[SDLK_F6]; }

	inline bool getF7( void )
		{ return mButtons[SDLK_F7]; }

	inline bool getF8( void )
		{ return mButtons[SDLK_F8]; }

	inline bool getF9( void )
		{ return mButtons[SDLK_F9]; }

	inline bool getF10( void )
		{ return mButtons[SDLK_F10]; }

	inline bool getF11( void )
		{ return mButtons[SDLK_F11]; }

	inline bool getF12( void )
		{ return mButtons[SDLK_F12]; }

	inline bool getESC( void )
		{ return mButtons[SDLK_ESCAPE]; }

#ifdef PLAT_GP2X				// GP2X Specific Defines
	#define GP2X_BUTTON_UP			  (0)
	#define GP2X_BUTTON_DOWN			(4)
	#define GP2X_BUTTON_LEFT			(2)
	#define GP2X_BUTTON_RIGHT		   (6)
	#define GP2X_BUTTON_UPLEFT		  (1)
	#define GP2X_BUTTON_UPRIGHT		 (7)
	#define GP2X_BUTTON_DOWNLEFT		(3)
	#define GP2X_BUTTON_DOWNRIGHT	   (5)
	#define GP2X_BUTTON_CLICK		   (18)
	#define GP2X_BUTTON_A			   (12)
	#define GP2X_BUTTON_B			   (13)
	#define GP2X_BUTTON_X			   (14)
	#define GP2X_BUTTON_Y			   (15)
	#define GP2X_BUTTON_L			   (10)
	#define GP2X_BUTTON_R			   (11)
	#define GP2X_BUTTON_START		   (8)
	#define GP2X_BUTTON_SELECT		  (9)
	#define GP2X_BUTTON_VOLUP		   (16)
	#define GP2X_BUTTON_VOLDOWN		 (17)

	inline bool GP2X_UP( void )
		{	return mButtons[GP2X_BUTTON_UP]; }
	inline bool GP2X_DOWN( void )
		{	return mButtons[GP2X_BUTTON_DOWN];}
	inline bool GP2X_LEFT( void )
		{	return mButtons[GP2X_BUTTON_LEFT];}
	inline bool GP2X_RIGHT( void )
		{	return mButtons[GP2X_BUTTON_RIGHT];}
	inline bool GP2X_UPLEFT( void )
		{	return mButtons[GP2X_BUTTON_UPLEFT];}
	inline bool GP2X_UPRIGHT( void )
		{	return mButtons[GP2X_BUTTON_UPRIGHT];}
	inline bool GP2X_DOWNLEFT( void )
		{	return mButtons[GP2X_BUTTON_DOWNLEFT];}
	inline bool GP2X_DOWNRIGHT( void )
		{	return mButtons[GP2X_BUTTON_DOWNRIGHT];}
	inline bool GP2X_BUTTONCLICK( void )
		{	return mButtons[GP2X_BUTTON_CLICK];}
	inline bool GP2X_A( void )
		{	return mButtons[GP2X_BUTTON_A];}
	inline bool GP2X_B( void )
		{	return mButtons[GP2X_BUTTON_B];}
	inline bool GP2X_X( void )
		{	return mButtons[GP2X_BUTTON_X];}
	inline bool GP2X_Y( void )
		{	return mButtons[GP2X_BUTTON_Y];}
	inline bool GP2X_L( void )
		{	return mButtons[GP2X_BUTTON_L];}
	inline bool GP2X_R( void )
		{	return mButtons[GP2X_BUTTON_R];}
	inline bool GP2X_START( void )
		{	return mButtons[GP2X_BUTTON_START];}
	inline bool GP2X_SELECT( void )
		{	return mButtons[GP2X_BUTTON_SELECT];}
	inline bool GP2X_VOLUP( void )
		{	return mButtons[GP2X_BUTTON_VOLUP];}
	inline bool GP2X_VOLDOWN( void )
		{	return mButtons[GP2X_BUTTON_VOLDOWN];}
#endif

#ifdef PLAT_PSPDEV					  // PSPDEV Specific Defines
/*
The PSP's controls provide a joystick with a two axes on the analog
stick and 14 independent buttons.  The button mapping is fixed:
*/
	#define PSP_BUTTON_TRIANGLE		(0)
	#define PSP_BUTTON_CIRCLE		  (1)
	#define PSP_BUTTON_CROSS		   (2)
	#define PSP_BUTTON_SQUARE		  (3)
	#define PSP_BUTTON_L			   (4)
	#define PSP_BUTTON_R			   (5)
	#define PSP_BUTTON_DOWN			(6)
	#define PSP_BUTTON_LEFT			(7)
	#define PSP_BUTTON_UP			  (8)
	#define PSP_BUTTON_RIGHT		   (9)
	#define PSP_BUTTON_SELECT		  (10)
	#define PSP_BUTTON_START		   (11)
	#define PSP_BUTTON_HOME			(12)
	#define PSP_BUTTON_HOLD			(13)

	inline bool PSP_TRIANGLE( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_TRIANGLE); }
	inline bool PSP_CIRCLE( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_CIRCLE); }
	inline bool PSP_CROSS( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_CROSS); }
	inline bool PSP_SQUARE( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_SQUARE); }
	inline bool PSP_UP( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_UP); }
	inline bool PSP_DOWN( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_DOWN); }
	inline bool PSP_LEFT( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_LEFT); }
	inline bool PSP_RIGHT( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_RIGHT); }
	inline bool PSP_L( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_L); }
	inline bool PSP_R( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_R); }
	inline bool PSP_START( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_START); }
	inline bool PSP_SELECT( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_SELECT); }
	inline bool PSP_HOME( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_HOME); }
	inline bool PSP_HOLD( void )
		{	return (bool)SDL_JoystickGetButton(mJoypad1, PSP_BUTTON_HOLD); }
#endif

	private:
		SDL_Event mEvent;						   // Our SDL Event
		Uint8 *mButtons;							// Our button pointer
		std::string mLastKey;					   // String to hold the last key pressed
		#ifndef PLAT_A320
			SDL_Joystick *mJoypad1, *mJoypad2;		  // A Joypad to play with!
		#endif

		int mMouseX, mMouseY;					   // Mouse X/Y

}; // End of SDLControl

#endif
