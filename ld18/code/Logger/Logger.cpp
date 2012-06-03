#include "Logger.h"

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

Logger* Logger::instance_ = 0;

Logger& Logger::instance()
{
	if (0 == instance_)
		instance_ = new Logger;
		
	return *instance_;		
}

Logger::Logger()
: output_(LOG_OUTPUT_TERMINAL)
, type_(LOG_TYPE_DEBUG)
, fileType_(LOG_FILE_UNOPENED)
, filename_("engine.log")
{
	
}

Logger::~Logger()
{
	closeFile();
	
	delete instance_;
	instance_ = 0;
}

void Logger::setFile(const std::string& filename, const FileType& pFileType)
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	
	filename_ = timeString + "_" + filename; 
	fileType_ = pFileType;
	
	std::ofstream logFile;
	logFile.open(filename_.c_str());
	logFile << getHeader() << std::flush;
	logFile.close();
}

void Logger::closeFile()
{
	std::ofstream logFile;
	logFile.open(filename_.c_str(), std::ios::app);
	logFile << getFooter() << std::flush;
	logFile.close();
	
	fileType_ = LOG_FILE_UNOPENED;
}

void Logger::log(const std::string& pText, const Type pType, const Output pOutput)
{
	bool outputText(true);
	Type logType(type_);
	Output logOutput(output_);
	
	// Check for non-defaults.
	if (pType != LOG_TYPE_DEFAULT)
		logType = pType;
		
	if (pOutput != LOG_OUTPUT_DEFAULT)
		logOutput = pOutput;
		
	if (LOG_OUTPUT_SILENT == logOutput) // if we're not going to output this, might as well leave now.
		return;
		
	// Check if we are actually going to output this.
	switch (logType) {
		case LOG_TYPE_DEBUG:
			#if !defined(DEBUG)
				outputText = false;
			#endif
			break;
		case LOG_TYPE_INFO:
		case LOG_TYPE_ERROR:
			outputText = true;
			break;
		default:
			log("Logger: Unknown log type! Tried to Log - " + pText, LOG_TYPE_ERROR);
	}
	
	if (false == outputText)// if we're not going to output this, might as well leave now.
		return;
		
	// See where we're going to output this.
	switch (logOutput) {
		case LOG_OUTPUT_FILE:
			logToFile(pText, logType);
			break;
		case LOG_OUTPUT_FILE_AND_TERMINAL:
			logToFile(pText, logType);
			logToTerm(pText, logType);
			break;
		case LOG_OUTPUT_TERMINAL:
			logToTerm(pText, logType);
			break;
		default:
			log("Logger: Unknown log output! Tried to Log - " + pText, LOG_TYPE_ERROR, LOG_OUTPUT_FILE_AND_TERMINAL);
	}
}

void Logger::logToTerm(const std::string& pText, const Type& pType)
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	
	switch (pType) {
		case LOG_TYPE_DEBUG:
			std::cout << "[DEBUG]" << timeString << "[DEBUG]" << pText;
			break;
		case LOG_TYPE_INFO:
			std::cout << "[INFO]" << timeString << "[INFO]" << pText;
			break;
		case LOG_TYPE_ERROR:
			std::cerr << "[ERROR]" << timeString << "[ERROR]" << pText;
			break;
		default:
			break; // Should not get here.. so just ignore...
	}
}

void Logger::logToFile(const std::string& pText, const Type& pType)
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	std::string finalText;
	
	switch (fileType_) {
		case LOG_FILE_TEXT:
			switch (pType) {
				case LOG_TYPE_DEBUG:
					finalText = ("[DEBUG]" + timeString + "[DEBUG]" + pText);
					break;
				case LOG_TYPE_INFO:
					finalText = ("[INFO]" + timeString + "[INFO]" + pText);
					break;
				case LOG_TYPE_ERROR:
					finalText = ("[ERROR]" + timeString + "[ERROR]" + pText);
					break;
				default:
					break; // Should not get here.. so just ignore...
			}
			break;
		case LOG_FILE_HTML:
			switch (pType) {
				case LOG_TYPE_DEBUG:
					finalText = ("\t<div id=\"DEBUG\">[" + timeString + "] " + pText + "</div>");
					break;
				case LOG_TYPE_INFO:
					finalText = ("\t<div id=\"INFO\">[" + timeString + "] " + pText + "</div>");
					break;
				case LOG_TYPE_ERROR:
					finalText = ("\t<div id=\"ERROR\">[" + timeString + "] " + pText + "</div>");
					break;
				default:
					break; // Should not get here.. so just ignore...
			}
			break;
		case LOG_FILE_UNOPENED:
			log("Logger: There is no file open to output to!", LOG_TYPE_ERROR, LOG_OUTPUT_TERMINAL);
			return;
		default:
			break; // Should not get here.. so just ignore
	}
	
	std::ofstream logFile;
	logFile.open(filename_.c_str(), std::ios::app);
	logFile << finalText << std::flush;
	logFile.close();
}

const std::string Logger::getHeader()
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	
	std::string header;
	
	switch (fileType_) {
		case LOG_FILE_HTML:
			header = ("<html>\n\t<head>\n\t\t<title>SGEngine Log</title>\n\t</head>\n\t<body>\n\t\t<h1>Started - " + timeString + "</h1>");
			break;
		case LOG_FILE_TEXT:
			header = "SGEngine Log\nStarted - " + timeString + "\n";
			break;
		default:
			break;
	}
	
	return header;
}

const std::string Logger::getFooter()
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	
	std::string footer;
	
	switch (fileType_) {
		case LOG_FILE_HTML:
			footer = ("\t\t<h1>Ended - " + timeString + "</h1>\n\t</body>\n</html>");
			break;
		case LOG_FILE_TEXT:
			footer = "Ended - " + timeString + "\n";
			break;
		default:
			break;
	}
	
	return footer;
}