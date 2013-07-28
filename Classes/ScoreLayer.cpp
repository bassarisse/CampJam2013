#include "ScoreLayer.h"

ScoreLayer::~ScoreLayer() {
}

bool ScoreLayer::init() {
	if ( !Layer::init() )
    {
        return false;
    }

	_score = 0;
	

	_scoreLabel = LabelBMFont::create(
		String::createWithFormat("%d", _score)->getCString(), 
		"MainFont.fnt",300,kTextAlignmentRight);

	
	_scoreLabel->setAnchorPoint(ccp(1,1));

	_scoreLabel->setPosition(ccp(1014,758));


	this->addChild(_scoreLabel);
	
	return true;
}


void ScoreLayer::setScore(int score) {
	_score = score;
}

void ScoreLayer::update(float dt) {
	_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
}