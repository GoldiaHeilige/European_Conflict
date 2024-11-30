#include "ProximitySound.h"

ProximitySound::ProximitySound(Node* player)
    : _player(player) {}

void ProximitySound::playSFX(const std::string& fileName, const Vec2& soundPosition, float maxDistance)
{
    int soundID = AudioManager::getInstance()->playSFX(fileName);
    if (soundID != AudioEngine::INVALID_AUDIO_ID)
    {
        _activeSounds.push_back({ soundID, soundPosition, maxDistance });
        updateSoundVolumes(); // Cập nhật âm lượng ngay sau khi phát
    }
}

void ProximitySound::updateSoundVolumes()
{
    if (!_player) return;

    Vec2 playerPos = _player->getPosition();

    for (size_t i = 0; i < _activeSounds.size(); ++i)
    {
        auto& sound = _activeSounds[i];

        float distance = playerPos.distance(sound.position);
        float volume = 1.0f - std::min(distance / sound.maxDistance, 1.0f);
        AudioEngine::setVolume(sound.soundID, volume);

        if (AudioEngine::getState(sound.soundID) != AudioEngine::AudioState::PLAYING)
        {
            AudioEngine::stop(sound.soundID);
            _activeSounds[i] = _activeSounds.back(); 
            _activeSounds.pop_back();            
            --i;                                 
        }
    }
}