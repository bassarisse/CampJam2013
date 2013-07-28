//
//  BossDesk.cpp
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#include "BossDesk.h"

bool BossDesk::init(b2World *world, Dictionary *properties) {
	
	this->setType(GameObjectTypeBossDesk);
    
    if (!GameObject::init(world, properties, false, false))
        return false;
    
    return true;
}
