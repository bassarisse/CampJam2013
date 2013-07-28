#ifndef __CAMPJAM_TITLESCENE_H__
#define __CAMPJAM_TITLESCENE_H__

#include "../BaseLayer.h"

using namespace cocos2d;


class TitleScene : public BaseLayer
{

public:

	virtual ~TitleScene();

	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(TitleScene);

	void update(float dt);
	virtual void buttonAny(bool pressed);
	bool _creditsShown;

	LayerColor *credits;
	Menu* menu;
};

#endif // __CAMPJAM_SCENE_H__