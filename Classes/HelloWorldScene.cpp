#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::test));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("panels.plist");
    
    
    this->field = new Field();
    field->initialize();
    field->setPosition(FIELD_START_AT);
    field->setAnchorPoint(CCPoint(0, 0));
    this->addChild(field);
    
    hitNumLabel = CCLabelTTF::create(CCString::createWithFormat("Hits:%d",field->getHitNum())->getCString(), "arial", 20);
    hitNumLabel->setAnchorPoint(CCPoint(0, 0));
    hitNumLabel->setPosition(CCPoint(visibleSize.width - 200, 80));
    this->addChild(hitNumLabel);
    
    scoreLabel = CCLabelTTF::create(CCString::createWithFormat("Score:%d", field->getScore())->getCString(), "arial", 20);
    scoreLabel->setAnchorPoint(CCPoint(0, 0));
    scoreLabel->setPosition(CCPoint(visibleSize.width - 200, 60));
    this->addChild(scoreLabel);
    
    totalRemovedNumLabel = CCLabelTTF::create(CCString::createWithFormat("Removed:%d", field->getTotalRemovedPanelsNum())->getCString(), "arial", 20);
    totalRemovedNumLabel->setAnchorPoint(CCPoint(0, 0));
    totalRemovedNumLabel->setPosition(CCPoint(visibleSize.width - 200, 40));
    this->addChild(totalRemovedNumLabel);
    
    gauge = Gauge::createGauge();
    gauge->setAnchorPoint(CCPoint(0, 0));
    gauge->setPosition(CCPoint(0, visibleSize.height - 60));
    gauge->setScaleX(visibleSize.width / 640);
    gauge->setScaleY(visibleSize.width / 640);
    this->addChild(gauge, 2);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    setTouchEnabled(true);
    
    this->schedule(schedule_selector(HelloWorld::update));
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;
    
    CCPoint loc;
    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            loc = touch->getLocation();
            this->field->onTouchBegan(loc - FIELD_START_AT);
        }
    }
}

void HelloWorld::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;
    
    CCPoint loc;
    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            loc = touch->getLocation();
            this->field->onTouchMove(loc - FIELD_START_AT);
        }
    }
}

void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;
    
    CCPoint loc;
    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            loc = touch->getLocation();
        }
    }
}

void HelloWorld::update(float dt){
    field->update();
    hitNumLabel->setString(CCString::createWithFormat("Hits:%d",field->getHitNum())->getCString());
    scoreLabel->setString(CCString::createWithFormat("Score:%d",field->getScore())->getCString());
    totalRemovedNumLabel->setString(CCString::createWithFormat("Removed:%d", field->getTotalRemovedPanelsNum())->getCString());
    gauge->reduce(500);
    passedframe++;
}


void HelloWorld::test(CCObject* pSender){
    field->test();
}