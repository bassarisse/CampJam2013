//
//  Common.h
//  CampJam
//
//  Created by Bruno Assarisse on 25/07/13.
//
//

#include "cocos2d.h"

using namespace cocos2d;

#ifndef CampJam_Common_h
#define CampJam_Common_h

#define PTM_RATIO 32.0f
#define kGravity 0
#define kWalkForce 6.0f
#define kCoffeeThreshold 60.0f
#define kCoffeeDamage 2.0f
#define kCoffeePower 0.065f
#define kCoffeeLifeDamage 2.0f
#define kCoffeeLevelAdd 15.0f
#define kPeaBerrySpeedFactor 3.2f
#define kPeaBerryTime 10.0f
#define kWaterEffectAmount 20.0f
#define kDonutEffectAmount 25.0f
#define kDamageBaseAmount 17.0f
#define kDamageTime 0.3f
#define kDamageImpulse 20.0f
#define kEnemyScore 3000.0f
#define kEnemyRandomRange 600
#define kEnemyRandomTime 5.0f
#define kEnemyDeathCoffeeNumber 3
#define kCopyScore 6000.0f

#define kWalkActionTag 500
#define kOverlayOpacity 210

#define greenLabelColor ccc3(150, 250, 150)
#define yellowLabelColor ccc3(250, 220, 100)
#define redLabelColor ccc3(240, 130, 120)

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
	GameObjectStateDead,
	GameObjectStateDying
};

enum GameObjectType {
    GameObjectTypeUnknown = 0,
    GameObjectTypePlayer,
    GameObjectTypeCoffee,
    GameObjectTypePeaBerry,
    GameObjectTypeDonut,
    GameObjectTypeWater,
	GameObjectTypeMan,
	GameObjectTypeWoman,
	GameObjectTypeManager,
	GameObjectTypePrinter,
	GameObjectTypeEmptyPaper,
	GameObjectTypeDocument,
	GameObjectTypeBossDesk
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
