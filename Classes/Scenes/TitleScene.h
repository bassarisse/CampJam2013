#ifndef __CAMPJAM_TITLESCENE_H__
#define __CAMPJAM_TITLESCENE_H__

#include "../BaseLayer.h"

using namespace cocos2d;


class TitleScene : public BaseLayer
{
    
private:
    
	Menu *_menu;
    Menu *_highscoresMenu;

public:

	virtual ~TitleScene();

	LayerColor *credits;
	bool _creditsShown;

	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(TitleScene);
    
    virtual void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void buttonAny(bool pressed);
    
    void enableMenus(bool enabled);
    
};

#endif // __CAMPJAM_SCENE_H__