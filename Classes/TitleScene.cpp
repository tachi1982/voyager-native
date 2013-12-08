#include "TitleScene.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"
#include "SimpleAudioEngine.h"
#include "PrologueScene.h"


USING_NS_CC_EXT;
USING_NS_CC;
using namespace CocosDenshion;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
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

    // add a "close" icon to exit the progress. it's an autorelease object
    auto buttonItem = MenuItemImage::create(
                                           "btn-map.png",
                                           "btn-map.png",
                                           CC_CALLBACK_1(TitleScene::menuCloseCallback, this));
    
	buttonItem->setPosition(Point(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(buttonItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Voyager"
    // create and initialize a label
    
    auto label = LabelTTF::create("This is TitleScene Scene of VoY∀GeR", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height - 50));
    this->addChild(label, 1);

    auto copyrightlabel = LabelTTF::create("©Planetarhythm: Towards the Nature of Planets", "Arial", 24);
    copyrightlabel->setPosition(Point(origin.x + visibleSize.width/2, origin.y + 75));
    this->addChild(copyrightlabel, 1);

    
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


    
    return true;
}


void TitleScene::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();
    //TODO メインシーンの作成
    log("TitleScene::onTouchBegan()");
    auto scene = PrologueScene::createScene();
    log("transition to prologue scene");
    // 0.5秒かけてブラックアウトして次のシーンへ移動する
    //auto fade = TransitionFade::create(0.5f, scene, Color3B::BLACK);
    //log("transition to prologue scene");
    Director::getInstance()->replaceScene(scene);
    log("transition to prologue scene");
}