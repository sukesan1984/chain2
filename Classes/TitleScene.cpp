#include "TitleScene.h"
#include "CCGATracker.h"

USING_NS_CC;

CCScene* Title::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Title *layer = Title::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Title::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    srand(time(NULL));
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("panels.plist");
    
    //CCLabelTTF* titleLabel  = CCLabelTTF::create("Hello", "arial", 20);
    //titleLabel->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height / 2));
    //this->addChild(titleLabel);
    
    CCMenuItemLabel *gameMainButton = CCMenuItemFont::create("Game Start", this, menu_selector(Title::gameMainAction));
    CCMenuItemLabel *rankingButton  = CCMenuItemFont::create("Ranking", this, menu_selector(Title::rankingAction));
    //CCMenuItemLabel *gamecenterButton  = CCMenuItemFont::create("GameCenterLogin", this, menu_selector(Title::login));
    
    //CCMenu *menu = CCMenu::createWithItems(gameMainButton, NULL);
    CCMenu *menu  = CCMenu::create(gameMainButton, rankingButton, NULL);
    menu->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    menu->alignItemsVertically();
    
    this->addChild(menu, 2);
    
    CCGATracker::sendView("Title");
    
    setTouchEnabled(true);
    
    this->schedule(schedule_selector(Title::update));
    return true;
}

void Title::gameMainAction(){
    //切り替え先のシーン
    CCScene *scene = Tutorial::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

void Title::rankingAction(){
    CCGATracker::sendView("Ranking");
    Cocos2dExt::NativeCodeLauncher::openRanking();
}
