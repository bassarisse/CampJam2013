#include "GamePlay.h"

#include "Entities/Player.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"
#include "Entities/Enemies/Man.h"
#include "Entities/Enemies/Woman.h"
#include "Entities/Enemies/Manager.h"
#include "Entities/Collectables/Coffee.h"
#include "Entities/Collectables/PeaBerry.h"
#include "Entities/Collectables/Water.h"
#include "Entities/Collectables/Donut.h"
#include "SimpleAudioEngine.h"
#include "Entities/EnemySpawnPoint.h"
#include "Entities/CollectableSpawnPoint.h"

USING_NS_CC;

using namespace CocosDenshion;

GamePlay::~GamePlay() {
    
    delete _contactListener;
    
    CC_SAFE_RELEASE(_player);
	CC_SAFE_RELEASE(_pauseLayer);

    for(std::vector<GameObject *>::size_type i = 0; i < _gameObjects.size(); i++) {
        
        GameObject *deadObject = _gameObjects[i];
        
        deadObject->release();
        deadObject = NULL;
    }
    
    for(std::vector<EnemySpawnPoint *>::size_type i = 0; i < _enemySpawnPoints.size(); i++) {
        _enemySpawnPoints[i]->release();
    }
    
    for(std::vector<CollectableSpawnPoint *>::size_type i = 0; i < _collectableSpawnPoints.size(); i++) {
        _collectableSpawnPoints[i]->release();
    }
    
}

Scene* GamePlay::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    GamePlay *layer = GamePlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !BaseLayer::init() )
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    srand(time(NULL));
    
    _winSize = Director::sharedDirector()->getWinSize();
    //Size visibleSize = Director::sharedDirector()->getVisibleSize();
    //Point origin = Director::sharedDirector()->getVisibleOrigin();
    
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Characters.plist");
    
    _contactListener = new BAContactListener();
    _mainLayer = Layer::create();
    _mainBatchNode = SpriteBatchNode::create("Characters.png");
    _tiledMap = TMXTiledMap::create("main.tmx");
    _isTouching = false;
    _touchLocation = ccp(0,0);
    
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
			Player* plinit = (Player*)_player;
            plinit->init(_world, objectProperties, this);
            _mainBatchNode->addChild(plinit->getNode());
            //_gameObjects.push_back(player);
		}
		else if (type->compare("EnemySpawnPoint") == 0)
        {
            EnemySpawnPoint *spawnPoint = new EnemySpawnPoint();
            spawnPoint->init(this, objectProperties);
            _enemySpawnPoints.push_back(spawnPoint);
            
        }
		else if (type->compare("CollectableSpawnPoint") == 0)
        {
            CollectableSpawnPoint *spawnPoint = new CollectableSpawnPoint();
            spawnPoint->init(this, objectProperties);
            _collectableSpawnPoints.push_back(spawnPoint);
            
        } else {
            
            GameObjectType gameObjectType = GameObjectTypeUnknown;
            
            if(type->compare("Coffee") == 0)
                gameObjectType = GameObjectTypeCoffee;
            
            else if(type->compare("Water") == 0)
                gameObjectType = GameObjectTypeWater;
            
            else if(type->compare("Donut") == 0)
                gameObjectType = GameObjectTypeDonut;
            
            else if(type->compare("PeaBerry") == 0)
                gameObjectType = GameObjectTypePeaBerry;
            
            else if(type->compare("Man") == 0)
                gameObjectType = GameObjectTypeMan;
            
            else if(type->compare("Woman") == 0)
                gameObjectType = GameObjectTypeWoman;
            
            else if(type->compare("Manager") == 0)
                gameObjectType = GameObjectTypeManager;
            
            if (gameObjectType != GameObjectTypeUnknown)
                this->createGameObject(gameObjectType, objectProperties);
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
	_scoreLayer = new ScoreLayer();

	Player* pl = (Player*)_player;

	_coffeeBar->init(pl->getCoffee());
	_coffeeBar->autorelease();
	
	_healthBar->init(pl->getLife());
	_healthBar->autorelease();

	_scoreLayer->init();
	_scoreLayer->autorelease();

	this->addChild(_scoreLayer);
	this->addChild(_coffeeBar);
	this->addChild(_healthBar);

	_pauseLayer = LayerColor::create(ccc4(0,0,0,130));
	_pauseLayer->retain();
	_pauseLayer->setPosition(ccp(0,0));
	_pauseLayer->setContentSize(CCSizeMake(1024, 768));
	LabelBMFont* pauseLabel = LabelBMFont::create("Paused!", 
		"MainFont.fnt",300,kTextAlignmentCenter);
	pauseLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	pauseLabel->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));
	_pauseLayer->addChild(pauseLabel);

	_isPaused = false;

    this->scheduleUpdate();
    
    //_debugLayer = B2DebugDrawLayer::create(_world, PTM_RATIO);
	_debugLayer = NULL;
    if (_debugLayer)
        this->addChild(_debugLayer, 9999);
    
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("main_bgm.mp3");

    return true;
}

