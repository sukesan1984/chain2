#include "TutorialScene.h"
#include "CCGATracker.h"

USING_NS_CC;

CCScene* Tutorial::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Tutorial *layer = Tutorial::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Tutorial::init()
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
    
    CCLabelTTF* title = CCLabelTTF::create("Tutorial", "arial", 40);
    title->setAnchorPoint(ccp(0.5, 1.0));
    title->setPosition(ccp(visibleSize.width / 2, visibleSize.height -20));
    this->addChild(title);
    
    CCSprite* tutorial = CCSprite::createWithSpriteFrameName("tutorial.png");
    tutorial->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    //visibleSize.width * tutorial->getContentSize().width / 640;
    // 600
    tutorial->setScale(visibleSize.width / 640);
    
    this->addChild(tutorial);
    
    CCMenuItemLabel *gameMainButton = CCMenuItemFont::create("Start", this, menu_selector(Tutorial::gameMainAction));
    
    CCMenu *menu = CCMenu::create(gameMainButton, NULL);
    //menu->setAnchorPoint(CCPoint(1.0, 0));
    menu->setPosition(ccp(visibleSize.width / 2, 70 ));
    menu->alignItemsHorizontally();
    
    this->addChild(menu, 2);
    
    CCGATracker::sendView("Tutorial");
    
    setTouchEnabled(true);
    
    this->schedule(schedule_selector(Tutorial::update));
    return true;
}

void Tutorial::gameMainAction(){
    //切り替え先のシーン
    CCScene *scene = GameMain::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

