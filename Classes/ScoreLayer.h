
#ifndef __CampJam__ScoreLayer__
#define __CampJam__ScoreLayer__

#include "cocos2d.h"

using namespace cocos2d;

class ScoreLayer : public Layer
{
public:
    
    ~ScoreLayer();
    
    virtual bool init();
            
	int _score;
	void setScore(int score);

	virtual void update(float dt);
	
	LabelBMFont* _scoreLabel;

};


#endif /* defined(__CampJam__BaseLayer__) */
