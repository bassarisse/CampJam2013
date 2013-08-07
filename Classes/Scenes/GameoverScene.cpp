#include "GameoverScene.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "GamePlay.h"

#include "GameJolt.h"
#include "HighscoresLayer.h"

USING_NS_CC;

using namespace CocosDenshion;

Scene* GameoverScene::scene(int score, bool isRecord)
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    GameoverScene *layer = GameoverScene::create(score, isRecord);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameoverScene::init(int score, bool isRecord)  {
	
	if ( !BaseLayer::init() )
    {
        return false;
    }
    
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);

	_score = score;
    
    GameJolt::getInstance()->addScore(score);
    
	auto bgSprite = Sprite::create("gameover.jpg");
	bgSprite->setPosition(ccp(this->getContentSize().width / 2,
                              this->getContentSize().height / 2));

	auto scoreLabel = LabelBMFont::create(
		String::createWithFormat("Your score: %d", _score)->getCString(), "MainFont.fnt", 600, kTextAlignmentLeft);

	scoreLabel->setAnchorPoint(ccp(0.0, 1.0));
	scoreLabel->setPosition(ccp(10, this->getContentSize().height - 10));
 
	auto startOpt = MenuItemImage::create("startover.png", "startover.png", [](Object* obj) {
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
		Scene *pScene = GamePlay::scene();
	
		Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
	});

	auto returnOpt = MenuItemImage::create("return.png", "return.png", [](Object* obj) {
		Scene *pScene = TitleScene::scene();
	
		Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
	});

	_menu = Menu::create(startOpt, returnOpt, NULL);
	_menu->setPosition(ccp(this->getContentSize().width - 170, this->getContentSize().height * 0.22f));
	_menu->alignItemsVertically();
    
    auto highscoresLabel = LabelBMFont::create("Highscores", "MiniFont.fnt", 100, kTextAlignmentCenter);
    highscoresLabel->setColor(yellowLabelColor);
    
    auto highscoresMenuItem = MenuItemLabel::create(highscoresLabel, [this](Object *object) {
        
        this->enableMenus(false);
        
        auto highscoreLayer = new HighscoresLayer();
        highscoreLayer->init([this]() {
            this->enableMenus(true);
        });
        this->addChild(highscoreLayer);
        highscoreLayer->release();
        
    });
    
    _highscoresMenu = Menu::create(highscoresMenuItem, NULL);
    _highscoresMenu->setPosition(ccp(this->getContentSize().width - 130, this->getContentSize().height - 40));
    
	this->addChild(bgSprite);
	this->addChild(scoreLabel);
	this->addChild(_menu);
    this->addChild(_highscoresMenu);
    
    if (isRecord) {
        
        auto recordLabel = LabelBMFont::create("New record!\nNow get back to work!", "MiniFont.fnt", 600, kTextAlignmentLeft);
        recordLabel->setAnchorPoint(ccp(0.0, 1.0));
        recordLabel->setPosition(ccp(12, this->getContentSize().height - 75));
        //recordLabel->setColor(ccc3(255, 255, 150));
        
        this->addChild(recordLabel);
        
    }
    
	return true;
}

void GameoverScene::enableMenus(bool enabled) {
    
    _menu->setEnabled(enabled);
    _highscoresMenu->setEnabled(enabled);
    
}