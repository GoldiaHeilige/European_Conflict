#include "IntroScene.h"

Scene* IntroScene::createIntroScene()
{
    return IntroScene::create();
}

bool IntroScene::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    Node::onEnter();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _physicsWorld->setGravity(Vec2::ZERO);
    _physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    _map = TMXTiledMap::create("Map/Tutorial_Map.tmx");
    this->addChild(_map);

    auto charInfo = new EntityInfo();
    charInfo->_type = "Character";
    charInfo->_name = "Hero";

    auto heroStat = new EntityStat();
    heroStat->_spd = 3;
    heroStat->_hp = 100;

    auto hero = Character::create(charInfo, heroStat);

    _character = Character::create(charInfo, heroStat);
    _character->setPosition(visibleSize / 2);
    _character->setName("Hero");
    this->addChild(_character, 1);
    this->addChild(KeyboardInput::getInstance());
    this->addChild(MouseInput::getInstance());

    auto followPlayer = cocos2d::Follow::create(_character, Rect(0, 0, _map->getMapSize().width * _map->getTileSize().width, _map->getMapSize().height * _map->getTileSize().height));
    this->runAction(followPlayer);

    auto mouseEvent = EventListenerMouse::create();
    mouseEvent->onMouseMove = CC_CALLBACK_1(IntroScene::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEvent, this);

    // Events for Map


    // Spawn Objects
    SpawnObjects spawnObjects(this);
    //spawnObjects.spawn_Civil_Normal_Cars_1(_map);
    //spawnObjects.spawn_Civil_Normal_Cars_2(_map);
    //spawnObjects.spawn_Building_Industrial_Normal(_map);
    //spawnObjects.spawn_Building_Industrial_Broken(_map);
    //spawnObjects.spawn_Industrial_Elements_Broken(_map);
    //spawnObjects.spawnFiresFromTiled(_map);

    // Spawn NPC
    spawnObjects.spawnEnemiesFromTiled(_map);

    this->scheduleUpdate();
    return true;
}

void IntroScene::update(float dt)
{
    _character->move(KeyboardInput::getInstance()->getDirection());
    Vec2 worldMousePos = this->convertToNodeSpace(_currentMousePos);

    if (worldMousePos != Vec2::ZERO) {
        Vec2 direction = worldMousePos - _character->getPosition();
        float angle = atan2(direction.y, direction.x);
        _character->rotateBody(angle);
    }
}

Sprite* IntroScene::addSpriteAtPosition(Vec2 position, int zOrder)
{
    return nullptr;
}

void IntroScene::onMouseMove(Event* event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    _currentMousePos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
}
