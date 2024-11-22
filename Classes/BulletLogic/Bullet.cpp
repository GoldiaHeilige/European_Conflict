#include "Bullet.h"
#include "EntityManager/IDamageable.h"
#include <typeinfo>

Bullet* Bullet::create(Entity* entity, std::string bulletSprite)
{
    Bullet* newObj = new Bullet();
    if (newObj != nullptr && newObj->init(entity, bulletSprite)) {
        newObj->autorelease();
        return newObj;
    }
    CC_SAFE_DELETE(newObj);
    return nullptr;
}

bool Bullet::init(Entity* entity, std::string bulletSprite)
{
    if (!Node::init()) {
        return false;
    }

    _entity = entity;

    std::string bulletSpritePath = "Bullet/" + bulletSprite + ".png";
    _model = Sprite::create(bulletSpritePath);

    if (!_model) {
        CCLOG("Error: Could not load bullet sprite from path: %s", bulletSpritePath.c_str());
        return false;
    }

    auto body = PhysicsBody::createCircle(_model->getContentSize().width / 3.9);
    body->setContactTestBitmask(1);
    this->setPhysicsBody(body);

    auto physicListener = EventListenerPhysicsContact::create();
    physicListener->onContactBegin = CC_CALLBACK_1(Bullet::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(physicListener, this);

    this->scheduleOnce([this](float) {
        this->removeFromParentAndCleanup(true);
        }, 10.0f, "remove_bullet_after_10_seconds");

    this->addChild(_model);
    return true;
}

void Bullet::fire(Vec2 direction, float velocity)
{
    getPhysicsBody()->setVelocity(direction * velocity);
}

bool Bullet::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    auto bullet = (nodeA == this) ? nodeA : (nodeB == this) ? nodeB : nullptr;
    auto target = (nodeA == this) ? nodeB : nodeA;

    if (bullet && target) {
        CCLOG("Bullet collided with target: %s", typeid(*target).name());

        if (auto damageable = dynamic_cast<IDamageable*>(target)) {
            onHit(damageable);
        }

        this->removeFromParentAndCleanup(true);
    }
    return true;
}

void Bullet::onHit(IDamageable* target) {}
