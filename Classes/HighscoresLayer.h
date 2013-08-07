//
//  HighscoresLayer.h
//  OfficeRampage
//
//  Created by Bruno Assarisse on 03/08/13.
//
//

#ifndef __OfficeRampage__HighscoresLayer__
#define __OfficeRampage__HighscoresLayer__

#include "cocos2d.h"

using namespace cocos2d;

class HighscoresLayer : public LayerColor {
    
private:
    
    Menu *_menu;
    LabelBMFont *_loadingLabel;
    LabelBMFont *_highscoreNumbers;
    LabelBMFont *_highscoreNames;
    LabelBMFont *_highscorePoints;
    
public:
    
    virtual bool init(std::function<void()> closeFunc);
    virtual void onEnter();
    
    void load();
    void setLoading(bool loading);
    void enableMenus(bool enabled);
    void updateScores(const char *numbers, const char *names, const char *points);
    
    CC_SYNTHESIZE(std::function<void()>, _closeFunc, CloseFunc)
    
};

#endif /* defined(__OfficeRampage__HighscoresLayer__) */
