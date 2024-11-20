#include "MouseInput.h"
#include "WeaponLogic/WeaponCtrl.h"

MouseInput* MouseInput::_instance = nullptr;

MouseInput* MouseInput::getInstance() {
    if (_instance == nullptr) {
        _instance = new MouseInput();
        _instance->init();
        _instance->retain();
    }
    return _instance;
}

bool MouseInput::init() {
    if (!Node::init()) {
        log("Init MouseInput failed");
        return false;
    }

    log("MouseInput initialized");

    // Mouse event listener
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(MouseInput::onMouseDown, this);
    listener->onMouseUp = CC_CALLBACK_1(MouseInput::onMouseUp, this);
    listener->onMouseMove = CC_CALLBACK_1(MouseInput::onMouseMove, this); 
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void MouseInput::onMouseDown(Event* event) {
    auto mouseEvent = static_cast<EventMouse*>(event);
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        _isLeftMouseDown = true; 

        auto scene = Director::getInstance()->getRunningScene();
        auto character = scene->getChildByName<Character*>("Hero");
        if (character) {
            Vec2 direction = _mousePosition - character->getPosition();
            direction.normalize();
            character->shoot(direction);
        }

        this->startAutoShooting();
    }
}

void MouseInput::onMouseUp(Event* event) {
    auto mouseEvent = static_cast<EventMouse*>(event);
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        _isLeftMouseDown = false;

        this->stopAutoShooting();
    }
}

void MouseInput::onMouseMove(Event* event) {
    auto mouseEvent = static_cast<EventMouse*>(event);
    _mousePosition = this->convertToNodeSpace(Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()));
}

void MouseInput::startAutoShooting() {
    this->schedule(CC_SCHEDULE_SELECTOR(MouseInput::autoShoot), 0.2f);
}

void MouseInput::stopAutoShooting() {
    this->unschedule(CC_SCHEDULE_SELECTOR(MouseInput::autoShoot));
}

void MouseInput::autoShoot(float dt) {
    if (_isLeftMouseDown) {
        auto scene = Director::getInstance()->getRunningScene();
        auto character = scene->getChildByName<Character*>("Hero");
        if (character) {
            Vec2 direction = _mousePosition - character->getPosition();
            direction.normalize();
            character->shoot(direction);
        }
    }
}
