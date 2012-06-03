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
	\file SDLAudio.h
	\brief The SDL Audio Object

*/

#ifndef _SDLAUDIO_H_
#define _SDLAUDIO_H_

#include "../../../arch.h"
#include "../../../client/audio/IAudio.h"
#include "../../../common/data/CSLinkedlist.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

class SDLMusic
{
	public:
		SDLMusic()
		:	Name(),
			Data()
		{
		}

		SDLMusic( const SDLMusic& )
		:	Name(),
			Data()
		{
		}

		SDLMusic operator=( const SDLMusic& )
		{
			return *this;
		}

		~SDLMusic()
		{
		}

		std::string Name;
		Mix_Music *Data;
};

class SDLSound
{
	public:
		SDLSound()
		:	Name(),
			Data()
		{
		}

		SDLSound( const SDLSound& )
		:	Name(),
			Data()
		{
		}

		SDLSound operator=( const SDLSound& )
		{
			return *this;
		}

		~SDLSound()
		{
		}

		std::string Name;
		Mix_Chunk *Data;
};

class SDLChanGroup
{
	public:
		SDLChanGroup()
		:	Name(),
			groupNum()
		{
		}

		~SDLChanGroup()
		{
		}

		std::string Name;
		int groupNum;
};

class SDLAudio : public SGZ::IAudio
{

	private:

		SLinkedList<SDLMusic*> MusicList;
		SListIterator<SDLMusic*> MusicListITR;

		SLinkedList<SDLSound*> SFXList;
		SListIterator<SDLSound*> SFXListITR;

		SLinkedList<SDLChanGroup*> GroupList;
		SListIterator<SDLChanGroup*> GroupListITR;


	public:
		SDLAudio()
		:   MusicList(),
			MusicListITR(),
			SFXList(),
			SFXListITR(),
			GroupList(),
			GroupListITR()
		{
			/* nope */
		}

		~SDLAudio()
		{
			/* nope */
		}

		bool createInterface();
		/** Create a client interface to talk on */

		bool destroyInterface();
		/** Destroy a client interface */

		bool updateAudio();
		/** Update/Poll Audio where applicable */

		bool createGROUP( const int num, const std::string &name );
		bool reserveCHANS( const int num );
		bool groupCHAN( const int chan, const std::string &name );
		bool groupCHANS( const int from, const int to, const std::string &name );
		int countGROUP( const std::string &name );
		int CHANinGROUP( const std::string &name );
		int oldestGROUP( const std::string &name );
		int newestGROUP( const std::string &name );
		bool fadeGROUP( const std::string &name, const int time );
		bool haltGROUP( const std::string &name );
		bool removeGROUP( const std::string &name );

		bool loadSFXFile( const std::string &Filename, const std::string &SFXName );
		bool loadMUSFile( const std::string &Filename, const std::string &MUSName );
		/** Load a file to play */

		bool removeSFX( const std::string &SFXName );
		bool removeMUS( const std::string &MUSName );
		/** Remove a file from the list */

		int playSFX( const std::string &SFXName, const int loops = 0, const int channels = -1 );
		bool playMUS( const std::string &MUSName, const int loops = 0 );
		/** Play file */

		int fadeInSFX( const std::string &SFXName, const int time, const int loops = 0, const int channel = -1 );
		bool fadeInMUS( const std::string &MUSName, const int time, const int loops = 0 );
		/** Fade in loaded file */

		bool fadeOutCHAN( const int channel, const int time );
		bool fadeOutMUS( const int time );
		/** Fade Out loaded file */

		bool stopMUS();
		bool stopCHAN( const int channel );
		/** Stop Playing */

		bool pauseMUS();
		bool pauseCHAN( const int channel );
		/** Pause the file */

		bool resumeMUS();
		bool resumeCHAN( const int channel );
		/** Resume the stream */

		bool rewindMUS();
		bool setMUSPOS( const double position );
		/** Rewind/Fast Forward Music */

		bool setVolumeMUS( const int volume );
		bool setVolumeSFX( const std::string &SFXName, const int volume );
		/** Adjust Volumes */

		int isCHANPlaying( const int channel );
		bool isMUSPlaying();
		/** What's playing */

		bool setChannels( const int channels );
		/** Set Audio Channels */

		bool setPanning( const int channel, const int left, const int right );
		bool setDistance( const int channel, const int distance );
		bool setPosition( const int channel, const int angle, const int distance );
		bool setReverseStereo( const int channel, const bool flip );
		/** Some Effects */

}; // End of SDLAudio

#endif
