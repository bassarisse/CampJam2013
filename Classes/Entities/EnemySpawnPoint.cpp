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
    
    return true;
}

void EnemySpawnPoint::update(float dt) {
    
    _spawnTime += dt;
    
    if (_nextSpawnTime == 0) {
        _nextSpawnTime = 8 + rand() % 20;
    }
    
    if (_spawnTime > _nextSpawnTime) {
        _spawnTime = 0;
        _nextSpawnTime = 0;
        
        _gamePlay->createGameObject((GameObjectType)(GameObjectTypeMan + rand() % (GameObjectTypeManager - GameObjectTypeMan)), _properties);
        
    }
    
}