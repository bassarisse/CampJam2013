
#ifndef __CampJam__HealthBar__
#define __CampJam__HealthBar__

#include "cocos2d.h"

using namespace cocos2d;

class HealthBar : public Layer
{
public:
    
    virtual bool init(float healthLevel);
            
	float _healthLevel;
	void setHealthLevel(float health);

	virtual void update(float dt);

	LayerColor* _bar;
	Sprite* _gaugeSprite;
    
	void blinkBar();

};


#endif /* defined(__CampJam__BaseLayer__) */
