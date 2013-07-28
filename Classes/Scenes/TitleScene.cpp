#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "GamePlay.h"

USING_NS_CC;

using namespace CocosDenshion;

TitleScene::~TitleScene() {
	CC_SAFE_RELEASE(credits);
}

Scene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool TitleScene::init()  {
	
	if ( !BaseLayer::init() )
    {
        return false;
    }

	/*
	LayerGradient* bgGrad = LayerGradient::create(ccc4(255,116,0,255), 
		ccc4(255,103,15,255));
	bgGrad->setPosition(ccp(0,0));
	bgGrad->setContentSize(this->getContentSize());
	*/

	Sprite* bgSprite = Sprite::create("officerampage.jpg");
	bgSprite->setContentSize(ccp(1024,768));
	bgSprite->setPosition(ccp((this->getContentSize().width / 2) + 12,
						this->getContentSize().height / 2));

	_creditsShown = false;

	MenuItemImage* startOpt = MenuItemImage::create("gettowork.png", "gettowork.png", [](Object* obj) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
		Scene *pScene = GamePlay::scene();
	
		Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
	});
	MenuItemImage* creditsOpt = MenuItemImage::create("credits.png", "credits.png",  [this](Object* obj) {
		_creditsShown = true;
		this->addChild(credits);
		menu->setEnabled(false);
	});
	

	credits = LayerColor::create(ccc4(0,0,0,130));
	credits->retain();
	credits->setPosition(ccp(0,0));
	credits->setContentSize(CCSizeMake(1024, 768));
	
	credits->setAnchorPoint(ccp(0, 0));
	credits->setPosition(ccp(0,0));

	LabelBMFont* creditstitle = LabelBMFont::create("Credits:", 
		"MainFont.fnt",450,kTextAlignmentCenter);
	creditstitle->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height - 50));

	credits->addChild(creditstitle);

	menu = Menu::create(startOpt, creditsOpt, NULL);
	menu->setPosition(ccp(this->getContentSize().width / 2, 60));
	menu->alignItemsHorizontallyWithPadding(600);

	this->addChild(bgSprite);
	this->addChild(menu);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("title_bgm.mp3", true);

	return true;
}

void TitleScene::update(float dt) {
	
}

void TitleScene::buttonAny(bool pressed) {
	if(!pressed)
		return;
	if(_creditsShown)
	{
		_creditsShown = false;
		this->removeChild(credits);
		menu->setEnabled(true);
	}
	
}
