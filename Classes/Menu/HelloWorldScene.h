#ifndef HELLO_WORLD_SCENE_H
#define HELLO_WORLD_SCENE_H

#include "cocos2d.h"
#include "Interface/HorizontalLayout.h"
#include "Interface/VerticalLayout.h"

class HelloWorldScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // Implement the "static create()" method manually
    CREATE_FUNC(HelloWorldScene);
};

#endif // HELLO_WORLD_SCENE_H
