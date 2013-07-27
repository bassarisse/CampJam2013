//
//  Player.cpp
//  PlatformerTest
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#include "Player.h"

Player::~Player() {
    
    CC_SAFE_DELETE(_headSensor);
    CC_SAFE_DELETE(_footSensor);
    
}

void Player::addFixtures() {
    
    float width = _node->getContentSize().width * 0.75f;
    float height = _node->getContentSize().height * 0.8f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(width, height);
    
    float basicSensorWidth = (width / 4.0f * _node->getScale()) / PTM_RATIO;
    float basicSensorY = (height / 2.0f * _node->getScale()) / PTM_RATIO;
    
    //foot sensor shape
    b2PolygonShape footSensorShape;
    footSensorShape.SetAsBox(basicSensorWidth, 0.1, b2Vec2(0, -basicSensorY), 0);
    
    //foot sensor shape
    b2PolygonShape headSensorShape;
    headSensorShape.SetAsBox(basicSensorWidth, 0.1, b2Vec2(0, basicSensorY), 0);
    
    _footSensor = new SensorTypeContainer();
    _footSensor->sensorType = SensorTypeFoot;
    
    _headSensor = new SensorTypeContainer();
    _headSensor->sensorType = SensorTypeHead;
    
    this->createSensorFixture(&footSensorShape, _footSensor);
    this->createSensorFixture(&headSensorShape, _headSensor);
    
}

void Player::createSensorFixture(b2Shape *shape, SensorTypeContainer *sensorTypeContainer) {
    
    //fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1;
    
    //add foot sensor fixture
    fixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = _body->CreateFixture(&fixtureDef);
    
    footSensorFixture->SetUserData( sensorTypeContainer );
    
}

bool Player::init(b2World *world, Dictionary *properties) {
    
    _node = Sprite::createWithSpriteFrameName("right1.png");

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Player::update(float dt) {
    
    GameObject::update(dt);
    
}