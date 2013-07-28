#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "GamePlay.h"

USING_NS_CC;

using namespace CocosDenshion;

TitleScene::~TitleScene() {
	
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

	LayerGradient* bgGrad = LayerGradient::create(ccc4(255,116,0,255), 
		ccc4(255,103,15,255));
	bgGrad->setPosition(ccp(0,0));
	bgGrad->setContentSize(this->getContentSize());

	LabelBMFont *titlelabel = LabelBMFont::create("Press any button!", 
		"MainFont.fnt",400,kTextAlignmentCenter);

	
	titlelabel->setAnchorPoint(ccp(0.5,0.5));
	titlelabel->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));

	this->addChild(bgGrad);
	this->addChild(titlelabel);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("title_bgm.mp3", true);

}

void TitleScene::update(float dt) {
	
}

void TitleScene::buttonAny(bool pressed) {
	if(pressed)
		return;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	Scene *pScene = GamePlay::scene();
	
	Director::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
}