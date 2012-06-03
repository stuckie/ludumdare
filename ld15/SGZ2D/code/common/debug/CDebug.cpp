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
	\file CDebug.cpp
	\brief SGEngine Debug Logging Facilities

	For when things go wrong, we need to be able to log whatever we get.
	Be them errors, warnings or debug messages!
*/

#include "CDebug.h"
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

using namespace SGZ;

CLogger::CLogger()
:   mVerbose ( false )
{
	#ifdef DEBUG
		mVerbose = true;
	#endif

}

CLogger::~CLogger()
{

}

void CLogger::log(const SGZLOG::Type pType, const std::string &pErrorString) const
{
	if (false == mVerbose)
		return;

	std::string timeString, statusString;
	std::ofstream logFile;

	time_t rawTime;
	time (&rawTime);

	if (pType==SGZLOG::Debug)
	{
		statusString = "[SGZLOG:Debug] ";
		logFile.open("debug.log", std::ios::app);
	}

	if (pType==SGZLOG::Error)
	{
		statusString = "[SGZLOG:Error] ";
		logFile.open("error.log");
	}

	if (pType==SGZLOG::Warning)
	{
		statusString = "[SGZLOG:Warning] ";
		logFile.open("warning.log", std::ios::app);
	}

	if (pType==SGZLOG::Message)
		statusString = "[SGZLOG:Message] ";

	timeString = statusString + std::string(ctime(&rawTime));

	if (pType==SGZLOG::Message)
	{
		std::cout << statusString << pErrorString << std::endl;
	}
	else
	{
		logFile << timeString << statusString << pErrorString << std::endl;
		logFile << std::flush;
		logFile.close();

		if ((pType==SGZLOG::Error) || (mVerbose==true))
			std::cout << timeString << statusString << pErrorString << std::endl;
	}
}

void CLogger::setVerbosity(const bool pSet)
{
	mVerbose = pSet;
}

/* We need to instantiate the Logger so it's singleton always works */
SGZ::CLogger logSingleton;
