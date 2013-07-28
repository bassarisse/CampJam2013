//
//  EnemySpawnPoint.cpp
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#include "EnemySpawnPoint.h"

#include "GamePlay.h"
#include "GameObject.h"

EnemySpawnPoint::~EnemySpawnPoint() {
    CC_SAFE_RELEASE(_properties);
}

bool EnemySpawnPoint::init(GamePlay *gamePlay, Dictionary *properties) {
    
    _gamePlay = gamePlay;
    _properties = properties;
    _properties->retain();
    _spawnTime = 0;
    _nextSpawnTime = 1 + rand() % 10;
    _maxObjects = 5;
    
    String *maxObjects = (String *)properties->objectForKey("MaxObjects");
    if (maxObjects)
        _maxObjects = maxObjects->intValue();
    
    return true;
}

void EnemySpawnPoint::update(float dt) {
    
    for (std::vector<GameObject *>::size_type i = 0; i < _gameObjects.size(); i++) {
        GameObject *gameObject = _gameObjects[i];
        if (gameObject->getState() == GameObjectStateDead) {
            std::vector<GameObject *>::iterator pos;
            pos = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
            _gameObjects.erase(pos);
        }
    }
    
    _spawnTime += dt;
    
    if (_nextSpawnTime == 0)
        _nextSpawnTime = 8 + rand() % 20;
    
    if (_spawnTime > _nextSpawnTime) {
        _spawnTime = 0;
        _nextSpawnTime = 0;
        
        if ((int)_gameObjects.size() >= _maxObjects)
            return;
        
        GameObject *newObj = _gamePlay->createGameObject((GameObjectType)(GameObjectTypeMan + rand() % (1 + GameObjectTypeManager - GameObjectTypeMan)), _properties);
        _gameObjects.push_back(newObj);
        
    }
    
}