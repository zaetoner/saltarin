#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    double aceleracion=0;
    float desplazamiento=0;
    cocos2d::DrawNode*personaje;
    cocos2d::Rect personajeRect;
    std::vector<cocos2d::DrawNode*>plataformas;
public:
    static cocos2d::Scene* createScene();
    void enAceleracion(cocos2d::Acceleration* acc,cocos2d::Event*event);
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
