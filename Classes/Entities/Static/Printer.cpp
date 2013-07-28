//
//  Printer.cpp
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#include "Printer.h"

bool Printer::init(b2World *world, Dictionary *properties) {
	
	this->setType(GameObjectTypePrinter);
    
    if (!GameObject::init(world, properties, false, false))
        return false;
    
    return true;
}