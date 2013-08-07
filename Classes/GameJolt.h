//
//  GameJolt.h
//  OfficeRampage
//
//  Created by Bruno Assarisse on 03/08/13.
//
//

#ifndef __OfficeRampage__GameJolt__
#define __OfficeRampage__GameJolt__

#include "GameJolt/gjAPI.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class GameJolt : public Object
{
private:
    
    GameJolt();
    
    //Instance of the singleton
    static GameJolt* m_mySingleton;
    
    gjAPI API;
    gjScoreTable *_scoreTable;
    
    gjScoreTable* getScoreTable();
    void addedScore(const gjScorePtr &score, void *extraData);
    void receivedScores(const gjScoreList &scoreList, void *extraData);
    
public:
    //Get instance of singleton
    static GameJolt* getInstance();
    
    void login(const string &sUserName, const string &sUserToken);
    void logout();
    
    void update(float dt);
    void addScore(int score);
    void loadScores(int max, function<void(gjScoreList)> func);
    
};

#endif /* defined(__OfficeRampage__GameJolt__) */
