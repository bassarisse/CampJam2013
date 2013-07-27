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
#define kCoffeeThreshold 60.0f
#define kCoffeeDamage 1.5f
#define kCoffeePower 0.08f

#define kWalkActionTag 500

enum kDirection {
    kDirectionUp = 0,
    kDirectionDown,
    kDirectionLeft,
    kDirectionRight
};

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
    GameObjectStateStanding = 0,
    GameObjectStateWalking,
    GameObjectStateTakingDamage,
    GameObjectStateAfterDamage,
};

enum GameObjectType {
    GameObjectTypePlayer = 0,
    GameObjectTypeCoffee,
    GameObjectTypePeaBerry,
    GameObjectTypeDonut,
    GameObjectTypeWater,
	GameObjectTypeMan
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


inline const char* getDirectionName(kDirection direction) {
    switch (direction) {
        case kDirectionUp: return "up"; break;
        case kDirectionLeft: return "left"; break;
        case kDirectionRight: return "right"; break;
        default: return "down"; break;
    }
}

#endif
