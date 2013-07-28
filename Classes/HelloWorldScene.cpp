#include "HelloWorldScene.h"

#include "Entities/Player.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"
#include "Entities/Man.h"
#include "Entities/Woman.h"
#include "Entities/Manager.h"
#include "Entities/Coffee.h"
#include "Entities/PeaBerry.h"
#include "Entities/Water.h"
#include "Entities/Donut.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


USING_NS_CC;

HelloWorld::~HelloWorld() {
    
    delete _contactListener;
    
    CC_SAFE_DELETE(_player);
    
    for(std::vector<GameObject *>::size_type i = 0; i < _gameObjects.size(); i++) {
        this->removeObject(_gameObjects[i]);
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
    
    
    GLProgram *alphaTestShader = ShaderCache::sharedShaderCache()->programForKey(kShader_PositionTextureColorAlphaTest);
    
    GLint alphaValueLocation = glGetUniformLocation(alphaTestShader->getProgram(), kUniformAlphaTestValue);
    
    // set alpha test value
    // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
    if (getShaderProgram())
    {
        getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, 1.0f);
    }
    
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Characters.plist");
    
    _contactListener = new BAContactListener();
    _mainLayer = Layer::create();
    _mainBatchNode = SpriteBatchNode::create("Characters.png");
    _tiledMap = TMXTiledMap::create("main.tmx");
    
    _mainBatchNode->getTexture()->setAliasTexParameters();
    _mainBatchNode->setShaderProgram(alphaTestShader);
    
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
	//Allocating object here so that we can pass its reference to all enemies.
	//Actual initialization occurs when it's TMX entity is found below
	_player = new Player();

    CCARRAY_FOREACH(gameObjects, gameObject) {
        Dictionary *objectProperties = (Dictionary *)gameObject;
        
        String *type = (String *)objectProperties->objectForKey("type");
        if (!type)
            continue;
        
        if (type->compare("Player") == 0) 
		{
            
            _player->init(_world, objectProperties);
            _mainBatchNode->addChild(_player->getNode());
            //_gameObjects.push_back(player); 
		} 
		/* 
		 * Powerups
		 */
		else if(type->compare("Coffee") == 0) 
		{
			Coffee* newPowerup = new Coffee();
			newPowerup->init(_world, objectProperties);
			_mainBatchNode->addChild(newPowerup->getNode());
			_gameObjects.push_back(newPowerup);

		} else if(type->compare("Water") == 0) 
		{
			Water* newPowerup = new Water();
			newPowerup->init(_world, objectProperties);
			_mainBatchNode->addChild(newPowerup->getNode());
			_gameObjects.push_back(newPowerup);
            
		} else if(type->compare("Donut") == 0) 
		{
			Donut* newPowerup = new Donut();
			newPowerup->init(_world, objectProperties);
			_mainBatchNode->addChild(newPowerup->getNode());
			_gameObjects.push_back(newPowerup);
            
		} else if(type->compare("PeaBerry") == 0) 
		{
			PeaBerry* newPowerup = new PeaBerry();
			newPowerup->init(_world, objectProperties);
			_mainBatchNode->addChild(newPowerup->getNode());
			_gameObjects.push_back(newPowerup);
            
		} 
		/* 
		 * Enemies
		 */
		else if(type->compare("Man") == 0)
		{
			Man *newEnemy = new Man();
			newEnemy->init(_world, objectProperties, (Player*)_player);
			_mainBatchNode->addChild(newEnemy->getNode());
			_gameObjects.push_back(newEnemy);
		}
		else if(type->compare("Woman") == 0)
		{
			Woman *newEnemy = new Woman();
			newEnemy->init(_world, objectProperties, (Player*)_player);
			_mainBatchNode->addChild(newEnemy->getNode());
			_gameObjects.push_back(newEnemy);
		}
		else if(type->compare("Manager") == 0)
		{
			Manager *newEnemy = new Manager();
			newEnemy->init(_world, objectProperties, (Player*)_player);
			_mainBatchNode->addChild(newEnemy->getNode());
			_gameObjects.push_back(newEnemy);
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
    
	_coffeeBar = new CoffeeBar();
	_healthBar = new HealthBar();
	Player* pl = (Player*)_player;

	_coffeeBar->init(pl->getCoffee());
	_coffeeBar->autorelease();

	_healthBar->init(pl->getLife());
	_healthBar->autorelease();

	this->addChild(_coffeeBar);
	this->addChild(_healthBar);

    this->scheduleUpdate();
    
    //_debugLayer = B2DebugDrawLayer::create(_world, PTM_RATIO);
	_debugLayer = NULL;
    if (_debugLayer)
        this->addChild(_debugLayer, 9999);
    
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("main_bgm.mp3", true);

	

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
    
    if (_debugLayer)
        _debugLayer->setPosition(viewPoint);

    for(std::vector<GameObject *>::size_type i = 0; i < _gameObjects.size(); i++) {
        _gameObjects[i]->update(dt);
    }
    
	//Add the dead objects to be removed in a separated array
	for(std::vector<GameObject *>::size_type i = 0; i < _gameObjects.size(); i++) {
        GameObject *gameObj = _gameObjects[i];
		if(gameObj->getState() == GameObjectStateDead) {
			switch(gameObj->getType()) {
			case GameObjectTypeCoffee:
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("drinked_coffee.wav");
				break;
			}

            this->removeObject(gameObj);
		}
    }



	Player* pl = (Player*)_player;
	_coffeeBar->setCoffeeLevel(pl->getCoffee());
	_coffeeBar->update(dt);

	_healthBar->setHealthLevel(pl->getLife());
	_healthBar->update(dt);

}

void HelloWorld::removeObject(GameObject* deadObject) {
    
	std::vector<GameObject *>::iterator pos;
	pos = std::find(_gameObjects.begin(), _gameObjects.end(), deadObject);
	_gameObjects.erase(pos);
    
	Node* deadNode = deadObject->getNode();
	_world->DestroyBody(deadObject->getBody());
    
	deadObject->release();
	deadNode->removeFromParentAndCleanup(true);
    deadObject = NULL;
    
}

void HelloWorld::buttonLeft(bool pressed) {
    
    if (pressed) {
        
        if (_buttonLeftPressed)
            return;
        _buttonLeftPressed = true;
        
        _movingHorizontalStates.push_back(MovingStateLeft);
        _player->changeDirection(kDirectionLeft);
        
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
        _player->changeDirection(kDirectionRight);
        
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
        _player->changeDirection(kDirectionUp);
        
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
        _player->changeDirection(kDirectionDown);
        
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
