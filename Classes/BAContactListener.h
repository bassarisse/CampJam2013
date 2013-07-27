//
//  BAContactListener.h
//  PlatformerTest
//
//  Created by Bruno Assarisse on 24/07/13.
//
//

#ifndef __PlatformerTest__BAContactListener__
#define __PlatformerTest__BAContactListener__

#import "Box2D.h"
#import <vector>
#import <algorithm>

struct BAContact {
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    bool operator==(const BAContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
    };
    
    class BAContactListener : public b2ContactListener {
        
    public:
        std::vector<BAContact> _contacts;
        
        BAContactListener();
        ~BAContactListener();
        
        virtual void BeginContact(b2Contact* contact);
        virtual void EndContact(b2Contact* contact);
        virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        
    };
    
#endif /* defined(__PlatformerTest__BAContactListener__) */