void GamePlay::update(float dt) {
    
	if(!_isPaused)
		_world->Step(dt, 8, 3);
    
    if (_isTouching) {
        Point touchLocation = Director::sharedDirector()->convertToGL(_touchLocation);
        touchLocation = _tiledMap->convertToNodeSpace(touchLocation);
        ((Player *)_player)->followPoint(touchLocation);
    }
    
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
    
    for(std::vector<EnemySpawnPoint *>::size_type i = 0; i < _enemySpawnPoints.size(); i++) {
        _enemySpawnPoints[i]->update(dt);
    }
    
    for(std::vector<CollectableSpawnPoint *>::size_type i = 0; i < _collectableSpawnPoints.size(); i++) {
        _collectableSpawnPoints[i]->update(dt);
    }
    
	//Add the dead objects to be removed in a separated array
	for(std::vector<GameObject *>::size_type i = 0; i < _gameObjects.size(); i++) {
        GameObject *gameObj = _gameObjects[i];
		if(gameObj->getState() == GameObjectStateDead) {
			switch(gameObj->getType()) {
				case GameObjectTypeWater:
                case GameObjectTypePeaBerry:
                case GameObjectTypeCoffee:
                    SimpleAudioEngine::sharedEngine()->playEffect("drinked_coffee.wav");
                    
					break;
				case GameObjectTypeDonut:
					SimpleAudioEngine::sharedEngine()->playEffect("donut_eating.wav");
					break;
				case GameObjectTypeMan:
					SimpleAudioEngine::sharedEngine()->playEffect("death_man.wav");

					break;
				case GameObjectTypeManager:
					SimpleAudioEngine::sharedEngine()->playEffect("death_manager.wav");

					break;
				case GameObjectTypeWoman:
					SimpleAudioEngine::sharedEngine()->playEffect("death_woman.wav");

					break;
				default:
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

	_scoreLayer->setScore(pl->getScore());
	_scoreLayer->update(dt);

}

GameObject* GamePlay::createGameObject(GameObjectType type, Dictionary *properties) {
    
    switch (type) {
            
            /*
             * Collectables
             */
            
        case GameObjectTypeCoffee:
        {
            Coffee* newPowerup = new Coffee();
            newPowerup->init(_world, properties);
            _mainBatchNode->addChild(newPowerup->getNode());
            _gameObjects.push_back(newPowerup);
            return newPowerup;
        }
            break;
            
        case GameObjectTypeWater:
        {
            Water* newPowerup = new Water();
            newPowerup->init(_world, properties);
            _mainBatchNode->addChild(newPowerup->getNode());
            _gameObjects.push_back(newPowerup);
            return newPowerup;
        }
            break;
            
        case GameObjectTypeDonut:
        {
            Donut* newPowerup = new Donut();
            newPowerup->init(_world, properties);
            _mainBatchNode->addChild(newPowerup->getNode());
            _gameObjects.push_back(newPowerup);
            return newPowerup;
        }
            break;
            
        case GameObjectTypePeaBerry:
        {
            PeaBerry* newPowerup = new PeaBerry();
            newPowerup->init(_world, properties);
            _mainBatchNode->addChild(newPowerup->getNode());
            _gameObjects.push_back(newPowerup);
            return newPowerup;
        }
            break;
            
            /*
             * Enemies
             */
        case GameObjectTypeMan:
        {
            Man *newEnemy = new Man();
            newEnemy->init(_world, properties, (Player*)_player);
            _mainBatchNode->addChild(newEnemy->getNode());
            _gameObjects.push_back(newEnemy);
            return newEnemy;
        }
            break;
            
        case GameObjectTypeWoman:
        {
            Woman *newEnemy = new Woman();
            newEnemy->init(_world, properties, (Player*)_player);
            _mainBatchNode->addChild(newEnemy->getNode());
            _gameObjects.push_back(newEnemy);
            return newEnemy;
        }
            break;
            
        case GameObjectTypeManager:
        {
            Manager *newEnemy = new Manager();
            newEnemy->init(_world, properties, (Player*)_player);
            _mainBatchNode->addChild(newEnemy->getNode());
            _gameObjects.push_back(newEnemy);
            return newEnemy;
        }
            break;
            
        default:
            break;
    }
    
    return NULL;
}

void GamePlay::removeObject(GameObject* deadObject) {
    
	std::vector<GameObject *>::iterator pos;
	pos = std::find(_gameObjects.begin(), _gameObjects.end(), deadObject);
	_gameObjects.erase(pos);
    
	Node* deadNode = deadObject->getNode();
    _world->DestroyBody(deadObject->getBody());
    
	deadObject->release();
	deadNode->removeFromParentAndCleanup(true);
    deadObject = NULL;
    
}

void GamePlay::registerWithTouchDispatcher()
{
    Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GamePlay::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    _isTouching = true;
    
    this->ccTouchMoved(pTouch, pEvent);
    
    return true;
}

void GamePlay::ccTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    
    _touchLocation = pTouch->getLocationInView();
    
    Point touchLocation = Director::sharedDirector()->convertToGL(_touchLocation);
    touchLocation = _tiledMap->convertToNodeSpace(touchLocation);
    
    ((Player *)_player)->followPoint(touchLocation);
    
}

void GamePlay::ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    _isTouching = false;
    ((Player *)_player)->stopFollowingPoint();
}

void GamePlay::ccTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    _isTouching = false;
    ((Player *)_player)->stopFollowingPoint();
}

