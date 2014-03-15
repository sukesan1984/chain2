#include "GameOverScene.h"
#include "CCGATracker.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

CCScene* GameOver::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameOver *layer = GameOver::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLayerColor *background = CCLayerColor::create(ccc4(255, 255 , 255, 255));
    background->setAnchorPoint(CCPoint(0.5,0.5));
    background->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
    //background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    background->setPosition(ccp(0, 0));
    this->addChild(background);
    
    CCLabelTTF* titleLabel  = CCLabelTTF::create("GAME OVER", "MisakiGothic", 40);
    titleLabel->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 7 / 8));
    titleLabel->setColor(ccBLACK);
    this->addChild(titleLabel);
    
    CCLabelTTF* score = CCLabelTTF::create(CCString::createWithFormat("SCORE: %d", Score::instance().getScore())->getCString(), "MisakiGothic", 20);
    score->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 3 / 4 - 30));
    score->setColor(ccBLACK);
    this->addChild(score);
   
    CCLabelTTF* hit = CCLabelTTF::create(CCString::createWithFormat("MAX HITS: %d", Score::instance().getMaxHitNum())->getCString(), "MisakiGothic", 20);
    hit->setColor(ccBLACK);
    hit->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 3 / 4 - 60));
    this->addChild(hit);
    
    CCMenuItemFont* gameMainFont = CCMenuItemFont::create("RETRY", this, menu_selector(GameOver::gameMainAction));
    gameMainFont->setFontNameObj("MisakiGothic");
    CCMenuItemLabel *gameMainButton = gameMainFont;
    gameMainButton->setColor(ccBLACK);
    
    CCMenuItemFont* rankingFont = CCMenuItemFont::create("RANKING", this, menu_selector(GameOver::rankingAction));
    rankingFont->setFontNameObj("MisakiGothic");
    CCMenuItemLabel *rankingButton  = rankingFont;
    rankingButton->setColor(ccBLACK);
    
    CCMenuItemFont* topFont = CCMenuItemFont::create("TO TITLE", this, menu_selector(GameOver::topAction));
    topFont->setFontNameObj("MisakiGothic");
    CCMenuItemLabel *topButton  = topFont;
    topButton->setColor(ccBLACK);
    
    //CCMenu *menu = CCMenu::createWithItems(gameMainButton, NULL);
    CCMenu *menu  = CCMenu::create(gameMainButton, rankingButton, topButton, NULL);
    menu->setPosition(ccp(visibleSize.width/2, visibleSize.height/4));
    menu->alignItemsVertically();
    
    this->addChild(menu, 2);
    
    Cocos2dExt::NativeCodeLauncher::postHighScore(1, Score::instance().getScore());
    Cocos2dExt::NativeCodeLauncher::postHighScore(2, Score::instance().getMaxHitNum());
 
    
    setTouchEnabled(true);
    
    CCGATracker::sendEvent("score", "score", "score", Score::instance().getScore());
    CCGATracker::sendEvent("score", "score", "hit", Score::instance().getMaxHitNum());
    
    CCGATracker::sendView("GameOver");
    
    
    this->schedule(schedule_selector(GameOver::update));
    return true;
}

void GameOver::gameMainAction(){
    SimpleAudioEngine::sharedEngine()->playEffect("menu.wav");
    //切り替え先のシーン
    CCScene *scene = GameMain::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

void GameOver::rankingAction(){
    SimpleAudioEngine::sharedEngine()->playEffect("menu.wav");
    CCGATracker::sendView("Ranking");
    Cocos2dExt::NativeCodeLauncher::openRanking();
}

void GameOver::topAction(){
    SimpleAudioEngine::sharedEngine()->playEffect("menu.wav");
    //切り替え先のシーン
    CCScene *scene = Title::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}