#include "Enemy.h"
#include "EnemyType.h"

Enemy* Enemy::create(EntityInfo* info, EntityStat* entityStat)
{
	auto character = new Enemy();
	if (character != nullptr && character->init(info, entityStat)) {
		character->autorelease();
		return character;
	}

	CC_SAFE_DELETE(character);
	return nullptr;
}

Enemy::~Enemy() {
	if (_entityStat) {
		delete _entityStat;
		_entityStat = nullptr;
	}
}

bool Enemy::init(EntityInfo* info, EntityStat* entityStat) {
	if (!Entity::init(info, entityStat)) {
		return false;
	}

	if (!info || !entityStat) {
		CCLOG("Error: Invalid EntityInfo or EntityStat provided for Enemy.");
		return false;
	}

	_entityStat = new EntityStat(*entityStat);

	//std::string spriteFileName = "Entity/" + info->_type + "/" + info->_name + ".png";
	//_model = Sprite::create(spriteFileName);

	AnimationUtils::loadSpriteFrameCache("Entity/" + _info->_type + "/", _info->_name);
	auto idle = AnimationUtils::createAnimation(_info->_name, 1.0f);
	Animate* animateIdle = Animate::create(idle.first);
	auto idleLoop = RepeatForever::create(animateIdle);

	_model = Sprite::createWithSpriteFrameName("./" + _info->_name + " (1)");
	_model->runAction(idleLoop);

	_model->setAnchorPoint(Vec2(0.5, 0.5));

	if (!_model || _model->getContentSize().width <= 0) {
		CCLOG("Error: Enemy model is invalid or uninitialized.");
		delete _entityStat; 
		_entityStat = nullptr;
		return false;
	}

	this->addChild(_model, 2);

	auto material = PhysicsMaterial(1, 0, 1);
	auto body = PhysicsBody::createCircle(_model->getContentSize().width / 3.2);
	body->setContactTestBitmask(2);
	this->setPhysicsBody(body);

	this->scheduleUpdate();
	return true;
}

void Enemy::takeDame(float dame) {
	if (!_entityStat) {
		CCLOG("Error: Enemy's EntityStat is null. Cannot take damage.");
		return;
	}

	_entityStat->_hp -= dame;
	CCLOG("Current Enemy HP: %f", _entityStat->_hp);

	if (_entityStat->_hp <= 0) {
		die();
	}
}

void Enemy::die()
{
	CCLOG("Enemy has died!");
	if (this->getPhysicsBody()) {
		this->removeComponent(this->getPhysicsBody());
	}
	this->removeChild(_model);

	AnimationUtils::loadSpriteFrameCache("Entity/" + _info->_type + "/", _info->_name + "_Death");
	auto deathAnimation = AnimationUtils::createAnimation(_info->_name + "_Death", 1.0f);
	auto animateDeath = Animate::create(deathAnimation.first);

	auto deathSprite = Sprite::createWithSpriteFrameName("./" + _info->_name + "_Death" + " (1)");
	this->addChild(deathSprite);

	auto sequence = Sequence::create(
		animateDeath,
		FadeOut::create(2.0f),
		CallFunc::create([this]() {
			this->removeFromParentAndCleanup(true);
			}),
		nullptr
	);
	deathSprite->runAction(sequence);
}