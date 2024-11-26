#include "AudioManager.h"
#include "AudioEngine.h"

AudioManager* AudioManager::_instance;

AudioManager* AudioManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new AudioManager();
    }
    return _instance;
}

void AudioManager::playMusic(std::string fileName)
{
    AudioEngine::stop(_bgmID);
    _bgmID = AudioEngine::play2d("Audio/Music/" + fileName, true, _musicVolume);
}

int AudioManager::playSFX(std::string fileName)
{
    int sfxID = AudioEngine::play2d("Audio/SFX/" + fileName, false, _sfxVolume);
    if (sfxID != AudioEngine::INVALID_AUDIO_ID)
    {
        _sfxIDs[sfxID] = fileName; 
    }
    return sfxID;
}

void AudioManager::stopSFX(int sfxID)
{
    if (_sfxIDs.find(sfxID) != _sfxIDs.end())
    {
        AudioEngine::stop(sfxID);
        _sfxIDs.erase(sfxID); 
    }
}

void AudioManager::setMusicVolume(float newVolume)
{
    _musicVolume = newVolume;

    AudioEngine::setVolume(_bgmID, _musicVolume);
}

void AudioManager::setSFXVolume(float newVolume)
{
    _sfxVolume = newVolume;
}

void AudioManager::preloadAudio(const std::string& fileName)
{
    auto SFX_PATH = "Audio/SFX/" + fileName;
    auto MUSIC_PATH = "Audio/Music/" + fileName;
    AudioEngine::preload(SFX_PATH);
    AudioEngine::preload(MUSIC_PATH);
}

void AudioManager::preloadAudioBatch(const std::vector<std::string>& fileNames)
{
    for (const auto& fileName : fileNames)
    {
        preloadAudio(fileName);
    }
}