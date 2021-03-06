#include "GameMainScene.h"
#include "CCGATracker.h"

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

    CCLayerColor *background = CCLayerColor::create(ccc4(255, 255 , 255, 255));
    background->setAnchorPoint(CCPoint(0.5,0.5));
    background->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
    //background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    background->setPosition(ccp(0, 0));
    this->addChild(background);
    
    
    Score::instance().reset();
    PanelTime::instance().reset();
    this->field = new Field();
    field->initialize();
    field->setPosition(CCPoint(FIELD_OFFSET_X, FIELD_OFFSET_Y));
    field->setAnchorPoint(CCPoint(0, 0));
    this->addChild(field);
    
    hitNumLabel = CCLabelTTF::create(CCString::createWithFormat("HITS:%d",field->getHitNum())->getCString(), MISAKI_FONT, 20);
    hitNumLabel->setColor(ccBLACK);
    hitNumLabel->setAnchorPoint(CCPoint(0, 1.0));
    hitNumLabel->setPosition(CCPoint(0, visibleSize.height - 20));
    this->addChild(hitNumLabel);
    
    scoreLabel = CCLabelTTF::create(CCString::createWithFormat("SCORE:%d", field->getScore())->getCString(), MISAKI_FONT, 20);
    scoreLabel->setColor(ccBLACK);
    scoreLabel->setAnchorPoint(CCPoint(1.0, 1.0));
    scoreLabel->setPosition(CCPoint(visibleSize.width,visibleSize.height - 20));
    this->addChild(scoreLabel);
    
    levelLabel = CCLabelTTF::create(CCString::createWithFormat("LEVEL:%d", 1)->getCString(), MISAKI_FONT, 20);
    levelLabel->setAnchorPoint(CCPoint(0.5, 1.0));
    levelLabel->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height));
    levelLabel->setColor(ccBLACK);
    this->addChild(levelLabel);
    
    gauge = Gauge::createGauge();
    gauge->setAnchorPoint(CCPoint(0, 1.0));
    gauge->setPosition(CCPoint(0, visibleSize.height - 40));
    gauge->setScaleX(visibleSize.width / 640);
    gauge->setScaleY(visibleSize.width / 640);
    this->addChild(gauge, 2);
    this->field->setGauge(gauge);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    setTouchEnabled(true);
    
    CCGATracker::sendView("GameMain");
    
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
            this->field->onTouchBegan(loc - CCPoint(FIELD_OFFSET_X, FIELD_OFFSET_Y));
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
            this->field->onTouchMove(loc - CCPoint(FIELD_OFFSET_X, FIELD_OFFSET_Y));
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
    hitNumLabel->setString(CCString::createWithFormat("HITS:%d",field->getHitNum())->getCString());
    scoreLabel->setString(CCString::createWithFormat("SCORE:%d",field->getScore())->getCString());
    levelLabel->setString(CCString::createWithFormat("LEVEL:%d", int(field->getTotalRemovedPanelsNum() / SPEED_UP_PANEL_NUM) + 1)->getCString());
    if(beforeTotalRemovedNum + SPEED_UP_PANEL_NUM < field->getTotalRemovedPanelsNum()){
        PanelTime::instance().speedUp();
        beforeTotalRemovedNum = field->getTotalRemovedPanelsNum();
    }
    gauge->reduce();
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