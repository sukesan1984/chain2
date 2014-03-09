#include "GameMainScene.h"

USING_NS_CC;

CCScene* GameMain::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameMain *layer = GameMain::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->goneToGameOver = false;
    
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
                                        menu_selector(GameMain::test));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("panels.plist");
    
    
    Score::instance().reset();
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
    
    this->schedule(schedule_selector(GameMain::update));
    return true;
}


void GameMain::menuCloseCallback(CCObject* pSender)
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

void GameMain::ccTouchesBegan(CCSet* pTouches, CCEvent* event){
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

void GameMain::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
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

void GameMain::ccTouchesEnded(CCSet* pTouches, CCEvent* event){
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

void GameMain::update(float dt){
    field->update();
    hitNumLabel->setString(CCString::createWithFormat("Hits:%d",field->getHitNum())->getCString());
    scoreLabel->setString(CCString::createWithFormat("Score:%d",field->getScore())->getCString());
    totalRemovedNumLabel->setString(CCString::createWithFormat("Removed:%d", field->getTotalRemovedPanelsNum())->getCString());
    gauge->reduce(2000);
    if(gauge->isGameOver() && !this->field->hasRemovingPanels() && !this->field->isMoving()){
        this->setTouchEnabled(false);
        if(!goneToGameOver){
            goneToGameOver = true;
            this->gotoGameOverScene();
        }
    }
    passedframe++;
}

void GameMain::test(CCObject* pSender){
    field->test();
}

void GameMain::gotoGameOverScene(){
    //切り替え先のシーン
    CCScene *scene = GameOver::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}