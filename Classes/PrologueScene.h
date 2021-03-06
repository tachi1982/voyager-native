//
//  Prologue.h
//  Voyager
//
//  Created by Chihiro Tachinami on 2013/11/27.
//
//

#ifndef Voyager_PrologueScene_h
#define Voyager_PrologueScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "TitleScene.h"

class PrologueScene
: public cocos2d::Layer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBAnimationManagerDelegate
{
public:
    PrologueScene();
    virtual ~PrologueScene();
    
    // 処理の状態
    enum State {
        State_TouchIgnore,
        State_StartAnimationEnd,
        State_TextStartAnimation,
        State_TextStartAnimationEnd,
        State_TextEndAnimation,
    };
    
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    // シーン切り替え後にBGMを再生
    virtual void onEnterTransitionDidFinish() override;
    // タップでテキストを更新する
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    // 開始のアニメーション
    void animationStart();
    // 開始のアニメーションを終了するアニメーション
    void animationStartEnd();
    // テキスト表示開始のアニメーション
    void animationTextStart();
    // テキスト表示終了のアニメーション
    void animationTextEnd();
    
    // CocosBuilder通常メンバ変数紐付け
    virtual bool onAssignCCBMemberVariable(cocos2d::Object* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
    // CocosBuilderアニメーション紐付け
    void setAnimationManager(cocos2d::extension::CCBAnimationManager* pAnimationManager);
    // CocosBuilderアニメーション完了時にタイムライン名が引数として実行される
    virtual void completedAnimationSequenceNamed(const char *name);
    CREATE_FUNC(PrologueScene);
    
private:
    // 現在の処理状態
    State _state;
    // メッセージのインデックス
    unsigned int _messageIndex;
    // メッセージの配列
    cocos2d::Array* _messageArray;
    // メッセージラベル
    cocos2d::LabelTTF* _messageTTF;
    cocos2d::extension::CCBAnimationManager* _animationManager;
};

class PrologueSceneLoader : public cocos2d::extension::LayerLoader {
public:
    virtual ~PrologueSceneLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PrologueSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PrologueScene);
};

#endif
