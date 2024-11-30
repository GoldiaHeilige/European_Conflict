#ifndef __PROXIMITY_SOUND_H__
#define __PROXIMITY_SOUND_H__

#include "cocos2d.h"
#include "AudioManager.h"
#include "AudioEngine.h"

USING_NS_CC;

class ProximitySound
{
public:
    ProximitySound(Node* player);

    void playSFX(const std::string& fileName, const Vec2& soundPosition, float maxDistance);
    void updateSoundVolumes();

private:
    Node* _player; // Tham chiếu đến node của người chơi
    struct SoundData
    {
        int soundID;
        Vec2 position;
        float maxDistance;
    };
    std::vector<SoundData> _activeSounds;
};

#endif // __PROXIMITY_SOUND_H__
