//
//  GameJoltLoginLayer.cpp
//  OfficeRampage
//
//  Created by Bruno Assarisse on 05/08/13.
//
//

#include "GameJoltLoginLayer.h"

#include "GameJolt.h"
#include "Common.h"

bool GameJoltLoginLayer::init(std::function<void()> closeFunc) {
    
    if (!LayerColor::initWithColor(ccc4(0, 0, 0, kOverlayOpacity)))
        return false;
    
    _closeFunc = closeFunc;
    
    Size inputSize = CCSizeMake(this->getContentSize().width * 0.3f, 40);
    
    auto gjLogo = Sprite::create("gamejolt_logo.png");
    gjLogo->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.75f));
    gjLogo->getTexture()->setAliasTexParameters();

    EditBox *loginEditBox = EditBox::create(inputSize, Scale9Sprite::create("editboxbg.png"));
    loginEditBox->setAnchorPoint(ccp(0.5f, 0.5f));
    loginEditBox->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.62f));
    loginEditBox->setFontColor(ccBLACK);
    loginEditBox->setPlaceHolder("Username");
    loginEditBox->setReturnType(kKeyboardReturnTypeDone);
    //_loginEditBox->setDelegate(this);
    
    EditBox *tokenEditBox = EditBox::create(inputSize, Scale9Sprite::create("editboxbg.png"));
    tokenEditBox->setAnchorPoint(ccp(0.5f, 0.5f));
    tokenEditBox->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.52f));
    tokenEditBox->setFontColor(ccBLACK);
    tokenEditBox->setPlaceHolder("Token");
    tokenEditBox->setReturnType(kKeyboardReturnTypeDone);
    //_tokenEditBox->setDelegate(this);
    
    if (UserDefault::sharedUserDefault()->getBoolForKey("Logged", false)) {
        string loggedUser = UserDefault::sharedUserDefault()->getStringForKey("LoggedUser");
        string loggedToken = UserDefault::sharedUserDefault()->getStringForKey("LoggedToken");
        loginEditBox->setText(loggedUser.c_str());
        tokenEditBox->setText(loggedToken.c_str());
    }
    
    auto loginLabel = LabelBMFont::create("Login", "MainFont.fnt", 100, kTextAlignmentCenter);
    auto cancelLabel = LabelBMFont::create("Cancel", "MiniFont.fnt", 100, kTextAlignmentCenter);
    auto logoutLabel = LabelBMFont::create("Logout", "MiniFont.fnt", 100, kTextAlignmentCenter);
    
    loginLabel->setColor(greenLabelColor);
    cancelLabel->setColor(yellowLabelColor);
    logoutLabel->setColor(redLabelColor);
    
    auto loginMenuItem = MenuItemLabel::create(loginLabel, [this, loginEditBox, tokenEditBox](Object *object) {
        
        GameJolt::getInstance()->login(loginEditBox->getText(), tokenEditBox->getText());
        this->getCloseFunc()();
        this->removeFromParentAndCleanup(true);
        
    });
    
    auto cancelMenuItem = MenuItemLabel::create(cancelLabel, [this](Object *object) {
        
        this->getCloseFunc()();
        this->removeFromParentAndCleanup(true);
        
    });
    
    auto logoutMenuItem = MenuItemLabel::create(logoutLabel, [this](Object *object) {
        
        GameJolt::getInstance()->logout();
        this->getCloseFunc()();
        this->removeFromParentAndCleanup(true);
        
    });
    
    auto menu = Menu::create(cancelMenuItem, loginMenuItem, logoutMenuItem, NULL);
    menu->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.4f));
    menu->alignItemsHorizontallyWithPadding(80);
    
    auto notice = LabelBMFont::create("Warning:\nThe token is NOT your password.\nGet yours on GameJolt.com!", "MiniFont.fnt", this->getContentSize().width, kTextAlignmentCenter);
    notice->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.11f));
    
    this->addChild(gjLogo);
    this->addChild(loginEditBox);
    this->addChild(tokenEditBox);
    this->addChild(menu);
    this->addChild(notice);
    
    return true;
}