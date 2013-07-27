//
//  BAContactListener.cpp
//  PlatformerTest
//
//  Created by Bruno Assarisse on 24/07/13.
//
//

#include "BAContactListener.h"

BAContactListener::BAContactListener() : _contacts() {
}

BAContactListener::~BAContactListener() {
}

void BAContactListener::BeginContact(b2Contact* contact) {
    // We need to copy out the data because the b2Contact passed in
    // is reused.
    BAContact aContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    _contacts.push_back(aContact);
}

void BAContactListener::EndContact(b2Contact* contact) {
    BAContact aContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    std::vector<BAContact>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), aContact);
    if (pos != _contacts.end()) {
        _contacts.erase(pos);
    }
}

void BAContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void BAContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}
