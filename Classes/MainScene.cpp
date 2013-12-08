//
//  MainScene.cpp
//  Voyager
//
//  Created by Chihiro Tachinami on 2013/12/08.
//
//

#include "MainScene.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "start" icon to start the game. it's an autorelease object
    auto buttonItem = MenuItemImage::create(
                                            "btn-ask.png",
                                            "btn-ask.png",
                                            CC_CALLBACK_1(MainScene::menuAskCallback, this));
    
	buttonItem->setPosition(Point(origin.x + visibleSize.width/2,
                                  origin.y + 100));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(buttonItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Voyager"
    // create and initialize a label
    
    auto label = LabelTTF::create("Debug: This is MainScene Scene of VoY∀GeR", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height - 50));
    this->addChild(label, 1);
    
    auto positionlabel = LabelTTF::create("Position: 木星", "Arial", 24);
    positionlabel->setPosition(Point(origin.x + visibleSize.width/4*3,
                             origin.y + visibleSize.height - label->getContentSize().height - 50));
    this->addChild(positionlabel, 1);
    auto editBoxSize = Size(320, 50);
    auto m_pEditTest = EditBox::create(editBoxSize, Scale9Sprite::create(("bg-textfield.png")));
    m_pEditTest->setFontSize(10);
    m_pEditTest->setFontColor(ccBLACK);
    m_pEditTest->setPlaceholderFontColor(ccWHITE);
    m_pEditTest->setPlaceHolder("テキスト入力欄");
    m_pEditTest->setMaxLength(8);
    m_pEditTest->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    m_pEditTest->setInputMode(kEditBoxInputModeAny);
    // add the sprite as a child to this layer
    m_pEditTest->setReturnType(kKeyboardReturnTypeDone);
    this->addChild(m_pEditTest, 10);
  /*
    auto textFieldSize = Size(320, 50);
    auto textField = CCTextFieldTTF::textFieldWithPlaceHolder("テキスト入力欄",textFieldSize,kCCTextAlignmentLeft,"Thonburi",24);
    textField->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(textField, 10);
   */
    // add "Background splash screen"
    auto bgSprite = Sprite::create("bg-portrait.png");
    bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(bgSprite, 0);
    
    // add "Bachground-head splash screen"
    auto headSprite = Sprite::create("bg-head.png");
    headSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 50));
    this->addChild(headSprite, 2);
    
    // add "Bachground-bottom splash screen"
    auto footSprite = Sprite::create("bg-foot.png");
    footSprite->setPosition(Point(visibleSize.width/2 + origin.x, origin.y + 50));
    this->addChild(footSprite, 3);
    
    // add "Voyager splash screen"
    auto VoyagerSprite = Sprite::create("chara-voyager.png");
    VoyagerSprite->setPosition(Point(visibleSize.width/4*3 + origin.x, visibleSize.height/4*3 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(VoyagerSprite, 10);
    
    return true;
}


void MainScene::menuAskCallback(Object* pSender)
{
    Director::getInstance()->end();
    
    //TODO 処理の作成
}