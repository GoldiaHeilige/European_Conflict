#include "PlayerStatsManager.h"

PlayerStatsManager* PlayerStatsManager::getInstance()
{
    static PlayerStatsManager instance;
    return &instance;
}

PlayerStatsManager::PlayerStatsManager()
    : _playerStats(nullptr)
{
    initializePlayerStats();
}

PlayerStatsManager::~PlayerStatsManager()
{
    delete _playerStats;
}

void PlayerStatsManager::initializePlayerStats()
{
    if (_playerStats == nullptr)
    {
        _playerStats = new EntityStat();
        _playerStats->_hp = 100.0f; // default HP
        _playerStats->_spd = 3.0f;  // default speed
        _playerStats->_armor = 0.0f; // default armor
    }
}

void PlayerStatsManager::updatePlayerStats(float hp, float speed, float armor)
{
    if (_playerStats)
    {
        _playerStats->_hp = hp;
        _playerStats->_spd = speed;
        _playerStats->_armor = armor;
    }
}

EntityStat* PlayerStatsManager::getPlayerStats()
{
    return _playerStats;
}
