
#include "Enemy.h"

Enemy::~Enemy() {
    
}

void Enemy::addFixtures() {
    
    float width = _node->getContentSize().width * 0.75f;
    float height = _node->getContentSize().height * 0.8f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(width, height);
    
}

void Enemy::createSensorFixture(b2Shape *shape, SensorTypeContainer *sensorTypeContainer) {
    
    //fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1;
    
    //add foot sensor fixture
    fixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = _body->CreateFixture(&fixtureDef);
    
    footSensorFixture->SetUserData( sensorTypeContainer );
    
}

bool Enemy::init(b2World *world, Dictionary *properties) {
    
    //_node = Sprite::createWithSpriteFrameName("right1.png");

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Enemy::update(float dt) {
    
    GameObject::update(dt);
    
}