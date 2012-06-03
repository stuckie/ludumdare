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
	\file GameServer.h
	\brief Game Server Code
*/

#ifndef _GAMESERVER_H_
#define _GAMESERVER_H_

#include "../IServer.h"

class MEntity;
class MTexture;
class MLevel;

class GameServer : public SGZ::IServer
{

	private:
		MEntity* mEntityManager;
		MTexture* mTextureManager;
		MLevel* mLevelManager;
		float mLastTime;
		float mDeltaTime;

	public:
		GameServer()
		:   mEntityManager(0),
			mTextureManager(0),
			mLevelManager(0),
			mLastTime(0.0f),
			mDeltaTime(0.0f)
		{
			/*nope*/
		};

		GameServer( const GameServer& )
		:   mEntityManager(0),
			mTextureManager(0),
			mLevelManager(0),
			mLastTime(0.0f),
			mDeltaTime(0.0f)
		{
			/*nope*/
		};

		GameServer operator=( const GameServer& )
		{
			throw("nope");
		}

		~GameServer()
		{
			/* nope */
		};

		bool createInterface ( void );
		bool updateServer ( void );
		bool destroyInterface ( void );

		MEntity* accessEntityManager( void ) { return mEntityManager; };
		MTexture* accessTextureManager( void ) { return mTextureManager; };
		MLevel* accessLevelManager( void ) { return mLevelManager; };

		inline float getFps( void ) const
			{ return 1000.0f/mDeltaTime; }
};

#endif
