
#ifndef __CampJam__CoffeeBar__
#define __CampJam__CoffeeBar__

#include "cocos2d.h"

using namespace cocos2d;

class CoffeeBar : public Layer
{
    
private:
    
    Sprite* _coffeeIcon;
	LayerColor* _bar;
	Sprite* _gaugeSprite;
    
    
public:
    
    virtual bool init(float coffeeLevel);
            
	float _coffeeLevel;
	void setCoffeeLevel(float coff);

	virtual void update(float dt);
    
	void blinkBar();
	void setPeaBerry(bool isPeaBerry);

};


#endif /* defined(__CampJam__BaseLayer__) */
