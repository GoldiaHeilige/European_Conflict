#include "Character.h"
#include "WeaponLogic/WeaponCtrl.h"

Character* Character::create(EntityInfo* info, EntityStat* entityStat) {
    auto character = new Character();
    if (character != nullptr && character->init(info, entityStat)) {
        character->autorelease();
        return character;
    }
    CC_SAFE_DELETE(character);
    return nullptr;
}

bool Character::init(EntityInfo* info, EntityStat* entityStat) {
    if (!Entity::init(info, entityStat)) {
        return false;
    }

    _stat = entityStat;

    if (!_model) {
        std::string initialSprite = getSpriteFileNameForCategory("");  
        _model = Sprite::create(initialSprite);
        if (_model) {
            this->addChild(_model);
        }
    }

    auto characterBody = PhysicsBody::createBox(this->getContentSize());
    characterBody->setDynamic(true);
    characterBody->setContactTestBitmask(true);
    this->addComponent(characterBody);

    return true;
}

Character::Character() : _model(nullptr), _stat(nullptr) {}

Character::~Character() {
    if (_model) {
        _model->removeFromParent();
    }
}

void Character::takeDame(int dame) {
    _stat->_hp -= dame;
    CCLOG("Hero took %d damage, remaining HP: %f", dame, _stat->_hp);

    if (_stat->_hp <= 0) {
        die();
    }
}

void Character::die() {
    CCLOG("Hero has died!");
    if (this->getPhysicsBody()) {
        this->removeComponent(this->getPhysicsBody());
    }
    this->removeChild(_model);

    AnimationUtils::loadSpriteFrameCache("Entity/" + _info->_type + "/", _info->_name + "_Death");

    auto deathAnimation = AnimationUtils::createAnimation(_info->_name + "_Death", 1.0f);
    auto animateDeath = Animate::create(deathAnimation.first);

    auto deathSprite = Sprite::createWithSpriteFrameName(_info->_name + "_Death (1)");
    this->addChild(deathSprite);

    auto sequence = Sequence::create(
        animateDeath,
        CallFunc::create([this]() {
            auto mainMenuScene = MainMenuScene::create();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, mainMenuScene));
            }),
        nullptr
    );
    deathSprite->runAction(sequence);
}

void Character::shoot(Vec2 direction) {
    WeaponCtrl::getInstance()->fireBullet(this, direction);
}

void Character::move(Vec2 direction) {
    if (direction.isZero()) {
        return;
    }
    this->setPosition(this->getPosition() + direction * _stat->_spd);
}

void Character::rotateBody(float angle) {
    float correctionAngle = -90.0f;
    _model->setRotation(-CC_RADIANS_TO_DEGREES(angle) + correctionAngle);
}

void Character::update(float dt) {
}

void Character::onEnter() {
    Node::onEnter();

    cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(
        "WeaponChanged", [this](cocos2d::EventCustom* event) {
            std::string* weaponCategory = static_cast<std::string*>(event->getUserData());
            this->updateSpriteBasedOnWeaponCategory(*weaponCategory);
        });
}

void Character::onExit() {
    cocos2d::Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("WeaponChanged");
    Node::onExit();
}

void Character::updateSpriteBasedOnWeaponCategory(const std::string& category) {
    std::string spriteFileName = getSpriteFileNameForCategory(category);

    if (_model) {
        this->removeChild(_model, true); 
    }

    _model = Sprite::create(spriteFileName);
    if (_model) {
        this->addChild(_model);
    }
}

std::string Character::getSpriteFileNameForCategory(const std::string& category) {
    std::string basePath = "Entity/" + _info->_type + "/";

    if (category == "Pistol") {
        return basePath + "Hero_Pistol.png"; 
    }
    else if (category == "Submachine Gun") {
        return basePath + "Hero_Rifle.png";  
    }
    else if (category == "Assault Rifle") {
        return basePath + "Hero_Rifle.png";  
    }
    else if (category == "Grenade Launcher") {
        return basePath + "Hero_GrenadeLauncher.png";  
    }

    return basePath + "Hero.png"; 
}

