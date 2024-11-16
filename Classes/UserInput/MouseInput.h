#ifndef __MOUSE_INPUT_H__
#define __MOUSE_INPUT_H__

#include "cocos2d.h"
#include "EntityManager/Character.h"

USING_NS_CC;

class MouseInput : public Node
{
public:
    static MouseInput* getInstance();

    bool init() override;

private:
    static MouseInput* _instance;

    bool _isLeftMouseDown = false; 
    Vec2 _mousePosition;        

    void onMouseDown(Event* event);
    void onMouseUp(Event* event);
    void onMouseMove(Event* event); 

    void startAutoShooting(); 
    void stopAutoShooting(); 
    void autoShoot(float dt); 

};

#endif // !__MOUSE_INPUT_H__
