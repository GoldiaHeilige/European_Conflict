#include "IntroScene.h"
#include "EntityManager/PlayerLogic/Character.h"
#include "EntityManager/PlayerLogic/PlayerStatsManager.h"
#include "EntityManager/EnemyLogic/Enemy.h"
#include "EntityManager/IDamageable.h"

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

    auto inventoryManager = InventoryManager::getInstance();
    inventoryManager->setName("InventoryManager");
    this->addChild(inventoryManager);
    CCLOG("InventoryManager added to the scene");

    _physicsWorld->setGravity(Vec2::ZERO);
    /*_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);*/

    _map = TMXTiledMap::create("Map/Tutorial_Map.tmx");
    this->addChild(_map);

    auto charInfo = new EntityInfo();
    charInfo->_type = "Character";
    charInfo->_name = "Hero";

    auto heroStats = PlayerStatsManager::getInstance()->getPlayerStats();

    _character = Character::create(charInfo, heroStats);
    _character->setPosition(visibleSize / 2);
    _character->setName("Hero");
    this->addChild(_character, 1);

    auto proximitySound = new ProximitySound(_character);

    auto followPlayer = Follow::create(_character, Rect::ZERO);
    this->runAction(followPlayer);

    _hudLayer = HUDLayer::create();
    this->addChild(_hudLayer);

    auto mouseEvent = EventListenerMouse::create();
    mouseEvent->onMouseMove = CC_CALLBACK_1(IntroScene::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEvent, this);

    // Events for Map


    SpawnObjects spawnObjects(this);
    // Spawn Objects
    //spawnObjects.spawn_Civil_Normal_Cars_1(_map);
    //spawnObjects.spawn_Civil_Normal_Cars_2(_map);
    //spawnObjects.spawn_Building_Industrial_Normal(_map);
    //spawnObjects.spawn_Building_Industrial_Broken(_map);
    //spawnObjects.spawn_Industrial_Elements_Broken(_map);
    //spawnObjects.spawnFiresFromTiled(_map);

    // Spawn NPC
    spawnObjects.spawnEnemiesFromTiled(_map);

    // Spawn Items
    SpawnItems spawnItems(this);
    spawnItems.spawnMedicalFromTiled(_map);




    this->addChild(KeyboardInput::getInstance());
    this->addChild(MouseInput::getInstance());
    this->scheduleUpdate();
    return true;
}

void IntroScene::update(float dt)
{
    if (_hudLayer)
    {
        Vec2 playerPosition = _character->getPosition();
        _hudLayer->updateWithPlayerPosition(playerPosition);
    }

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

void IntroScene::onEnter()
{
    Scene::onEnter();

    ResourcesManager::getInstance()->preloadResourcesForGroup("Game");
    ResourcesManager::getInstance()->releaseResourcesForGroup("Menu");
}

void IntroScene::onExit(Ref* pSender)
{

    ResourcesManager::getInstance()->releaseResourcesForGroup("Game");

    auto scene = MainMenuScene::create();  
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
}

void IntroScene::preloadResources()
{
    auto resMgr = ResourcesManager::getInstance();
}