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
	\file CInterpret.cpp
	\brief The Interpreter Code

*/

#include "CInterpret.h"
#include "../debug/CDebug.h"
#include "../../client/OClient.h"
#include "../../server/OServer.h"
#include "../script/OScript.h"

using namespace SGZ;

bool CInterpret::setup( )
{
	Logger.log( SGZLOG::Warning, "SGZEngine Launched.\n");
	mRunStatus = true;
	Logger.log( SGZLOG::Debug,"Starting up SGZ::Interpretor!\n");

	mServerObject = new OServer;
	if(!mServerObject) {
		Logger.log( SGZLOG::Warning, "Error Creating our Server Interface\n");
		return false;
	}
	else {
		mServerObject->createInterface();
	}

	mClientObject = new OClient;
	if(!mClientObject) {
		Logger.log( SGZLOG::Warning, "Error Creating Our Client Interface\n");
		return false;
	}
	else {
		mClientObject->createInterface();
	}

	mScriptObject = new OScript;
	if(!mScriptObject) {
		Logger.log( SGZLOG::Warning, "Error Starting Scripting Interface\n");
		return false;
	}
	else {
		mScriptObject->createInterface();
	}

	if(!mScriptObject->loadConfigScript()) {
		firstRun();
		return false;
	}

	mLastTime = 0;

	Logger.log( SGZLOG::Debug,"SGZ::Interpretor Start Code Complete\n");

	return true;
}

bool CInterpret::run()
{
	if(!mScriptObject->updateScripts()) {
		Logger.log( SGZLOG::Warning, "Script Failed to Update! BAIL\n");
		quit();
		return false;
	}

	/* we do nothing more, script handles it all */
	return true;
}

bool CInterpret::shutdown()
{
	Logger.log( SGZLOG::Debug, "SGZ::Interpretor Stopping...\n");
	if(mClientObject) {
		Logger.log( SGZLOG::Debug, "Bringing down Client Object\n");
		mClientObject->destroyInterface();
		mClientObject=NULL;
	}

	if(mServerObject) {
		Logger.log( SGZLOG::Debug, "Bringing down Server Object\n");
		mServerObject->destroyInterface();
		mServerObject=NULL;
	}

	if(mScriptObject) {
		Logger.log( SGZLOG::Debug, "Bringing down Script Object\n");
		mScriptObject->destroyInterface();
		mScriptObject=NULL;
	}

	mRunStatus = false;
	Logger.log( SGZLOG::Debug, "SGZ::Interpretor Stopped Successfully\n");
	Logger.log( SGZLOG::Warning, "SGZEngine Closed.\n");

	return true;
}

void CInterpret::firstRun( void ) const
{
	Logger.log( SGZLOG::Warning, "Config was Mangled/Non-existant.\nGenerating Default Config.\n");
	mScriptObject->saveConfigScript("640:480:32:\"SGZEngine\":data/scripts/engine.sgz:main:");
	mScriptObject->loadConfigScript();
}


void CInterpret::updateInterfaces ( void )
{
// kill me for this...
    Uint32 curTime = SDL_GetTicks();

    while (curTime < mLastTime + (1000 / 60.0))
    {
        SDL_Delay(1);
        curTime = SDL_GetTicks();
    }

    mLastTime = curTime;

	if(mServerObject)
		mServerObject->updateServer();

	if(mClientObject)
		mClientObject->updateClient();
}

// We're a Singleton, so instance ourselves here, out the road...
CInterpret Interpretor;
