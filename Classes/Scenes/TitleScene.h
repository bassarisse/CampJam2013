#ifndef __CAMPJAM_TITLESCENE_H__
#define __CAMPJAM_TITLESCENE_H__

#include "../BaseLayer.h"

using namespace cocos2d;


class TitleScene : public BaseLayer
{

public:

	virtual ~TitleScene();

	LayerColor *credits;
	Menu* menu;
	bool _creditsShown;

	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(TitleScene);
    
    virtual void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void buttonAny(bool pressed);
    
};

#endif // __CAMPJAM_SCENE_H__