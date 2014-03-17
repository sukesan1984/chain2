#include "TutorialScene.h"
#include "CCGATracker.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

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
    
    CCLayerColor *background = CCLayerColor::create(ccc4(255, 255 , 255, 255));
    background->setAnchorPoint(CCPoint(0.5,0.5));
    background->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
    //background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    background->setPosition(ccp(0, 0));
    this->addChild(background);
    
    CCLabelTTF* title = CCLabelTTF::create("遊び方", MISAKI_FONT, 40);
    title->setAnchorPoint(ccp(0.5, 1.0));
    title->setPosition(ccp(visibleSize.width / 2, visibleSize.height -20));
    title->setColor(ccBLACK);
    this->addChild(title);
    
    CCSprite* tutorial = CCSprite::createWithSpriteFrameName("tutorial.png");
    tutorial->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    //visibleSize.width * tutorial->getContentSize().width / 640;
    // 600
    tutorial->setScale(visibleSize.width / 640);
    
    this->addChild(tutorial);
    
    CCMenuItemFont* gameMainFont = CCMenuItemFont::create("START", this, menu_selector(GameOver::gameMainAction));
    gameMainFont->setFontNameObj(MISAKI_FONT);
    CCMenuItemLabel *gameMainButton = gameMainFont;
    gameMainButton->setColor(ccBLACK);
    
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
    SimpleAudioEngine::sharedEngine()->playEffect("menu.wav");
    //切り替え先のシーン
    CCScene *scene = GameMain::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

