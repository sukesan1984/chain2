#include "CreditScene.h"
#include "CCGATracker.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

CCScene* Credit::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Credit *layer = Credit::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Credit::init()
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
    
    
    CCLayerColor *background = CCLayerColor::create(ccc4(255, 255 , 255, 255));
    background->setAnchorPoint(CCPoint(0.5,0.5));
    background->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
    //background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    background->setPosition(ccp(0, 0));
    this->addChild(background);
    
       
    CCLabelTTF* specialThanks = CCLabelTTF::create("SPECIAL THANKS", "MisakiGothic", 30);
    specialThanks->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 3 / 4));
    specialThanks->setColor(ccBLACK);
    this->addChild(specialThanks);
    
    CCLabelTTF* maou = CCLabelTTF::create("魔王魂", "MisakiGothic", 20);
    maou->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 3 / 4 - 50));
    maou->setColor(ccBLACK);
    this->addChild(maou);
    
    CCLabelTTF* shinchoku = CCLabelTTF::create("進捗確認会", "MisakiGothic", 20);
    shinchoku->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height * 3 / 4 - 80));
    shinchoku->setColor(ccBLACK);
    this->addChild(shinchoku);
    
    CCMenuItemFont* titleFont = CCMenuItemFont::create("TO TITLE", this, menu_selector(Credit::titleAction));
    titleFont->setFontNameObj("MisakiGothic");
    CCMenuItemLabel *titleButton  =titleFont;
    titleButton->setColor(ccBLACK);
    
    //CCMenu *menu = CCMenu::createWithItems(gameMainButton, NULL);
    CCMenu *menu  = CCMenu::create(titleButton, NULL);
    menu->setPosition(ccp(visibleSize.width/2, visibleSize.height/4));
    menu->alignItemsVertically();
    
    this->addChild(menu, 2);
    
    CCGATracker::sendView("Credit");
    
    setTouchEnabled(true);
    
    this->schedule(schedule_selector(Credit::update));
    return true;
}

void Credit::titleAction(){
    SimpleAudioEngine::sharedEngine()->playEffect("menu.wav");
    //切り替え先のシーン
    CCScene *scene = Title::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

