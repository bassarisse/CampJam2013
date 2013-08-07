//
//  GameJoltLoginLayer.h
//  OfficeRampage
//
//  Created by Bruno Assarisse on 05/08/13.
//
//

#ifndef __OfficeRampage__GameJoltLoginLayer__
#define __OfficeRampage__GameJoltLoginLayer__

#include "cocos2d.h"
#include "../../../extensions/GUI/CCEditBox/CCEditBox.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class GameJoltLoginLayer : public LayerColor {
    
public:
    
    virtual bool init(std::function<void()> closeFunc);
    
    CC_SYNTHESIZE(std::function<void()>, _closeFunc, CloseFunc)
    
};

#endif /* defined(__OfficeRampage__GameJoltLoginLayer__) */
