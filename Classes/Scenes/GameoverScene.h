#ifndef __CAMPJAM_GAMEOVER_H__
#define __CAMPJAM_GAMEOVER_H__

#include "../BaseLayer.h"

using namespace cocos2d;


class GameoverScene : public BaseLayer
{

public:


	static GameoverScene* create(int score) 
	{ 
		GameoverScene *pRet = new GameoverScene(); 
		if (pRet && pRet->init(score)) 
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

	virtual ~GameoverScene();

	virtual bool init(int score);
	static Scene* scene(int score);

	void update(float dt);

	void GameoverScene::clickedRetry(Object* sender);
	void GameoverScene::clickedTitle(Object* sender);

};

#endif // __CAMPJAM_SCENE_H__