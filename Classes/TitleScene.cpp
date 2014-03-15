#include "TitleScene.h"
#include "CCGATracker.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
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
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("title.plist");
    SimpleAudioEngine::sharedEngine()->preloadEffect("menu.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("pon.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("shupiin.wav");
    
    
    //CCLabelTTF* titleLabel  = CCLabelTTF::create("Hello", "arial", 20);
    //titleLabel->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height / 2));
    //this->addChild(titleLabel);
    
    CCSprite* titleBackground = CCSprite::createWithSpriteFrameName("title.png");
    titleBackground->setAnchorPoint(CCPoint(0.5, 0.5));
    titleBackground->setScale(1.18);
    this->addChild(titleBackground, 1);
    
    CCMenuItemFont* gameMainFont = CCMenuItemFont::create("GAME START", this, menu_selector(Title::gameMainAction));
    gameMainFont->setFontNameObj("MisakiGothic");
    CCMenuItemLabel *gameMainButton = gameMainFont;
    gameMainButton->setColor(ccBLACK);
    
    CCMenuItemFont* rankingFont = CCMenuItemFont::create("RANKING", this, menu_selector(Title::rankingAction));
    rankingFont->setFontNameObj("MisakiGothic");
    CCMenuItemLabel *rankingButton  =rankingFont;
    rankingButton->setColor(ccBLACK);
    //CCMenuItemLabel *gamecenterButton  = CCMenuItemFont::create("GameCenterLogin", this, menu_selector(Title::login));
    
    //CCMenu *menu = CCMenu::createWithItems(gameMainButton, NULL);
    CCMenu *menu  = CCMenu::create(gameMainButton, rankingButton, NULL);
    menu->setPosition(ccp(visibleSize.width/2, visibleSize.height/4));
    menu->alignItemsVertically();
    
    this->addChild(menu, 2);
    
    CCGATracker::sendView("Title");
    
    setTouchEnabled(true);
    
    this->schedule(schedule_selector(Title::update));
    return true;
}

void Title::gameMainAction(){
    SimpleAudioEngine::sharedEngine()->playEffect("menu.wav");
    //切り替え先のシーン
    CCScene *scene = Tutorial::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

void Title::rankingAction(){
    SimpleAudioEngine::sharedEngine()->playEffect("menu.wav");
    CCGATracker::sendView("Ranking");
    Cocos2dExt::NativeCodeLauncher::openRanking();
}
