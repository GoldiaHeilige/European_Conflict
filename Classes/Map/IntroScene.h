#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "cocos2d.h"
#include "GameData/ResourcesManager.h"
#include "Interface/HUDLayer.h"
#include "Interface/InventoryManager.h"
#include "Menu/MainMenuScene.h"

#include "UserInput/KeyboardInput.h"
#include "UserInput/MouseInput.h"

#include "Map/SpawnObjects.h"
#include "Map/SpawnItems.h"

#include "Audio/ProximitySound.h"

using namespace cocos2d;

class IntroScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createIntroScene();
    virtual bool init() override;
    void update(float dt) override;

    void onEnter();
    void onExit(Ref* pSender);
    void preloadResources();

private:
    void onMouseMove(Event* event);

    cocos2d::TMXTiledMap* _map;

    Sprite* addSpriteAtPosition(Vec2 position, int zOrder);

    Character* _character;
    cocos2d::Vec2 _direction;
    Vec2 _currentMousePos = Vec2::ZERO;
    HUDLayer* _hudLayer;

    CREATE_FUNC(IntroScene);
};

#endif // __INTROSCENE_H__