#ifndef __CAMPJAM_SCENE_H__
#define __CAMPJAM_SCENE_H__

#include "BaseLayer.h"
#include "Box2D/Box2D.h"
#include "BAContactListener.h"
#include "GameObject.h"
#include "CoffeeBar.h"
#include "HealthBar.h"

using namespace cocos2d;

class B2DebugDrawLayer;
class EnemySpawnPoint;
class CollectableSpawnPoint;

class GamePlay : public BaseLayer
{
private:
    
    bool _buttonLeftPressed;
    bool _buttonRightPressed;
    bool _buttonUpPressed;
    bool _buttonDownPressed;
    bool _buttonAPressed;
    
public:
    virtual ~GamePlay();
    
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(GamePlay);
    
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
    std::vector<EnemySpawnPoint *> _enemySpawnPoints;
    std::vector<CollectableSpawnPoint *> _collectableSpawnPoints;
    GameObject *_player;
    
	CoffeeBar *_coffeeBar;
	HealthBar *_healthBar;

    // Box2D
    
    b2World *_world;
    
    // Methods
    
    void update(float dt);
    
    GameObject* createGameObject(GameObjectType type, Dictionary *properties);
	void removeObject(GameObject* deadObject);
    
    virtual void buttonLeft(bool pressed);
    virtual void buttonRight(bool pressed);
    virtual void buttonUp(bool pressed);
    virtual void buttonDown(bool pressed);
    virtual void buttonA(bool pressed);

    
};

#endif // __CAMPJAM_SCENE_H__
