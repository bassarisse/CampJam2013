//
//  Common.h
//  PlatformerTest
//
//  Created by Bruno Assarisse on 25/07/13.
//
//

#include "cocos2d.h"

using namespace cocos2d;

#ifndef PlatformerTest_Common_h
#define PlatformerTest_Common_h

#define PTM_RATIO 32.0f
#define kGravity 0

#define kWalkForce 3.0f

enum MovingHorizontalState {
    MovingStateHorizontalStopped = 0,
    MovingStateLeft,
    MovingStateRight
};

enum MovingVerticalState {
    MovingStateVerticalStopped = 0,
    MovingStateUp,
    MovingStateDown
};

enum GameObjectState {
    GameObjectStateStanding = 0
};

enum GameObjectType {
    GameObjectTypePlayer = 0,
    GameObjectTypeCoffee,
    GameObjectTypePeaBerry,
    GameObjectTypeDonut,
    GameObjectTypeWater
};

enum SensorType {
    SensorTypeUnknown = 0
};

inline float floatValue(Object* o)
{
    String* string = dynamic_cast<String*>(o);
    if (string)
        return string->floatValue();
    return 0.0f;
}

#endif
