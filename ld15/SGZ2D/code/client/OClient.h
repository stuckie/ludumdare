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
	\file OClient.h
	\brief The Client Object

	This is the Main Client Object
*/

#ifndef _OCLIENT_H_
#define _OCLIENT_H_

#include "IClient.h"
#include <string>

class OControl;
class OAudio;
class ORender;
class MGui;

class OClient : public SGZ::IClient
{
	private:

		OControl	*mControlObject;
		OAudio		*mAudioObject;
		ORender		*mRenderObject;
		MGui		*mGuiObject;

		/** Mouse Information */
		int mMouseX;
		int mMouseY;
		bool mMouseButtons[5];

		/** Key Information */
		unsigned char *mKeyboard;

		/** Joypad/stick Information */
		unsigned char *mJoyButtons;
		signed short mJoyStickX;
		signed short mJoyStickY;

	public:
		OClient()
		:	mControlObject(NULL),
			mAudioObject(NULL),
			mRenderObject(NULL),
			mGuiObject(NULL),
			mMouseX(0),mMouseY(0),
			mMouseButtons(),
			mKeyboard(NULL),
			mJoyButtons(NULL),
			mJoyStickX(0),mJoyStickY(0)
		{
			/* nope */
		}

		OClient( const OClient& )
		:	mControlObject(NULL),
			mAudioObject(NULL),
			mRenderObject(NULL),
			mGuiObject(NULL),
			mMouseX(0),mMouseY(0),
			mMouseButtons(),
			mKeyboard(NULL),
			mJoyButtons(NULL),
			mJoyStickX(0),mJoyStickY(0)
		{
		}

		OClient operator=( const OClient& )
		{
			return *this;
		}

		~OClient()
		{
			/* nope */
		}

		void createInterface();
		/* Create a Client interface */

		void destroyInterface();
		/* Destroy a Client interface */

		void updateClient();
		/* Update This Client */

		void createWindow(const std::string &pName, const int pWidth, const int pHeight, const int pBPP);
		/* Opens a Window */

		void closeWindow();
		/* Closes a Window */

		void setFullscreen(const bool pSet);
		/* Set Fullscreen */

		void updateMousePos(const int &pX, const int &pY);
		/* Update The Mouse Position */

		void updateMouseButtons(const bool pDown, const int pButton);
		/* Update The Mouse Buttons */

		void updateKeys(const unsigned char &pKey, const bool pDown);
		/* Update The Keyboard */

		void updateJoyButtons(const unsigned char &pButton, const bool pDown );
		/* Update the Joystick/Joypad Buttons */

		void updateJoyAxis(const signed short &pXAxis, const signed short &pYAxis );
		/* Update the Joystick X/Y Axis */

		ORender *accessRenderer()
			{   return mRenderObject;   }

		OControl *accessController()
			{   return mControlObject;   }

		OAudio *accessAudio()
			{   return mAudioObject; }

		MGui *accessGui()
			{ return mGuiObject; }

}; // End of OClient

#endif