void GamePlay::buttonLeft(bool pressed) {
    
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

void GamePlay::buttonRight(bool pressed) {
    
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

void GamePlay::buttonUp(bool pressed) {
    
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

void GamePlay::buttonDown(bool pressed) {
    
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

void GamePlay::buttonA(bool pressed) {
    
}

void GamePlay::buttonB(bool pressed) {
	if(!pressed)
		return;

	if(_isPaused)
	{
		_isPaused = false;
		this->removeChild(_pauseLayer);
		this->recursivelyResumeAllChildren(this);
	} else 
	{
		_isPaused = true;
		this->addChild(_pauseLayer);
		this->recursivelyPauseAllChildren(this);
	}
}

void GamePlay::onEnter() {
	BaseLayer::onEnter();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("main_bgm.mp3", true);

}


void GamePlay::showScore(Point positionToShow, int scoreAmount) {
	LabelBMFont *deathScore = LabelBMFont::create(
					String::createWithFormat("%d", scoreAmount)->getCString(), 
					"MainFont.fnt",50,kTextAlignmentCenter);


	//deathScore->setPosition(ccp(_node->getPosition().x + (_node->getContentSize().width / 2),
	//	_node->getPosition().y + (_node->getContentSize().height + 10)));

	deathScore->setPosition(ccp(positionToShow.x, positionToShow.y));

	_mainLayer->addChild(deathScore);

	int randomNumber = (15 + (rand() % 31)) * (rand() % 2 == 0 ? 1 : -1);
	int randomHeig = (15 + (rand() % 16));

	JumpTo* scoreJump = JumpTo::create(1.0f, ccp(deathScore->getPosition().x + randomNumber,
		deathScore->getPosition().y), randomHeig, 1);

	FadeOut* fadingOut = FadeOut::create(0.7f);
	Sequence* timerFade = Sequence::create(DelayTime::create(0.4f), fadingOut, 
											CallFuncN::create(this, callfuncN_selector(GamePlay::scoreDidJump)), NULL);

	Spawn* wrap = Spawn::create(timerFade, scoreJump, NULL);

	deathScore->runAction(wrap);
}

void GamePlay::scoreDidJump(Node* scoreNode) {
	scoreNode->removeFromParentAndCleanup(true);
}