//
//  MainScene.h
//  Voyager
//
//  Created by Chihiro Tachinami on 2013/12/08.
//
//

#ifndef Voyager_MainScene_h
#define Voyager_MainScene_h

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuAskCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
};

#endif
