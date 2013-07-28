#include "GameoverScene.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "GamePlay.h"

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

	Sprite* bgSprite = Sprite::create("gameover.jpg");
	bgSprite->setContentSize(ccp(1024,768));
	bgSprite->setPosition(ccp((this->getContentSize().width / 2) ,
						this->getContentSize().height / 2));


	

	LabelBMFont *scoreLabel = LabelBMFont::create(
		String::createWithFormat("Your score: %d", _score)->getCString(),
		"MainFont.fnt",400,kTextAlignmentCenter);

	
	scoreLabel->setAnchorPoint(ccp(0.5,0.5));
	scoreLabel->setPosition(ccp(180, this->getContentSize().height - 200));



	
	MenuItemLabel* item1;
	MenuItemLabel* item2;
	
	LabelBMFont *retryLabel = LabelBMFont::create(
		"Try again",
		"MainFont.fnt",400,kTextAlignmentCenter);

	LabelBMFont *titleLabel = LabelBMFont::create(
		"Title screen",
		"MainFont.fnt",400,kTextAlignmentCenter);

 
	item2 = MenuItemLabel::create(titleLabel, this,
									menu_selector(GameoverScene::clickedTitle));
 

	MenuItemImage* startOpt = MenuItemImage::create("startover.png", "startover.png", [](Object* obj) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
		Scene *pScene = GamePlay::scene();
	
		Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
	});

	Menu* menu = Menu::create(startOpt, item2, NULL);
	menu->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height - 80));
	menu->alignItemsHorizontallyWithPadding(380);

	
	this->addChild(bgSprite);
	this->addChild(scoreLabel);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("title_bgm.mp3", true);
	this->addChild(menu);
	return true;
}

void GameoverScene::clickedRetry(Object* sender) {
	Scene *pScene = GamePlay::scene();
	
	Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
}

void GameoverScene::clickedTitle(Object* sender) {
	Scene *pScene = TitleScene::scene();
	
	Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
}

void GameoverScene::update(float dt) {
	
}
/*
void GameoverScene::buttonAny(bool pressed) {
	if(pressed)
		return;

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	Scene *pScene = TitleScene::scene();
	
	Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
}*/