
#ifndef __CampJam__CoffeeBar__
#define __CampJam__CoffeeBar__

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

	void blinkBar();

};


#endif /* defined(__CampJam__BaseLayer__) */
