#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "GameData/ResourcesManager.h" 
#include "audio/include/AudioEngine.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static MainMenuScene* create();
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;

    void switchToGameScene(Ref* pSender);
    void menuCloseCallback(Ref* pSender);
    void showNameInputOverlay();
    void showDifficultyInfo(Ref* pSender);

private:
    cocos2d::Sprite* _background;
};

#endif // __MAIN_MENU_SCENE_H__
