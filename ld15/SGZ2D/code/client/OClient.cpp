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
	\file OClient.cpp
	\brief The Client Object

	The Event Interface is literally used as a generic struct for all events.
*/

#include "OClient.h"

#include "../common/debug/CDebug.h"
#include "renderer/ORender.h"
#include "audio/OAudio.h"
#include "input/OControl.h"
#include "gui/MGui.h"

using namespace SGZ;

void OClient::createInterface()
{
	/* Create a client interface */
	Logger.log( SGZLOG::Debug, "Creating Client Interface...\n");

	mRenderObject = new ORender;
	if(mRenderObject)
		mRenderObject->createRenderer();

	Logger.log( SGZLOG::Debug, "Renderer Running...\n");

	mControlObject = new OControl;
	if(mControlObject)
		mControlObject->createInterface();

	Logger.log( SGZLOG::Debug, "Controller Running...\n");

	mAudioObject = new OAudio;
	if(mAudioObject)
		mAudioObject->createInterface();

	Logger.log( SGZLOG::Debug, "Audio Running...\n");

	Logger.log( SGZLOG::Debug, "Client Object Created\n");
}

void OClient::destroyInterface()
{
	/* Destroy a script interface */

	if(mAudioObject) {
		mAudioObject->destroyInterface();
		mAudioObject=NULL;
	}

	if(mControlObject) {
		mControlObject->destroyInterface();
		mControlObject=NULL;
	}

	if(mRenderObject) {
		mRenderObject->stopRenderer();
		mRenderObject=NULL;
	}

	Logger.log( SGZLOG::Debug, "Client Object Destroyed\n");
}

void OClient::createWindow(const std::string &pName, const int pWidth, const int pHeight, const int pBPP)
{
	/** Open a Window up */
	if(mRenderObject)
		mRenderObject->createWindow( pName, pWidth, pHeight, pBPP );
}

void OClient::closeWindow()
{
	if(mRenderObject)
		mRenderObject->closeWindow();
}

void OClient::setFullscreen( const bool pSet )
{
	/** Set Fullscreen */
	if(mRenderObject)
		mRenderObject->setFullscreen(pSet);
}

void OClient::updateMousePos( const int &pX, const int &pY )
{
	/** Update Mouse Co-Ords */
	mMouseX = pX;
	mMouseY = pY;

}

void OClient::updateMouseButtons( const bool pDown, const int pButton )
{
	/** Update Mouse Buttons */
	mMouseButtons[pButton]=pDown;
}

void OClient::updateKeys( const unsigned char &pKey, const bool pDown )
{
	mKeyboard[pKey]=pDown;
}

void OClient::updateJoyButtons( const unsigned char &pButton, const bool pDown )
{
	mJoyButtons[pButton]=pDown;
}

void OClient::updateJoyAxis( const signed short &pXAxis, const signed short &pYAxis )
{
	mJoyStickX = pXAxis;
	mJoyStickY = pYAxis;
}

void OClient::updateClient()
{
	if(mRenderObject)
		mRenderObject->updateScreen();

	if(mControlObject)
		mControlObject->updateControls();

	if(mAudioObject)
		mAudioObject->updateAudio();

}
