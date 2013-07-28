//
//  CollectableSpawnPoint.cpp
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#include "CollectableSpawnPoint.h"

#include "GamePlay.h"
#include "GameObject.h"

CollectableSpawnPoint::~CollectableSpawnPoint() {
    CC_SAFE_RELEASE(_properties);
}

bool CollectableSpawnPoint::init(GamePlay *gamePlay, Dictionary *properties) {
    
    _gamePlay = gamePlay;
    _properties = properties;
    _properties->retain();
    _spawnTime = 0;
    _nextSpawnTime = 1 + rand() % 10;
    _maxObjects = 1;
    
    return true;
}

void CollectableSpawnPoint::update(float dt) {
    
    for (std::vector<GameObject *>::size_type i; i < _gameObjects.size(); i++) {
        GameObject *gameObject = _gameObjects[i];
        if (gameObject->getState() == GameObjectStateDead) {
            std::vector<GameObject *>::iterator pos;
            pos = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
            _gameObjects.erase(pos);
        }
    }
    
    _spawnTime += dt;
    
    if (_nextSpawnTime == 0) {
        _nextSpawnTime = 8 + rand() % 20;
    }
    
    if (_spawnTime > _nextSpawnTime) {
        _spawnTime = 0;
        _nextSpawnTime = 0;
        
        if (_gameObjects.size() >= _maxObjects)
            return;
        
        GameObject *newObj = _gamePlay->createGameObject((GameObjectType)(GameObjectTypeCoffee + rand() % (1 + GameObjectTypeWater - GameObjectTypeCoffee)), _properties);
        _gameObjects.push_back(newObj);
        
    }
    
}
