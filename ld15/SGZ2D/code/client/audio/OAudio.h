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
	\file OAudio.h
	\brief The Audio Object

*/

#ifndef _OAUDIO_H_
#define _OAUDIO_H_

#include "IAudio.h"

#ifdef SND_SDL
#include "../../system/sdl/audio/SDLAudio.h"
#endif

#ifdef SND_DIRECTX
#include "../../system/directx/audio/DXAudio.h"
#endif

#ifdef SND_OPENAL
#include "../../system/openal/OALAudio.h"
#endif

#ifdef PLAT_PS2LINUX
#include "../../system/ps2linux/audio/PS2Audio.h"
#endif


class OAudio : public SGZ::IAudio
{
	private:

		#ifdef SND_SDL
			SDLAudio	mAudioObject;
		#endif

		#ifdef SND_DIRECTX
			DXAudio		mAudioObject;
		#endif

		#ifdef SND_OPENAL
			OALAudio	mAudioObject;
		#endif

		#ifdef PLAT_PS2LINUX
			PS2Audio	mAudioObject;
		#endif

	public:
		OAudio()
		: mAudioObject()
		{
			/* nope... */
		}

		~OAudio()
		{
			/* nope... */
		}

		bool createInterface()
		{ return mAudioObject.createInterface(); }

		bool destroyInterface()
		{ return mAudioObject.destroyInterface(); }

		bool updateAudio()
		{ return mAudioObject.updateAudio(); }

		bool loadSFXFile( const std::string &pFilename, const std::string &pSFXName )
		{ return mAudioObject.loadSFXFile( pFilename, pSFXName ); }

		bool loadMUSFile( const std::string &pFilename, const std::string &pMUSName )
		{ return mAudioObject.loadMUSFile( pFilename, pMUSName ); }

		bool removeMUS( const std::string &pMUSName )
		{ return mAudioObject.removeMUS( pMUSName ); }

		bool removeSFX( const std::string &pSFXName )
		{ return mAudioObject.removeSFX( pSFXName ); }

		int playSFX( const std::string &pSFXName, const int pLoops = 0, const int pChannels = -1 )
		{ return mAudioObject.playSFX( pSFXName, pLoops, pChannels ); }

		bool playMUS( const std::string &pMUSName, const int pLoops = 0 )
		{ return mAudioObject.playMUS( pMUSName, pLoops ); }

		int fadeInSFX( const std::string &pSFXName, const int pTime, const int pLoops = 0, const int pChannel = -1 )
		{ return mAudioObject.fadeInSFX( pSFXName, pTime, pLoops, pChannel ); }

		bool fadeInMUS( const std::string &pMUSName, const int pTime, const int pLoops = 0 )
		{ return mAudioObject.fadeInMUS( pMUSName, pTime, pLoops ); }

		bool fadeOutCHAN( const int pChannel, const int pTime )
		{ return mAudioObject.fadeOutCHAN ( pChannel, pTime ); }

		bool fadeOutMUS( const int pTime )
		{ return mAudioObject.fadeOutMUS( pTime ); }

		bool stopMUS()
		{ return mAudioObject.stopMUS(); }

		bool stopCHAN( const int pChannel )
		{ return mAudioObject.stopCHAN( pChannel ); }

		bool pauseMUS()
		{ return mAudioObject.pauseMUS(); }

		bool pauseCHAN( const int pChannel )
		{ return mAudioObject.pauseCHAN ( pChannel ); }

		bool resumeMUS()
		{ return mAudioObject.resumeMUS(); }

		bool resumeCHAN( const int pChannel )
		{ return mAudioObject.resumeCHAN( pChannel ); }

		bool rewindMUS()
		{ return mAudioObject.rewindMUS(); }

		bool setMUSPOS( const double pPosition )
		{ return mAudioObject.setMUSPOS( pPosition ); }

		bool setVolumeMUS( const int pVolume )
		{ return mAudioObject.setVolumeMUS( pVolume ); }

		bool setVolumeSFX( const std::string &pSFXName, const int pVolume )
		{ return mAudioObject.setVolumeSFX( pSFXName, pVolume ); }

		int isCHANPlaying( const int pChannel )
		{ return mAudioObject.isCHANPlaying( pChannel ); }

		bool isMUSPlaying()
		{ return mAudioObject.isMUSPlaying(); }

		bool setChannels( const int pChannels )
		{ return mAudioObject.setChannels( pChannels ); }

		bool setPanning( const int pChannel, const int pLeft, const int pRight )
		{ return mAudioObject.setPanning( pChannel, pLeft, pRight ); }

		bool setDistance( const int pChannel, const int pDistance )
		{ return mAudioObject.setDistance( pChannel, pDistance ); }

		bool setPosition( const int pChannel, const int pAngle, const int pDistance )
		{ return mAudioObject.setPosition( pChannel, pAngle, pDistance ); }

		bool setReverseStereo( const int pChannel, const bool pFlip )
		{ return mAudioObject.setReverseStereo( pChannel, pFlip ); }

		bool createGROUP( const int pNum, const std::string &pName )
		{ return mAudioObject.createGROUP ( pNum, pName ); }

		bool reserveCHANS( const int pNum )
		{ return mAudioObject.reserveCHANS( pNum ); }

		bool groupCHAN( const int pChan, const std::string &pName )
		{ return mAudioObject.groupCHAN( pChan, pName ); }

		bool groupCHANS( const int pFrom, const int pTo, const std::string &pName )
		{ return mAudioObject.groupCHANS( pFrom, pTo, pName ); }

		int countGROUP( const std::string &pName )
		{ return mAudioObject.countGROUP( pName ); }

		int CHANinGROUP( const std::string &pName )
		{ return mAudioObject.CHANinGROUP( pName ); }

		int oldestGROUP( const std::string &pName )
		{ return mAudioObject.oldestGROUP( pName ); }

		int newestGROUP( const std::string &pName )
		{ return mAudioObject.newestGROUP( pName ); }

		bool fadeGROUP( const std::string &pName, const int pTime )
		{ return mAudioObject.fadeGROUP( pName, pTime ); }

		bool haltGROUP( const std::string &pName )
		{ return mAudioObject.haltGROUP( pName ); }

		bool removeGROUP( const std::string &pName )
		{ return mAudioObject.removeGROUP( pName ); }

}; // End of OAudio


#endif
