#include "HelloWorldScene.h"

#include "Player.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"

USING_NS_CC;

HelloWorld::~HelloWorld() {
    
    delete _contactListener;
    
    CC_SAFE_DELETE(_player);
    
    for(std::vector<GameObject *>::size_type i = 0; i != _gameObjects.size(); i++) {
        _gameObjects[i]->release();
    }
    
}

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !BaseLayer::init() )
    {
        return false;
    }
    
    _winSize = Director::sharedDirector()->getWinSize();
    //Size visibleSize = Director::sharedDirector()->getVisibleSize();
    //Point origin = Director::sharedDirector()->getVisibleOrigin();
    
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("chars.plist");
    
    _contactListener = new BAContactListener();
    _mainLayer = Layer::create();
    _mainBatchNode = SpriteBatchNode::create("chars.png");
    _tiledMap = TMXTiledMap::create("main.tmx");
    
    _mainBatchNode->getTexture()->setAliasTexParameters();
    
    _mainLayer->addChild(_tiledMap);
    _mainLayer->addChild(_mainBatchNode);
    
    this->addChild(_mainLayer);
    
    TMXObjectGroup *collisionGroup = _tiledMap->objectGroupNamed("collision");
    TMXObjectGroup *gameObjectsGroup = _tiledMap->objectGroupNamed("objects");
    
    b2Vec2 gravity = b2Vec2(0.0f, kGravity);
    
    _world = new b2World(gravity);
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);
    _world->SetContactListener(_contactListener);
    
    Array *gameObjects = gameObjectsGroup->getObjects();
    Object *gameObject;
    CCARRAY_FOREACH(gameObjects, gameObject) {
        Dictionary *objectProperties = (Dictionary *)gameObject;
        
        String *type = (String *)objectProperties->objectForKey("type");
        if (!type)
            continue;
        
        if (type->compare("Player") == 0) {
            
            _player = new Player();
            _player->init(_world, objectProperties);
            
            _mainBatchNode->addChild(_player->getNode());
            //_gameObjects.push_back(player);
        }
        
    }
    
    Array *collisions = collisionGroup->getObjects();
    Object *collision;
    CCARRAY_FOREACH(collisions, collision) {
        Dictionary *objectProperties = (Dictionary *)collision;
        
        float x = floatValue(objectProperties->objectForKey("x")) / PTM_RATIO;
        float y = floatValue(objectProperties->objectForKey("y")) / PTM_RATIO;
        
        String *width = (String *)objectProperties->objectForKey("width");
        Array *points = (Array *)objectProperties->objectForKey("polylinePoints");
        if (!points)
            points = (Array *)objectProperties->objectForKey("points");
        Object *aObject;
        
        if (width->compare("") != 0) {
            
            float halfwidth = floatValue(width) / 2.0f / PTM_RATIO;
            float halfheight = floatValue(objectProperties->objectForKey("height")) / 2.0f / PTM_RATIO;
            
            x += halfwidth;
            y += halfheight;
            
            b2PolygonShape shape;
            shape.SetAsBox(halfwidth, halfheight);
            
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            
            b2BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(x, y);
            b2Body *body = _world->CreateBody(&bodyDef);
            
            body->CreateFixture(&fixtureDef);
            
        } else if (points) {
            
            std::vector<b2Vec2> verts;
            
            CCARRAY_FOREACH(points, aObject) {
                Dictionary *dict = (Dictionary *)aObject;
                
                float vertX = floatValue(dict->objectForKey("x")) / PTM_RATIO;
                float vertY = floatValue(dict->objectForKey("y")) / PTM_RATIO;
                
                verts.push_back(b2Vec2(vertX, -vertY));
            }
            
            b2ChainShape shape;
            shape.CreateChain(&verts[0], points->count());
            
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            
            b2BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(x, y);
            b2Body *body = _world->CreateBody(&bodyDef);
            
            body->CreateFixture(&fixtureDef);
        }
        
    }
    
    _movingHorizontalStates.push_back(MovingStateHorizontalStopped);
    _movingVerticalStates.push_back(MovingStateVerticalStopped);
    
    this->scheduleUpdate();
    
    //this->addChild(B2DebugDrawLayer::create(_world, PTM_RATIO), 9999);
    
    return true;
}

