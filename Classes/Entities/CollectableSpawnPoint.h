//
//  CollectableSpawnPoint.h
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#ifndef __CampJam2013__CollectableSpawnPoint__
#define __CampJam2013__CollectableSpawnPoint__

#include "cocos2d.h"
//#include <Box2D/Box2D.h>
#include "Common.h"

class GamePlay;
class GameObject;

using namespace cocos2d;

class CollectableSpawnPoint : public Object {
    
private:
    GamePlay *_gamePlay;
    Dictionary *_properties;
    float _spawnTime;
    float _nextSpawnTime;
    float _maxObjects;
    float _spawnX;
    float _spawnY;
    
public:
    
    virtual ~CollectableSpawnPoint();
    
    bool init(GamePlay *gamePlay, Dictionary *properties);
    void update(float dt);
    
};

#endif /* defined(__CampJam2013__CollectableSpawnPoint__) */
