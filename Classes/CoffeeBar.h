
#ifndef __PlatformerTest__CoffeeBar__
#define __PlatformerTest__CoffeeBar__

#include "cocos2d.h"

using namespace cocos2d;

class CoffeeBar : public Layer
{
public:
    
    ~CoffeeBar();
    
    virtual bool init(float coffeeLevel);
            
	float _coffeeLevel;
	void setCoffeeLevel(float coff);

	virtual void update(float dt);

	LayerColor* _bar;

};


#endif /* defined(__PlatformerTest__BaseLayer__) */
