#ifndef _LOGGER_H_
#define _LOGGER_H_

// Logger code was pinched from my SGEngine project. -- Stuckie (LD18)

#include <string>

class Logger
{
	public:
		//! Creates or returns the current active instance of Logger.
		static Logger& instance();
		
		~Logger();
		
		enum Output {
			LOG_OUTPUT_FILE
		,	LOG_OUTPUT_TERMINAL
		,	LOG_OUTPUT_FILE_AND_TERMINAL
		,	LOG_OUTPUT_SILENT
		,	LOG_OUTPUT_DEFAULT
		};
		
		enum Type {
			LOG_TYPE_INFO
		,	LOG_TYPE_DEBUG
		,	LOG_TYPE_ERROR
		,	LOG_TYPE_DEFAULT
		};
		
		enum FileType {
			LOG_FILE_TEXT
		,	LOG_FILE_HTML
		,	LOG_FILE_UNOPENED
		};

		//! Set the default Output for Logger
		void setOutput(const Output& pOutput) { output_ = pOutput; }
		
		//! Set the default log Type for Logger
		void setType(const Type& pType) { type_ = pType; }
		
		//! Set the output file for Logger, and it's type.
		void setFile(const std::string& filename, const FileType& pFileType);
				
		//! Closes the log file.
		void closeFile();
		
		//! Log a string.
		//! Optional parameters include overriding Type and Output
		void log(const std::string& pText, const Type pType = LOG_TYPE_DEFAULT, const Output pOutput = LOG_OUTPUT_DEFAULT);
		
	protected:
		//! Log text string to File.
		void logToFile(const std::string& pText, const Type& pType);
		
		//! Log text string to Terminal.
		void logToTerm(const std::string& pText, const Type& pType);
		
		//! Creates a log Header.
		const std::string getHeader();
		
		//! Creates a log Footer.
		const std::string getFooter();
		
	private:
		//! Private constructor to stop accidental creations outside of the instance.
		Logger();
		
		Output output_;				//!< Default Log Output
		Type type_;					//!< Default Log Type
		FileType fileType_;			//!< Current File Type
		std::string filename_;		//!< Current File Name
		
		static Logger* instance_;	//!< Active instance of the Logger
};

#endif
