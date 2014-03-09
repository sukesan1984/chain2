#include "GameOverScene.h"

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
    
    CCLabelTTF* titleLabel  = CCLabelTTF::create("GameOver", "arial", 20);
    titleLabel->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 3 / 4));
    this->addChild(titleLabel);
    
    CCLabelTTF* score = CCLabelTTF::create(CCString::createWithFormat("score: %d", Score::instance().getScore())->getCString(), "Arial", 20);
    score->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 3 / 4 - 30));
    this->addChild(score);
   
    CCLabelTTF* hit = CCLabelTTF::create(CCString::createWithFormat("maxHit: %d", Score::instance().getMaxHitNum())->getCString(), "Arial", 20);
    hit->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 3 / 4 - 60));
    this->addChild(hit);
    
    CCMenuItemLabel *gameMainButton = CCMenuItemFont::create("Retry", this, menu_selector(GameOver::gameMainAction));
    CCMenuItemLabel *rankingButton  = CCMenuItemFont::create("Ranking", this, menu_selector(GameOver::rankingAction));
    
    //CCMenu *menu = CCMenu::createWithItems(gameMainButton, NULL);
    CCMenu *menu  = CCMenu::create(gameMainButton, rankingButton, NULL);
    menu->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    menu->alignItemsVertically();
    
    this->addChild(menu, 2);
    
    Cocos2dExt::NativeCodeLauncher::postHighScore(1, Score::instance().getScore());
    Cocos2dExt::NativeCodeLauncher::postHighScore(2, Score::instance().getMaxHitNum());
 
    
    setTouchEnabled(true);
    
    this->schedule(schedule_selector(GameOver::update));
    return true;
}

void GameOver::gameMainAction(){
    //切り替え先のシーン
    CCScene *scene = GameMain::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

void GameOver::rankingAction(){
    Cocos2dExt::NativeCodeLauncher::openRanking();
}