//
//  HighscoresLayer.cpp
//  OfficeRampage
//
//  Created by Bruno Assarisse on 03/08/13.
//
//

#include "HighscoresLayer.h"

#include "GameJolt.h"
#include "GameJoltLoginLayer.h"
#include "Common.h"

bool HighscoresLayer::init(std::function<void()> closeFunc) {
    
    if (!LayerColor::initWithColor(ccc4(0, 0, 0, kOverlayOpacity)))
        return false;
    
    _closeFunc = closeFunc;
    
    int highscoreListY = this->getContentSize().height - 100;
    int highscoreListMidX = this->getContentSize().width * 0.4f;
    
    auto title = LabelBMFont::create("Highscores", "MainFont.fnt", 200, kTextAlignmentCenter);
    title->setPosition(ccp(this->getContentSize().width * 0.5f, highscoreListY + 50));
    
    _loadingLabel = LabelBMFont::create("Loading...", "MainFont.fnt", this->getContentSize().width * 0.5f, kTextAlignmentCenter);
    _loadingLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    _loadingLabel->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f));
    
    _highscoreNumbers = LabelBMFont::create("", "MiniFont.fnt", 50, kTextAlignmentCenter);
    _highscoreNames = LabelBMFont::create("", "MiniFont.fnt", highscoreListMidX, kTextAlignmentLeft);
    _highscorePoints = LabelBMFont::create("", "MiniFont.fnt", highscoreListMidX, kTextAlignmentRight);
    
    _highscoreNumbers->setAnchorPoint(ccp(0.5f, 1));
    _highscoreNames->setAnchorPoint(ccp(0, 1));
    _highscorePoints->setAnchorPoint(ccp(1, 1));
    
    _highscoreNumbers->setPosition(ccp(highscoreListMidX, highscoreListY));
    _highscoreNames->setPosition(ccp(highscoreListMidX + 25, highscoreListY));
    _highscorePoints->setPosition(ccp(highscoreListMidX - 25, highscoreListY));
    
    auto gjLogo = Sprite::create("gamejolt_poweredby.png");
    gjLogo->setAnchorPoint(ccp(0, 0));
    gjLogo->setPosition(ccp(20, 20));
    gjLogo->getTexture()->setAliasTexParameters();
    
    auto loginLabel = LabelBMFont::create("Account", "MainFont.fnt", 100, kTextAlignmentCenter);
    auto backLabel = LabelBMFont::create("Back", "MainFont.fnt", 100, kTextAlignmentCenter);
    
    loginLabel->setColor(greenLabelColor);
    backLabel->setColor(yellowLabelColor);
    
    auto loginMenuItem = MenuItemLabel::create(loginLabel, [this](Object *object) {
        
        this->enableMenus(false);
        
        auto loginLayer = new GameJoltLoginLayer();
        loginLayer->init([this]() {
            this->enableMenus(true);
        });
        this->addChild(loginLayer);
        loginLayer->release();
        
    });
    
    auto backMenuItem = MenuItemLabel::create(backLabel, [this](Object *object) {
        
        this->getCloseFunc()();
        this->removeFromParentAndCleanup(true);
        
    });
    
    _menu = Menu::create(loginMenuItem, backMenuItem, NULL);
    _menu->setPosition(ccp(this->getContentSize().width * 0.7f, 38));
    _menu->alignItemsHorizontallyWithPadding(100);
    
    this->addChild(title);
    this->addChild(_loadingLabel);
    this->addChild(_highscoreNumbers);
    this->addChild(_highscoreNames);
    this->addChild(_highscorePoints);
    this->addChild(gjLogo);
    this->addChild(_menu);
    
    int recordScore = UserDefault::sharedUserDefault()->getIntegerForKey("Record", 0);
    
    if (recordScore > 0) {
        
        auto bestScoreLabel = LabelBMFont::create(String::createWithFormat("Your best score: %i", recordScore)->getCString(), "MiniFont.fnt", this->getContentSize().width * 0.5f, kTextAlignmentCenter);
        bestScoreLabel->setAnchorPoint(ccp(0.5f, 0.5f));
        bestScoreLabel->setPosition(ccp(this->getContentSize().width * 0.5f, 129));
        
        this->addChild(bestScoreLabel);
        
    }
    
    return true;
}

void HighscoresLayer::onEnter() {
    LayerColor::onEnter();
    this->load();
}

void HighscoresLayer::load() {
    
    this->setLoading(true);
    
    GameJolt::getInstance()->loadScores(12, [this](gjScoreList scoreList) {
        
        std::string numbers = "";
        std::string names = "";
        std::string points = "";
        
        for (gjScoreList::size_type i = 0; i < scoreList.size(); i++) {
            auto score = scoreList[i];
            
            if (i > 0) {
                numbers.append("\n");
                names.append("\n");
                points.append("\n");
            }
            
            numbers.append(String::createWithFormat("%li", i + 1)->getCString());
            names.append("- ");
            names.append(score->GetUserName());
            points.append(String::createWithFormat("%i -", score->GetSort())->getCString());
            
        }
        
        this->updateScores(numbers.c_str(), names.c_str(), points.c_str());
        this->setLoading(false);
        
    });
    
}

void HighscoresLayer::setLoading(bool loading) {
    
    _loadingLabel->setVisible(loading);
    _highscoreNumbers->setVisible(!loading);
    _highscoreNames->setVisible(!loading);
    _highscorePoints->setVisible(!loading);
    
}

void HighscoresLayer::enableMenus(bool enabled) {
    
    _menu->setEnabled(enabled);
    
}

void HighscoresLayer::updateScores(const char *numbers, const char *names, const char *points) {
    
    _highscoreNumbers->setString(numbers);
    _highscoreNames->setString(names);
    _highscorePoints->setString(points);
    
}