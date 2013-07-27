#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "BaseLayer.h"
#include "Box2D/Box2D.h"
#include "BAContactListener.h"
#include "GameObject.h"

using namespace cocos2d;

class B2DebugDrawLayer;

class HelloWorld : public BaseLayer
{
private:
    
    bool _buttonLeftPressed;
    bool _buttonRightPressed;
    bool _buttonUpPressed;
    bool _buttonDownPressed;
    bool _buttonAPressed;
    
public:
    virtual ~HelloWorld();
    
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(HelloWorld);
    
    // Variables/properties
    
    Size _winSize;
    BAContactListener *_contactListener;
    Layer *_mainLayer;
    SpriteBatchNode *_mainBatchNode;
    TMXTiledMap *_tiledMap;
    B2DebugDrawLayer *_debugLayer;
    
    std::vector<MovingHorizontalState> _movingHorizontalStates;
    std::vector<MovingVerticalState> _movingVerticalStates;
    std::vector<GameObject *> _gameObjects;
    GameObject *_player;
    
    // Box2D
    
    b2World *_world;
    
    // Methods
    
    void update(float dt);
    
    virtual void buttonLeft(bool pressed);
    virtual void buttonRight(bool pressed);
    virtual void buttonUp(bool pressed);
    virtual void buttonDown(bool pressed);
    virtual void buttonA(bool pressed);

	void removeObject(GameObject* deadObject);
    
};

#endif // __HELLOWORLD_SCENE_H__