void HelloWorld::update(float dt) {
    
    _world->Step(dt, 8, 3);
    
    _player->setMovingHorizontalState(_movingHorizontalStates[_movingHorizontalStates.size() - 1]);
    _player->setMovingVerticalState(_movingVerticalStates[_movingVerticalStates.size() - 1]);
    _player->update(dt);
    
    Point playerPosition = _player->getNode()->getPosition();
    
    int x = MAX(playerPosition.x, _winSize.width/2);
    int y = MAX(playerPosition.y, _winSize.height/2);
    x = MIN(x, (_tiledMap->getMapSize().width * _tiledMap->getTileSize().width) - _winSize.width / 2);
    y = MIN(y, (_tiledMap->getMapSize().height * _tiledMap->getTileSize().height) - _winSize.height/2);
    Point actualPosition = ccp(x, y);
    
    Point centerOfView = ccp(_winSize.width/2, _winSize.height/2);
    Point viewPoint = ccpSub(centerOfView, actualPosition);
    _mainLayer->setPosition(viewPoint);
    
    for(std::vector<GameObject *>::size_type i = 0; i != _gameObjects.size(); i++) {
        _gameObjects[i]->update(dt);
    }
    
}

void HelloWorld::buttonLeft(bool pressed) {
    
    if (pressed) {
        
        if (_buttonLeftPressed)
            return;
        _buttonLeftPressed = true;
        
        _movingHorizontalStates.push_back(MovingStateLeft);
        
    } else {
        
        _buttonLeftPressed = false;
        
        std::vector<MovingHorizontalState>::iterator pos;
        pos = std::find(_movingHorizontalStates.begin(), _movingHorizontalStates.end(), MovingStateLeft);
        if (pos != _movingHorizontalStates.end()) {
            _movingHorizontalStates.erase(pos);
        }
        
    }
    
}

void HelloWorld::buttonRight(bool pressed) {
    
    if (pressed) {
        
        if (_buttonRightPressed)
            return;
        _buttonRightPressed = true;
        
        _movingHorizontalStates.push_back(MovingStateRight);
        
    } else {
        
        _buttonRightPressed = false;
        
        std::vector<MovingHorizontalState>::iterator pos;
        pos = std::find(_movingHorizontalStates.begin(), _movingHorizontalStates.end(), MovingStateRight);
        if (pos != _movingHorizontalStates.end()) {
            _movingHorizontalStates.erase(pos);
        }
        
    }
    
}

void HelloWorld::buttonUp(bool pressed) {
    
    if (pressed) {
        
        if (_buttonUpPressed)
            return;
        _buttonUpPressed = true;
        
        _movingVerticalStates.push_back(MovingStateUp);
        
    } else {
        
        _buttonUpPressed = false;
        
        std::vector<MovingVerticalState>::iterator pos;
        pos = std::find(_movingVerticalStates.begin(), _movingVerticalStates.end(), MovingStateUp);
        if (pos != _movingVerticalStates.end()) {
            _movingVerticalStates.erase(pos);
        }
        
    }
    
}

void HelloWorld::buttonDown(bool pressed) {
    
    if (pressed) {
        
        if (_buttonDownPressed)
            return;
        _buttonDownPressed = true;
        
        _movingVerticalStates.push_back(MovingStateDown);
        
    } else {
        
        _buttonDownPressed = false;
        
        std::vector<MovingVerticalState>::iterator pos;
        pos = std::find(_movingVerticalStates.begin(), _movingVerticalStates.end(), MovingStateDown);
        if (pos != _movingVerticalStates.end()) {
            _movingVerticalStates.erase(pos);
        }
        
    }
    
}

void HelloWorld::buttonA(bool pressed) {
    
    
    
}
