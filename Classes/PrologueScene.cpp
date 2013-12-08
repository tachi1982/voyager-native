//
//  Prologue.cpp
//  Voyager
//
//  Created by Chihiro Tachinami on 2013/11/27.
//
//

#include "PrologueScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;


PrologueScene::PrologueScene()
: _state(State_TouchIgnore)
, _messageIndex(0)
, _messageArray(nullptr)
, _messageTTF(nullptr)
, _animationManager(nullptr)
{
}

PrologueScene::~PrologueScene()
{
    log("Prologue::~Prologue()");
    if (_messageArray != nullptr)
    {
        _messageArray->removeAllObjects();
        CC_SAFE_RELEASE(_messageArray);
    }
    CC_SAFE_RELEASE(_messageTTF);
    CC_SAFE_RELEASE(_animationManager);
}
Scene* PrologueScene::createScene()
{
    auto scene = Scene::create();
    
    auto nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    // プロローグシーンのローダーを追加
    nodeLoaderLibrary->registerNodeLoader("PrologueScene", PrologueSceneLoader::loader());
    CCBReader* reader = new CCBReader(nodeLoaderLibrary);
    log("reading Prologue ccbi");
    // プロローグのccbiファイルを読み込む
    auto prologueNode = reader->readNodeGraphFromFile("PrologueScene.ccbi");
    // アニメーションマネージャーをセットする
    static_cast<PrologueScene*>(prologueNode)->setAnimationManager(reader->getAnimationManager());
    log("here is passed l:50");
    scene->addChild(prologueNode);
    // 開放
    reader->release();
    
    log("returning scene");
    return scene;
}
bool PrologueScene::init()
{
    log("PrologueScene::init()");
    if ( !Layer::init() )
    {
        return false;
    }
    
    // プロローグの内容をセットする
    _messageArray = Array::create(
                                  ccs("宇宙のどこかにある、名前のない小さな惑星。"),
                                  ccs("そこに、『君』はたったひとりで暮らしています。"),
                                  ccs("そんなある日、空から轟音と共に何かが落ちてきました。"),
                                  ccs("『君』が恐る恐る近づいてみるとーー。"),
                                  ccs("「……ここはどこでしょう？」"),
                                  ccs("それは突然動き出し、『君』に尋ねたのです。"),
                                  ccs("（画面をタップして次へ）"),
                                  NULL);
    // retainしてあげないとこのブロック抜けたら消えてしまう
    _messageArray->retain();
    
    // シングルタップのみ受付
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    return true;
}

void PrologueScene::onEnterTransitionDidFinish()
{
    log("PrologueScene::onEnterTransitionDidFinish()");
    Layer::onEnterTransitionDidFinish();
    
    animationStart();
}

bool PrologueScene::onTouchBegan(Touch *touch, Event *event)
{
    log("PrologueScene::onTouchBegan()");
    switch (_state)
    {
        case State_StartAnimationEnd:
            animationStartEnd();
            break;
            // テキスト表示開始アニメーション中か終了していればテキスト表示終了アニメーションを再生
        case State_TextStartAnimation:
        case State_TextStartAnimationEnd:
            animationTextEnd();
            break;
            // テキスト表示終了アニメーション中なら次のテキスト表示にスキップ
        case State_TextEndAnimation:
            // 最後はスルー
            if (_messageIndex == _messageArray->count())
            {
                return false;
            }
            animationTextStart();
            break;
            // それ以外は何もしない
        default:
            return false;
    }
    return false;
}

void PrologueScene::animationStart()
{
    log("PrologueScene::animationStart()");
    _animationManager->runAnimationsForSequenceNamedTweenDuration("Start", 0.0f);
}

void PrologueScene::animationStartEnd()
{
    log("PrologueScene::animationStartEnd()");
    _state = State_TouchIgnore;
    _animationManager->runAnimationsForSequenceNamedTweenDuration("StartEnd", 0.0f);
}

void PrologueScene::animationTextStart()
{
    log("PrologueScene::animationTextStart()");
    _state = State_TextStartAnimation;
    // メッセージを更新してから表示する
    String* message = static_cast<String*>(_messageArray->getObjectAtIndex(_messageIndex));
    _messageTTF->setString(message->getCString());
    
    float duration = 0.0f;
    // 初回だけディレイを取る
    if (_messageIndex == 0)
    {
        duration = 0.3f;
    }
    _animationManager->runAnimationsForSequenceNamedTweenDuration("TextStart", duration);
    // 次のメッセージを表示するようにカウントアップ
    ++_messageIndex;
}
void PrologueScene::animationTextEnd()
{
    log("PrologueScene::animationTextEnd()");
    _state = State_TextEndAnimation;
    _animationManager->runAnimationsForSequenceNamedTweenDuration("TextEnd", 0.0f);
}


bool PrologueScene::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode)
{
    log("onAssignCCBMember: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_messageTTF", LabelTTF*, _messageTTF);
    
    return true;
}

void PrologueScene::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
    log("PrologueScene::setAnimationManager()");
    CC_SAFE_RELEASE_NULL(_animationManager);
    _animationManager = pAnimationManager;
    CC_SAFE_RETAIN(_animationManager);
    // アニメーション終了を受け取れるようにデリゲートをセット
    _animationManager->setDelegate(this);
}

void PrologueScene::completedAnimationSequenceNamed(const char *name)
{
    log("completedAnimation: %s", name);
    // タイムラインの名前によって処理を分ける。必要のあるものだけ指定する
    if(strcmp(name,"Start") == 0)
    {
        _state = State_StartAnimationEnd;
    }
    else if(strcmp(name,"StartEnd") == 0)
    {
        animationTextStart();
    }
    else if(strcmp(name,"TextStart") == 0)
    {
        _state = State_TextStartAnimationEnd;
    }
    else if(strcmp(name,"TextEnd") == 0)
    {
        // メッセージを表示。最後まで表示したら次のシーンへ
        if (_messageIndex < _messageArray->count())
        {
            animationTextStart();
        }
        else
        {
            // TODO チュートリアルを作成後切り替える;
            auto scene = TitleScene::createScene();
            // 0.5秒かけてブラックアウトしてシーンを切り替える
            auto fade = TransitionFade::create(0.5f, scene, Color3B::BLACK);
            Director::getInstance()->replaceScene(fade);
        }
    }
}