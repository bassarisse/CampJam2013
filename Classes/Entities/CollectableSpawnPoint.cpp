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
        _nextSpawnTime = 10 + rand() % 25;
    
    if (_spawnTime > _nextSpawnTime) {
        _spawnTime = 0;
        _nextSpawnTime = 0;
        
        if ((int)_gameObjects.size() >= _maxObjects)
            return;
        
		int dice = rand() % 10;

		GameObjectType spawnType = GameObjectTypeCoffee;

		if(dice <= 6) {
			spawnType = GameObjectTypeCoffee;
		} else if(dice > 6 && dice <= 7 ) {
			spawnType = GameObjectTypeWater;
		} else if(dice > 7 && dice <= 8) {
			spawnType = GameObjectTypePeaBerry;
		} else if(dice > 8 && dice <= 9) {
			spawnType = GameObjectTypeDonut;
		}


        GameObject *newObj = _gamePlay->createGameObject(spawnType, _properties);
        _gameObjects.push_back(newObj);
        
    }
    
}
