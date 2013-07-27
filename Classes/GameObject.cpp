//
//  GameObject.cpp
//  PlatformerTest
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#include "GameObject.h"
#include "BAContactListener.h"

GameObject::GameObject() {
    
}

GameObject::~GameObject() {
    
}

void GameObject::setProperties(Dictionary* properties)
{
    if (properties) {
        
        float x = floatValue(properties->objectForKey("x"));
        float y = floatValue(properties->objectForKey("y"));
        float halfwidth = floatValue(properties->objectForKey("width")) / 2.0f;
        float halfheight = floatValue(properties->objectForKey("height")) / 2.0f;
        
        x += halfwidth;
        y += halfheight;
        
        _node->setPosition(ccp(x, y));
    }
}

void GameObject::addCircularFixture(float radius) {
    
    b2CircleShape shape;
    shape.m_radius = radius * _node->getScale() / PTM_RATIO;
    this->createFixture(&shape);
    
}

void GameObject::addRectangularFixture(float width, float height) {
    
    b2PolygonShape shape;
    shape.SetAsBox(width / 2.0f * _node->getScale() / PTM_RATIO, height / 2.0f * _node->getScale() / PTM_RATIO);
    this->createFixture(&shape);
    
}

void GameObject::createFixture(b2Shape *shape) {
    
    // some properties can be modified later by iterating on body's fixtures (e.g. fixture->SetFriction())
    
    b2FixtureDef fixtureDef;
    
    fixtureDef.shape = shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.filter.categoryBits = kFilterCategorySolidObject;
    fixtureDef.filter.maskBits = 0xffff;
    
    _body->CreateFixture(&fixtureDef);
    
}

void GameObject::addFixtures() {
    
}

bool GameObject::canJump() {
    
    if (_jumpTime > 0)
        return false;
    
    for(std::vector<BAContact>::size_type i = 0; i != contactListener->_contacts.size(); i++) {
        BAContact aContact = contactListener->_contacts[i];
        
        SensorTypeContainer *fixtureAUserData = (SensorTypeContainer *)aContact.fixtureA->GetUserData();
        SensorTypeContainer *fixtureBUserData = (SensorTypeContainer *)aContact.fixtureB->GetUserData();
        
        if ((fixtureAUserData && fixtureAUserData->sensorType == SensorTypeFoot && !aContact.fixtureB->GetBody()->GetUserData()) ||
            (fixtureBUserData && fixtureBUserData->sensorType == SensorTypeFoot && !aContact.fixtureA->GetBody()->GetUserData()))
            return true;
        
    }
    
    return false;
}

bool GameObject::isHittingHead() {
    
    for(std::vector<BAContact>::size_type i = 0; i != contactListener->_contacts.size(); i++) {
        BAContact aContact = contactListener->_contacts[i];
        
        SensorTypeContainer *fixtureAUserData = (SensorTypeContainer *)aContact.fixtureA->GetUserData();
        SensorTypeContainer *fixtureBUserData = (SensorTypeContainer *)aContact.fixtureB->GetUserData();
        
        if ((fixtureAUserData && fixtureAUserData->sensorType == SensorTypeHead && !aContact.fixtureB->GetBody()->GetUserData()) ||
            (fixtureBUserData && fixtureBUserData->sensorType == SensorTypeHead && !aContact.fixtureA->GetBody()->GetUserData()))
            return true;
        
    }
    
    return false;
}

Node* GameObject::getNode() {
    return _node;
}

void GameObject::addBodyToWorld(b2World *world) {
    
    b2BodyDef bodyDef;
    
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(_node->getPositionX() / PTM_RATIO, _node->getPositionY() / PTM_RATIO);
    bodyDef.userData = this;
    bodyDef.fixedRotation = true;
    
    _body = world->CreateBody(&bodyDef);
    
}

bool GameObject::init(b2World *world, Dictionary *properties) {
    
    _jumpTime = 0;
    
    this->setMovingState(MovingStateStopped);
    this->setProperties(properties);
    this->addBodyToWorld(world);
    this->addFixtures();
    
    return true;
}

void GameObject::update(float dt) {
    
    if (_jumpTime > 0) _jumpTime -= dt;
    else if (_jumpTime < 0) _jumpTime = 0;
    
    b2Vec2 position = _body->GetPosition();
    
    _node->setPosition(position.x * PTM_RATIO, position.y * PTM_RATIO);
    
    b2Vec2 vel = _body->GetLinearVelocity();
    
    if (this->getState() == GameObjectStateStanding && this->getMovingState() == MovingStateStopped && this->canJump())
        _body->SetGravityScale(0.0f);
    else
        _body->SetGravityScale(1.0f);
    
    float desiredXVel = 0;
    float desiredYVel = 0;
    
    switch (this->getMovingState())
    {
        case MovingStateLeft:     desiredXVel = b2Max( vel.x - (kWalkForce/3.0f), -kWalkForce ); break;
        case MovingStateStopped:  desiredXVel = vel.x * 0.75f; desiredYVel = vel.y * 0.75f; break;
        case MovingStateRight:    desiredXVel = b2Min( vel.x + (kWalkForce/3.0f),  kWalkForce ); break;
    }
    
    float xVelChange = desiredXVel - vel.x;
    float yVelChange = desiredYVel > 0 ? desiredYVel - vel.y : 0;
    float xImpulse = _body->GetMass() * xVelChange;
    float yImpulse = _body->GetMass() * yVelChange;
    
    _body->ApplyLinearImpulse( b2Vec2(xImpulse, yImpulse), _body->GetWorldCenter() );
    
    if (this->getState() == GameObjectStateJumpStarting) {
        
        if (this->isHittingHead()) {
            _jumpTime = 0;
            
            float yImpulse = _body->GetMass();
            _body->ApplyLinearImpulse( b2Vec2(0, -yImpulse), _body->GetWorldCenter() );
        }
        
        if (_jumpTime > 0) {
            
            b2Vec2 vel = _body->GetLinearVelocity();
            float desiredYVel = kJumpForce;
            
            float yVelChange = desiredYVel - vel.y;
            float yImpulse = _body->GetMass() * yVelChange;
            
            _body->ApplyLinearImpulse( b2Vec2(0, yImpulse), _body->GetWorldCenter() );
            
        } else {
            this->setState(GameObjectStateJumping);
        }
        
    }
    
    if (this->getState() == GameObjectStateJumping && _jumpTime == 0 && this->canJump()) {
        
        this->setState(GameObjectStateStanding);
        
    }
    
}

void GameObject::jump() {
    
    if (this->getState() != GameObjectStateStanding)
        return;
     
    if (this->canJump()) {
        this->setState(GameObjectStateJumpStarting);
        
        _jumpTime = 0.2f;
        float impulse = _body->GetMass() * kJumpForce;
        _body->ApplyLinearImpulse( b2Vec2(0,impulse), _body->GetWorldCenter() );
        
    }
    
}

void GameObject::finishJump() {
    
    if (this->getState() != GameObjectStateJumpStarting)
        return;
    this->setState(GameObjectStateJumping);
    
}