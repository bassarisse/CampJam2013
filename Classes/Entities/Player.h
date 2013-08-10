//
//  Player.h
//  CampJam
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#ifndef __CampJam__Player__
#define __CampJam__Player__

#include "GameObject.h"

class GamePlay;

class Player : public GameObject {
    
private:
        
protected:
    
    bool _isFollowingPoint;
    Point _pointToFollow;
    bool _isUnderPeaBerryEffect;
    float _peaBerryTime;
    float _damageTime;
    
    virtual void addFixtures();
    virtual float getSpeed();
	virtual void handleCollision(GameObject *gameObject);
	virtual void handleMovement();
	virtual void handleMovement(float angle);
    
public:
    
    virtual ~Player();
    
    virtual bool init(b2World *world, Dictionary *properties, GamePlay* gameScreen);
    virtual void update(float dt);
    virtual void followPoint(Point point);
    virtual void stopFollowingPoint();
    
	//GamePlay* _gameScreen;
	CC_SYNTHESIZE(GamePlay*, _gameScreen, GameScreen);

	CC_SYNTHESIZE(float, _score, Score);
	CC_SYNTHESIZE(float, _coffee, Coffee);
	CC_SYNTHESIZE(float, _life, Life);
    
	CC_SYNTHESIZE(bool, _hasEmptyPaper, HasEmptyPaper);
	CC_SYNTHESIZE(bool, _hasDocument, HasDocument);
	CC_SYNTHESIZE(int, _copiesQty, CopiesQty);

};

#endif /* defined(__CampJam__Player__) */
