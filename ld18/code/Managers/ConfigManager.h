#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

class Configuration;
class HighScoreTable;
class ConfigManager
{
	public:
		~ConfigManager();
	
		//! Creates or returns the current active instance.
		static ConfigManager& instance();
		
		//! Loads the configuration ( key binds, etc.. )
		void loadConfig();
		
		//! Saves the configuration
		void saveConfig();
		
		//! Loads the HighScores
		void loadHighScores();
		
		//! Saves the HighScores
		void saveHighScores();
		
		//! Read-Access to the Configuration
		const Configuration& readConfig() const;
		
		//! Write-Access to the Configuration
		Configuration& writeConfig();
		
		//! Read-Access to the HighScoreTable
		const HighScoreTable& readHighScoreTable() const;
		
		//! Write-Access to the HighScoreTable
		HighScoreTable& writeHighScoreTable();
		
	private:
		ConfigManager();
		
		Configuration* configuration_;		//!< Current loaded Configuration
		HighScoreTable* highscoreTable_;	//!< Current loaded High Score Table
		static ConfigManager* instance_;	//!< Active instance
};

#endif
