#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

   visibleSize = Director::getInstance()->getVisibleSize();
   origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////

    personaje=DrawNode::create();
    personaje->setContentSize(Size(visibleSize.width/20,visibleSize.height/30));
    personaje->setAnchorPoint(Vec2(0.5,0.5));
    personaje->drawSolidRect(Vec2(0,0),Vec2(visibleSize.width/20,visibleSize.height/30),Color4F::GREEN);
    personaje->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/3));
    addChild(personaje);

    for(unsigned i=0;i<17;i++){
        DrawNode*plataforma=DrawNode::create();
        plataforma->setContentSize(Size(visibleSize.width/5,visibleSize.height/30));
        plataforma->setAnchorPoint(Vec2(0.5,0.5));
        plataforma->drawSolidRect(Vec2(0,0),Vec2(visibleSize.width/5,visibleSize.height/30),Color4F::BLUE);
        plataforma->setPosition(Vec2(rand()%(int)visibleSize.width,rand()%(int)visibleSize.height));
        plataformas.push_back(plataforma);
        addChild(plataforma);
    }

    Device::setAccelerometerEnabled(true);
    EventListenerAcceleration* Aceleracion=EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::enAceleracion,this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Aceleracion,this);


    scheduleUpdate();
    return true;
}

void HelloWorld::update(float dt){

    Vec2 pos=personaje->getPosition();

    if(pos.y>visibleSize.height/2)
        for(DrawNode*plataforma:plataformas){
            pos.y=visibleSize.height/2;
            Vec2 posicion=plataforma->getPosition();
            posicion.y-=desplazamiento;
            plataforma->setPosition(posicion);
            if(posicion.y < origin.y){
                posicion.y+=visibleSize.height;
                posicion.x=rand()%(int)visibleSize.width;
                plataforma->setPosition(posicion);
            }
        }

    personajeRect=Rect(Vec2(pos.x-personaje->getContentSize().width/2,pos.y-personaje->getContentSize().height/2),
                       Size(personaje->getContentSize().width,personaje->getContentSize().height));

    if(desplazamiento<0)
        for(DrawNode* plataforma:plataformas){
            Vec2 posicion=plataforma->getPosition();
            float x=posicion.x-plataforma->getContentSize().width/2;
            float y=posicion.y-plataforma->getContentSize().height/2;
            float w=plataforma->getContentSize().width;
            float h=plataforma->getContentSize().height;

            Rect rect=Rect(Vec2(x,y),Size(w,h));
            if(rect.intersectsRect(personajeRect)){
                desplazamiento=10;
            }
        }

    pos.x+=aceleracion;

    desplazamiento -= 0.2;
    pos.y += desplazamiento;

    if(pos.y<origin.y)desplazamiento=10;

    if(pos.x < origin.x){
        pos.x+=visibleSize.width;
    }else if(pos.x > visibleSize.width){
        pos.x-=visibleSize.width;
    }

    personaje->setPosition(pos);

}

void HelloWorld::enAceleracion(Acceleration*acc,Event*event){
    aceleracion=acc->x*20;
}


