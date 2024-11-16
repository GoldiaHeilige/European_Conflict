#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include <unordered_map>

USING_NS_CC;

class AudioManager
{
public:
	static AudioManager* getInstance();

	void playMusic(std::string fileName);
	int playSFX(std::string fileName);
	void stopSFX(int sfxID);

	void setMusicVolume(float newVolume);
	void setSFXVolume(float newVolume);
private:
	static AudioManager* _instance;

	//float _musicVolume, _sfxVolume;
	float _musicVolume = 1.0f;
	float _sfxVolume = 1.0f;

	int _bgmID;
	std::unordered_map<int, std::string> _sfxIDs;
};

#endif // !__AUDIO_MANAGER_H__
