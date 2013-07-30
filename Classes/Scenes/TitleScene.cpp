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
    
	_creditsShown = false;

	Sprite* bgSprite = Sprite::create("officerampage.png");
	bgSprite->setPosition(ccp((this->getContentSize().width / 2), this->getContentSize().height / 2));

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
    
	LabelBMFont* creditsText = LabelBMFont::create("CREDITS\n \nCoding:\n Bruno Assarisse\nMurilo Clemente\n \nArt:\nCamila Christie\n \nMade in CampJam 2013\n within 48 hours :)", "MainFont.fnt", 750, kTextAlignmentCenter);
	creditsText->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));
	
	credits = LayerColor::create(ccc4(0,0,0,130));
	credits->retain();
	credits->setPosition(ccp(0,0));
	credits->setContentSize(CCSizeMake(1024, 768));
	credits->setAnchorPoint(ccp(0, 0));
	credits->setPosition(ccp(0,0));
	credits->addChild(creditsText);

	menu = Menu::create(startOpt, creditsOpt, NULL);
	menu->setPosition(ccp(this->getContentSize().width / 2, 60));
	menu->alignItemsHorizontallyWithPadding(670);

	this->addChild(bgSprite);
	this->addChild(menu);
	
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("title_bgm.mp3", true);
    
    this->setTouchEnabled(true);

	return true;
}

void TitleScene::registerWithTouchDispatcher()
{
    Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TitleScene::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    return true;
}

void TitleScene::ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    this->buttonAny(false);
}

void TitleScene::buttonAny(bool pressed) {
    
	if(pressed)
		return;
    
	if(_creditsShown)
	{
		_creditsShown = false;
		this->removeChild(credits);
		menu->setEnabled(true);
	}
	
}
