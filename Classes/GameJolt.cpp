//
//  GameJolt.cpp
//  OfficeRampage
//
//  Created by Bruno Assarisse on 03/08/13.
//
//

#include "GameJolt.h"

class ScoreCallBack {
public:
    function<void(gjScoreList)> func;
};

GameJolt* GameJolt::m_mySingleton = nullptr;

GameJolt::GameJolt()
:API(16430, "a7838f4ca9a817c69268e4bf684e2eb0")
{
    
    _scoreTable = nullptr;
    
    if (UserDefault::sharedUserDefault()->getBoolForKey("Logged", false)) {
        string loggedUser = UserDefault::sharedUserDefault()->getStringForKey("LoggedUser");
        string loggedToken = UserDefault::sharedUserDefault()->getStringForKey("LoggedToken");
        this->login(loggedUser, loggedToken);
    }
    
    Director::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 50, false);
}

GameJolt* GameJolt::getInstance()
{
    //If the singleton has no instance yet, create one
    if(nullptr == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new GameJolt();
    }
    
    //Return the singleton object
    return m_mySingleton;
}

void GameJolt::update(float dt) {
    
    API.Update();
    
}

gjScoreTable* GameJolt::getScoreTable() {
    if (_scoreTable == nullptr) {
        _scoreTable = API.InterScore()->GetScoreTable(16777);
    }
    return _scoreTable;
}

void GameJolt::login(const std::string &sUserName, const std::string &sUserToken) {
    
    this->logout();
    
    API.Login(false, sUserName, sUserToken);
    
    UserDefault::sharedUserDefault()->setBoolForKey("Logged", true);
    UserDefault::sharedUserDefault()->setStringForKey("LoggedUser", sUserName);
    UserDefault::sharedUserDefault()->setStringForKey("LoggedToken", sUserToken);
    UserDefault::sharedUserDefault()->flush();
    
    if (!UserDefault::sharedUserDefault()->getBoolForKey("ScoreSynced", false)) {
        int recordScore = UserDefault::sharedUserDefault()->getIntegerForKey("Record", 0);
        if (recordScore > 0)
            this->addScore(recordScore);
    }
    
}

void GameJolt::logout() {
    
    if (!UserDefault::sharedUserDefault()->getBoolForKey("Logged", false))
        return;
    
    API.Logout();
    
    UserDefault::sharedUserDefault()->setBoolForKey("Logged", false);
    UserDefault::sharedUserDefault()->setStringForKey("LoggedUser", "");
    UserDefault::sharedUserDefault()->setStringForKey("LoggedToken", "");
    UserDefault::sharedUserDefault()->flush();
    
}

void GameJolt::addScore(int score) {
    
    UserDefault::sharedUserDefault()->setBoolForKey("ScoreSynced", false);
    UserDefault::sharedUserDefault()->flush();
    
    if (!UserDefault::sharedUserDefault()->getBoolForKey("Logged", false))
        return;
    
    this->getScoreTable()->AddScoreCall(String::createWithFormat("%i points", score)->getCString(), score, "", "", this, &GameJolt::addedScore, nullptr);
    
}

void GameJolt::addedScore(const gjScorePtr &score, void *extraData) {
    
    UserDefault::sharedUserDefault()->setBoolForKey("ScoreSynced", true);
    UserDefault::sharedUserDefault()->flush();
    
}

void GameJolt::loadScores(int max, function<void(gjScoreList)> func) {
    
    auto callback = new ScoreCallBack();
    callback->func = func;
    
    this->getScoreTable()->FetchScoresCall(false, max, this, &GameJolt::receivedScores, callback);
    
}

void GameJolt::receivedScores(const gjScoreList &scoreList, void *extraData) {
    
    auto callback = (ScoreCallBack *)extraData;
    callback->func(scoreList);
    delete callback;
}