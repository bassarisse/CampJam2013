#include "GameoverScene.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"

USING_NS_CC;

using namespace CocosDenshion;

GameoverScene::~GameoverScene() {
	
}

Scene* GameoverScene::scene(int score)
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    GameoverScene *layer = GameoverScene::create(score);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameoverScene::init(int score)  {
	
	if ( !BaseLayer::init() )
    {
        return false;
    }
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);

	_score = score;

	LayerGradient* bgGrad = LayerGradient::create(ccc4(255,116,0,255), 
		ccc4(255,103,15,255));
	bgGrad->setPosition(ccp(0,0));
	bgGrad->setContentSize(this->getContentSize());

	LabelBMFont *titlelabel = LabelBMFont::create("Game over, INTERN!", 
		"MainFont.fnt",400,kTextAlignmentCenter);

	
	titlelabel->setAnchorPoint(ccp(0.5,0.5));
	titlelabel->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));


	LabelBMFont *scoreLabel = LabelBMFont::create(
		String::createWithFormat("Your score: %d", _score)->getCString(),
		"MainFont.fnt",400,kTextAlignmentCenter);

	
	scoreLabel->setAnchorPoint(ccp(0.5,0.5));
	scoreLabel->setPosition(ccp(titlelabel->getPosition().x, titlelabel->getPosition().y + 200));


	this->addChild(bgGrad);
	this->addChild(titlelabel);
	this->addChild(scoreLabel);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("title_bgm.mp3", true);

	return true;
}

void GameoverScene::update(float dt) {
	
}

void GameoverScene::buttonAny(bool pressed) {
	if(pressed)
		return;

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	Scene *pScene = TitleScene::scene();
	
	Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
}