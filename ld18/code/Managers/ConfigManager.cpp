#include "ConfigManager.h"

#include <cassert>

#include "../Loadables/Configuration.h"
#include "../Loadables/HighScoreTable.h"

ConfigManager* ConfigManager::instance_ = 0;

ConfigManager& ConfigManager::instance()
{
	if (0 == instance_)
		instance_ = new ConfigManager;
		
	return *instance_;		
}

ConfigManager::ConfigManager()
: configuration_(0)
, highscoreTable_(0)
{
	
}

ConfigManager::~ConfigManager()
{
	delete instance_;
	instance_ = 0;
}

void ConfigManager::loadConfig()
{
	// Load config.cfg
}

void ConfigManager::saveConfig()
{
	// Save config.cfg
}

void ConfigManager::loadHighScores()
{
	// Load scores.tbl
}

void ConfigManager::saveHighScores()
{
	// Save scores.tbl
}

const Configuration& ConfigManager::readConfig() const
{
	assert(configuration_);
	return *configuration_;
}

Configuration& ConfigManager::writeConfig()
{
	assert(configuration_);
	return *configuration_;
}

const HighScoreTable& ConfigManager::readHighScoreTable() const
{
	assert(highscoreTable_);
	return *highscoreTable_;
}

HighScoreTable& ConfigManager::writeHighScoreTable()
{
	assert(highscoreTable_);
	return *highscoreTable_;
}