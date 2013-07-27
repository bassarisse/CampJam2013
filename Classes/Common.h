//
//  Common.h
//  PlatformerTest
//
//  Created by Bruno Assarisse on 25/07/13.
//
//

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

#endif
