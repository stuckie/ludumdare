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
	\file IAudio.h
	\brief The Audio Interface
*/

#ifndef _IAUDIO_H_
#define _IAUDIO_H_

#include <string>

namespace SGZ
{
	class IAudio
	{
		public:
		virtual ~IAudio() {}

		virtual bool createInterface() = 0;
		/** Create a client interface to talk on */

		virtual bool destroyInterface() = 0;
		/** Destroy a client interface */

		virtual bool updateAudio() = 0;
		/** Update/Poll Audio where applicable */

		virtual bool loadSFXFile( const std::string &pFilename, const std::string &pSFXName ) = 0;
		/** Load an SFX to Play */
		virtual bool loadMUSFile( const std::string &pFilename, const std::string &pMUSName ) = 0;
		/** Load a MUS to play */

		virtual bool removeMUS( const std::string &pMUSName ) = 0;
		/** Remove a MUS from memory */
		virtual bool removeSFX( const std::string &pSFXName ) = 0;
		/** Remove a SFX from List */

		virtual int playSFX( const std::string &pSFXName, const int pLoops = 0, const int pChannel = -1 ) = 0;
		/** Play a loaded SFX file */
		virtual bool playMUS( const std::string &pMUSName, const int pLoops = 0 ) = 0;
		/** Play loaded MUS file */

		virtual int fadeInSFX( const std::string &pSFXName, const int pTime, const int pLoops = 0, const int pChannel = -1 ) = 0;
		/** Fade in loaded SFX file */
		virtual bool fadeInMUS( const std::string &pMUSName, const int pTime, const int pLoops = 0 ) = 0;
		/** Fade in loaded MUS file */

		virtual bool fadeOutCHAN( const int pChannel, const int pTime ) = 0;
		/** Fade Out SFX Channel */
		virtual bool fadeOutMUS( const int pTime ) = 0;
		/** Fade Out loaded MUS file */

		virtual bool stopMUS() = 0;
		/** Stop Mus Playing */
		virtual bool stopCHAN( const int pChannel ) = 0;
		/** Stop SFX Channel Playing */

		virtual bool pauseMUS() = 0;
		/** Pause the Mus stream */
		virtual bool pauseCHAN( const int pChannel ) = 0;
		/** Pause the SFX Channel */

		virtual bool resumeMUS() = 0;
		/** Resume the Mus stream */
		virtual bool resumeCHAN( const int pChannel ) = 0;
		/** Resume the SFX Channel */

		virtual bool rewindMUS() = 0;
		/** Rewind Music */
		virtual bool setMUSPOS( const double pPosition ) = 0;
		/** Fast Forward Music */

		virtual bool setVolumeMUS( const int pVolume ) = 0;
		/** Adjust Mus Volume */
		virtual bool setVolumeSFX( const std::string &pSFXName, const int pVolume ) = 0;
		/** Adjust SFX Volumes */

		virtual int isCHANPlaying( const int pChannel ) = 0;
		/** Is SFX Channel playing */
		virtual bool isMUSPlaying() = 0;
		/** Is Mus playing */

		virtual bool setChannels( const int pChannels ) = 0;
		/** Set amount of SFX Channels */

		virtual bool setPanning( const int pChannel, const int pLeft, const int pRight ) = 0;
		/** Set Channel Panning */
		virtual bool setDistance( const int pChannel, const int pDistance ) = 0;
		/** Set Channel Distance */
		virtual bool setPosition( const int pChannel, const int pAngle, const int pDistance ) = 0;
		/** Set Channel Position */
		virtual bool setReverseStereo( const int pChannel, const bool pFlip) = 0;
		/** Reverse Channel Stereo */

		virtual bool createGROUP( const int pNum, const std::string &pName ) = 0;
		/** Create a group of channels */

		virtual bool reserveCHANS( const int pNum ) = 0;
		/** Reserve channels for a group */

		virtual bool groupCHAN( const int pChan, const std::string &pName ) = 0;
		/** Group A channel to a group */

		virtual bool groupCHANS( const int pFrom, const int pTo, const std::string &pName ) = 0;
		/** Group Multiple Channels to a group */

		virtual int countGROUP( const std::string &pName ) = 0;
		/** Count how many channels are in a group */

		virtual int CHANinGROUP( const std::string &pName ) = 0;
		/** Returns a free channel in a group */

		virtual int oldestGROUP( const std::string &pName ) = 0;
		/** Return the oldest Channel from a group */

		virtual int newestGROUP( const std::string &pName ) = 0;
		/** Return the newest Channel from a group */

		virtual bool fadeGROUP( const std::string &pName, const int pTime ) = 0;
		/** Fade out a group */

		virtual bool haltGROUP( const std::string &pName ) = 0;
		/** Stop a group */

		virtual bool removeGROUP( const std::string &pName ) = 0;
		/** Remove a Group */

	}; // End of IAudio

} // End of Namespace


#endif
