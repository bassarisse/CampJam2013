
#ifndef __PlatformerTest__HealthBar__
#define __PlatformerTest__HealthBar__

#include "cocos2d.h"

using namespace cocos2d;

class HealthBar : public Layer
{
public:
    
    ~HealthBar();
    
    virtual bool init(float healthLevel);
            
	float _healthLevel;
	void setHealthLevel(float health);

	virtual void update(float dt);

	LayerColor* _bar;

};


#endif /* defined(__PlatformerTest__BaseLayer__) */
