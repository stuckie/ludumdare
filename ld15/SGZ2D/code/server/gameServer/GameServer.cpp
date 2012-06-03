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
	\file GameServer.cpp
	\brief Game Server Code
*/

#include "GameServer.h"
#include "../../common/debug/CDebug.h"
#include "../managers/entityManager/MEntity.h"
#include "../managers/textureManager/MTexture.h"
#include "../managers/levelManager/MLevel.h"
#include <ctime>

bool GameServer::createInterface( void )
{
	/* Set up Managers and Clear them */

	/* Create a new Entity Manager */
	mEntityManager = new MEntity;

	/* Create a new Texture Manager */
	mTextureManager = new MTexture;

	/* Create a new Level Manager */
	mLevelManager = new MLevel;

	/* Start The Timer */
	mLastTime = clock() / 1000.0f;

	return true;
}

bool GameServer::destroyInterface( void )
{
	/* Clear Managers and Delete them */

	if(mEntityManager)
		delete mEntityManager;
	if(mTextureManager)
		delete mTextureManager;
	if(mLevelManager)
		delete mLevelManager;

	return true;
}

bool GameServer::updateServer( void )
{
	float currentTime = clock() / 1000.0f;
	mDeltaTime = currentTime - mLastTime;

	mEntityManager->updateEntities(mDeltaTime);

	mLastTime = currentTime;

	return true;
}
