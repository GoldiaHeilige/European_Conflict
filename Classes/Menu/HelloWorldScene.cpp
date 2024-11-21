#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorldScene::createScene() {
    return HelloWorldScene::create();
}

bool HelloWorldScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // Lấy kích thước màn hình
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Tạo các layout
    auto horizontalLayout = HorizontalLayout::create();
    auto verticalLayout = VerticalLayout::create();

    // Đặt các layout vào giữa màn hình
    horizontalLayout->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    verticalLayout->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // Tạo các Sprite cho HelloWorld.png
    auto spriteTop = Sprite::create("HelloWorld.png");
    auto spriteBottom = Sprite::create("HelloWorld.png");
    auto spriteLeft = Sprite::create("HelloWorld.png");
    auto spriteRight = Sprite::create("HelloWorld.png");

    // Đặt anchorPoint và thêm các sprite vào layout
    spriteTop->setAnchorPoint(Vec2(0.5, 1)); // Phía trên
    spriteBottom->setAnchorPoint(Vec2(0.5, 0)); // Phía dưới
    spriteLeft->setAnchorPoint(Vec2(0, 0.5)); // Phía trái
    spriteRight->setAnchorPoint(Vec2(1, 0.5)); // Phía phải

    // Đặt các sprite vào màn hình
    spriteTop->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y));
    spriteBottom->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y));
    spriteLeft->setPosition(Vec2(origin.x, visibleSize.height / 2 + origin.y));
    spriteRight->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height / 2 + origin.y));

    // Thêm các sprite vào scene
    this->addChild(spriteTop);
    this->addChild(spriteBottom);
    this->addChild(spriteLeft);
    this->addChild(spriteRight);

    // Tạo các Label
    auto labelTop = Label::createWithTTF("Top Label", "fonts/Marker Felt.ttf", 24);
    auto labelBottom = Label::createWithTTF("Bottom Label", "fonts/Marker Felt.ttf", 24);

    // Đặt vị trí cho các Label
    labelTop->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - 50));
    labelBottom->setPosition(Vec2(visibleSize.width / 2 + origin.x, 50));

    // Thêm các Label vào scene
    this->addChild(labelTop);
    this->addChild(labelBottom);

    return true;
}
