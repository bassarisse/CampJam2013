//
//  Document.cpp
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#include "Document.h"

bool Document::init(b2World *world, Dictionary *properties) {
	
	this->setType(GameObjectTypeDocument);
    
    if (!GameObject::init(world, properties, false, false))
        return false;
    
    return true;
}
