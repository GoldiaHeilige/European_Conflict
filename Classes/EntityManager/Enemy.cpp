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

bool Enemy::init(EntityInfo* info, EntityStat* entityStat)
{
	if (!Entity::init(info, entityStat))
	{
		return false;
	}

	EntityInfo* enemyInfo = nullptr;
	EntityStat* enemyStat = nullptr;
	if (!EnemyType::getInstance()->getEnemyData(info->_name, enemyInfo, enemyStat)) {
		CCLOG("Error: Could not retrieve enemy data for %s", info->_name.c_str());
		return false;
	}
	_entityStat = enemyStat;

	auto material = PhysicsMaterial(1, 0, 1);
	auto body = PhysicsBody::createCircle(_model->getContentSize().width / 3.2);
	body->setContactTestBitmask(2);
	this->setPhysicsBody(body);

	this->scheduleUpdate();
	return true;
}

void Enemy::takeDame(float dame) {
	// Kiểm tra nếu có giáp và trừ giáp trước
	if (_entityStat->_armor > 0) {
		float armorDmg = std::min(dame, _entityStat->_armor);
		_entityStat->_armor -= armorDmg;
		dame -= armorDmg; // Sát thương còn lại sau khi trừ giáp
	}

	// Sau khi trừ giáp (nếu có), trừ vào HP
	_entityStat->_hp -= dame;
	CCLOG("Enemy took %.2f damage, remaining HP: %.2f, Armor: %.2f", dame, _entityStat->_hp, _entityStat->_armor);

	if (_entityStat->_hp <= 0) {
		die(); // Kẻ địch chết nếu HP <= 0
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

void Enemy::update(float dt)
{
	if (!_isMoving) {
		_movementTimer += dt;
		if (_movementTimer >= _nextMovementTime) {
			_movementTimer = 0.0f;
			_nextMovementTime = (rand() % 6 + 5); 

			_targetDirection = Vec2(cos(rand() % 360 * M_PI / 180.0f), sin(rand() % 360 * M_PI / 180.0f));

			float moveDistance = rand() % 101 + 100;
			_targetPosition = getPosition() + _targetDirection * moveDistance;

			float angle = std::atan2(_targetDirection.y, _targetDirection.x) * 180 / M_PI;
			setRotation(angle);

			_isMoving = true;
		}
	}
	else {
		float moveSpeed = _entityStat->_spd * dt;
		Vec2 direction = _targetPosition - getPosition();

		if (direction.length() <= moveSpeed) {
			setPosition(_targetPosition);
			_isMoving = false;
		}
		else {
			direction.normalize();
			setPosition(getPosition() + direction * moveSpeed);
		}
	}
}
