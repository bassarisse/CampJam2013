//
//  GameObject.cpp
//  PlatformerTest
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#include "GameObject.h"

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

void GameObject::addRectangularFixture(float x, float y, float width, float height) {
    
    b2PolygonShape shape;
    shape.SetAsBox(width / 2.0f * _node->getScale() / PTM_RATIO,
                   height / 2.0f * _node->getScale() / PTM_RATIO,
                   b2Vec2(x * _node->getScale() / PTM_RATIO, y * _node->getScale() / PTM_RATIO),
                   0);
    this->createFixture(&shape);
    
}

void GameObject::createFixture(b2Shape *shape) {
    
    // some properties can be modified later by iterating on body's fixtures (e.g. fixture->SetFriction())
    
    b2FixtureDef fixtureDef;
    
    fixtureDef.shape = shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.userData = this;
    
    _body->CreateFixture(&fixtureDef);
    
}

void GameObject::addFixtures() {
    
}

void GameObject::createSensorFixture(b2Shape *shape, SensorTypeContainer *sensorTypeContainer) {
    
    //fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1;
    fixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = _body->CreateFixture(&fixtureDef);
    
    footSensorFixture->SetUserData( sensorTypeContainer );
    
}

float GameObject::getSpeed() {
    return _speedFactor;
}

void GameObject::handleCollisions() {
    
}

Node* GameObject::getNode() {
    return _node;
}

void GameObject::addContact(GameObject *contact) {
    _contacts.push_back(contact);
}

void GameObject::removeContact(GameObject *contact) {
    
    std::vector<GameObject *>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), contact);
    if (pos != _contacts.end()) {
        _contacts.erase(pos);
    }
    
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
    
    _speedFactor = 0.0f;
    _lastDirection = kDirectionDown;
    _lastVerticalDirection = kDirectionDown;
    _lastHorizontalDirection = kDirectionRight;
    
    this->setMovingVerticalState(MovingStateVerticalStopped);
    this->setMovingHorizontalState(MovingStateHorizontalStopped);
    this->setProperties(properties);
    this->addBodyToWorld(world);
    this->addFixtures();
    
    return true;
}

void GameObject::update(float dt) {
    
    b2Vec2 position = _body->GetPosition();
    
    int x = position.x * PTM_RATIO;
    int y = position.y * PTM_RATIO;
    
    _node->setPosition(x, y);
    _node->getParent()->reorderChild(_node, - 10 - y);
    //_node->setVertexZ(- 10 - y);
    
    this->handleMovement();
        
}

void GameObject::handleMovement() {
    
    float angle = 0;
    
    switch (this->getMovingHorizontalState())
    {
        case MovingStateLeft:
            switch (this->getMovingVerticalState())
        {
            case MovingStateDown: angle = 225; break;
            case MovingStateVerticalStopped: angle = 180; break;
            case MovingStateUp: angle = 135; break;
        }
            break;
        case MovingStateHorizontalStopped:
            switch (this->getMovingVerticalState())
        {
            case MovingStateDown: angle = 270; break;
            case MovingStateVerticalStopped: angle = -1; break;
            case MovingStateUp: angle = 90; break;
        }
            break;
        case MovingStateRight:
            switch (this->getMovingVerticalState())
        {
            case MovingStateDown: angle = 315; break;
            case MovingStateVerticalStopped: angle = 0; break;
            case MovingStateUp: angle = 45; break;
        }
            break;
    }
    
    this->handleMovement(angle);
    
}

void GameObject::handleMovement(float angle) {
    
    this->setState(this->getMovingHorizontalState() == MovingStateHorizontalStopped && this->getMovingVerticalState() == MovingStateVerticalStopped ? GameObjectStateStanding : GameObjectStateWalking);
    
    float x = (kWalkForce + this->getSpeed()) * cos(angle * M_PI / 180.0f);
    float y = (kWalkForce + this->getSpeed()) * sin(angle * M_PI / 180.0f);
    
    float desiredXVel = 0;
    float desiredYVel = 0;
    
    b2Vec2 vel = _body->GetLinearVelocity();
    
    switch (this->getMovingHorizontalState())
    {
        case MovingStateLeft:     desiredXVel = b2Max( vel.x - (abs(x)/3.0f), x); break;
        case MovingStateHorizontalStopped:  desiredXVel = vel.x * 0.75f; break;
        case MovingStateRight:    desiredXVel = b2Min( vel.x + (abs(x)/3.0f), x); break;
    }
    
    switch (this->getMovingVerticalState())
    {
        case MovingStateDown:     desiredYVel = b2Max( vel.y - (abs(y)/3.0f), y); break;
        case MovingStateVerticalStopped:  desiredYVel = vel.y * 0.75f; break;
        case MovingStateUp:    desiredYVel = b2Min( vel.y + (abs(y)/3.0f), y); break;
    }
    
    float xVelChange = desiredXVel - vel.x;
    float yVelChange = desiredYVel - vel.y;
    float xImpulse = _body->GetMass() * xVelChange;
    float yImpulse = _body->GetMass() * yVelChange;
    
    _body->ApplyLinearImpulse( b2Vec2(xImpulse, yImpulse), _body->GetWorldCenter() );
    
}

bool GameObject::changeDirection(kDirection direction) {
    
    if (_lastDirection == direction)
        return false;
    
    _lastDirection = direction;
    
    if (direction == kDirectionUp || direction == kDirectionDown)
        _lastVerticalDirection = direction;
    if (direction == kDirectionLeft || direction == kDirectionRight)
        _lastHorizontalDirection = direction;
    
    if (_node->getActionByTag(kWalkActionTag))
        _node->stopActionByTag(kWalkActionTag);
    
    return true;
}
