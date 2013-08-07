#ifndef __CAMPJAM_GAMEOVER_H__
#define __CAMPJAM_GAMEOVER_H__

#include "../BaseLayer.h"

using namespace cocos2d;


class GameoverScene : public BaseLayer
{
    
private:
    
    Menu *_menu;
    Menu *_highscoresMenu;

public:


	static GameoverScene* create(int score, bool isRecord) 
	{ 
		GameoverScene *pRet = new GameoverScene(); 
		if (pRet && pRet->init(score, isRecord))
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = NULL; 
			return NULL; 
		} 
	}

	CC_SYNTHESIZE(int, _score, Score);

	virtual bool init(int score, bool isRecord);
	static Scene* scene(int score, bool isRecord);

    void enableMenus(bool enabled);

};

#endif // __CAMPJAM_SCENE_H__