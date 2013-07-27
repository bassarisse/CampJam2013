//
//  BaseLayer.h
//  PlatformerTest
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#ifndef __PlatformerTest__BaseLayer__
#define __PlatformerTest__BaseLayer__

#include "cocos2d.h"

using namespace cocos2d;

class BaseLayer : public Layer
{
public:
    
    ~BaseLayer();
    
    virtual bool init();
    
    double getCurrentTimeInSeconds();
    
    virtual void recursivelyPauseAllChildren(Node *node);
    virtual void recursivelyResumeAllChildren(Node *node);
    
    virtual void keyPressed(int keyCode);
    virtual void keyReleased(int keyCode);
    virtual void handleKey(int keyCode, bool pressed);
    
    virtual void buttonUp(bool pressed);
    virtual void buttonDown(bool pressed);
    virtual void buttonLeft(bool pressed);
    virtual void buttonRight(bool pressed);
    virtual void buttonA(bool pressed);
    virtual void buttonB(bool pressed);
    virtual void buttonStart(bool pressed);
    virtual void buttonSelect(bool pressed);
    
};


#endif /* defined(__PlatformerTest__BaseLayer__) */
