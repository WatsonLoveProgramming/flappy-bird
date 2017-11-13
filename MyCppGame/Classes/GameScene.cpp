#include"GameScene.h"
using namespace CocosDenshion;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();
	scene->addChild(layer);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -2000));
	//Zhe Zhao --- mask
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;
    
    //Contact Listener
    auto contact = EventListenerPhysicsContact::create();
    contact->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);
    
    //Touch Listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //Schedule Update
    this->schedule(schedule_selector(GameScene::moveBackground), 0.01, -1, 0.05);
    this->schedule(schedule_selector(GameScene::generatePipe), 1.7);
    this->scheduleOnce(schedule_selector(GameScene::initFlappyObj), 0.02);
    this->scheduleUpdate();
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.25);
    SimpleAudioEngine::getInstance()->preloadEffect("haha.mp3");
    SimpleAudioEngine::getInstance()->setEffectsVolume(1);
    SimpleAudioEngine::getInstance()->preloadEffect("due.mp3");
    
    initBackground();
    
	return true;
}

void GameScene::initBackground()
{
    //Edge Box
    auto edgeUpper = Sprite::create();
	this->addChild(edgeUpper, 20);
    auto edgeBodyUpperBound = PhysicsBody::createEdgeSegment(Vec2(0, 1334), Vec2(750, 1334));
	edgeBodyUpperBound->setDynamic(false);
	edgeUpper->setPhysicsBody(edgeBodyUpperBound);

	auto edgeLower = Sprite::create();
	this->addChild(edgeLower, 20);
	auto edgeBodyLowerBound = PhysicsBody::createEdgeSegment(Vec2(0, 0), Vec2(750, 0));
	edgeBodyLowerBound->setDynamic(false);
	edgeBodyLowerBound->setContactTestBitmask(0x0001);
	edgeLower->setPhysicsBody(edgeBodyLowerBound);

    //Setup Background Rolling
    auto backGround = Sprite::create("background.png");
    backGround->setPosition(Point::ZERO);
    backGround->setAnchorPoint(Point::ZERO);
    this->addChild(backGround, 0);
    backGround->setTag(10);
    
    auto backGround2 = Sprite::create("background.png");
    backGround2->setPosition(Point::ZERO);
    backGround2->setAnchorPoint(Point::ZERO);
    this->addChild(backGround2, 0);
    backGround2->setTag(11);
}

void GameScene::initFlappyObj(float t)
{

	obj = Sprite::create();
	Vector<SpriteFrame*> allframe;  
	for (int i = 0; i < 9; i++){
		SpriteFrame * sf = SpriteFrame::create("bird2.png", Rect(i * 100, 0, 100, 100));
		allframe.pushBack(sf);
	}
	Animation * ani = Animation::createWithSpriteFrames(allframe, .5); 
	obj->runAction(RepeatForever::create(Animate::create(ani)));

    obj->setPosition(Vec2(200,600));
    obj->setScale(1);
    this->addChild(obj, 20);
    
	body = PhysicsBody::createCircle(45);
    body->setMass(500);
    body->setEnable(false);
    body->setContactTestBitmask(0x1111);
    obj->setPhysicsBody(body);
    
    scoreLabel = Label::createWithTTF("Score: 0", "fonts/JOKERMAN.TTF", 40);
	scoreLabel->setPosition(visibleSize.width - 100, visibleSize.height - 14);
    this->addChild(scoreLabel, 20);
}

void GameScene::moveBackground(float t)
{
	auto background = this->getChildByTag(10);
	auto background2 = this->getChildByTag(11);

	background->setPositionX(background->getPositionX() - 1);
    background2->setPositionX(background->getPositionX() + 750);
    
    if (background->getPositionX() < -750)
        background->setPositionX(0);
    
	for (int i = 0; i < pipes.size(); i++){
        //Move the pipe
		pipes.at(i)->setPositionX(pipes.at(i)->getPositionX() - 3);
        
        //take one score and play sound while pipe over bird
		if (obj->getPositionX() - pipes.at(i)->getPositionX() < 3
			&& obj->getPositionX() - pipes.at(i)->getPositionX() >= 0) {
            score++;
            scoreLabel->setString(StringUtils::format("Score: %d", score));
            SimpleAudioEngine::getInstance()->playEffect("haha.mp3");
        }

        //Remove and clean up every outbounded pipe
		if (pipes.at(i)->getPositionX() < -750) {
			pipes.eraseObject(pipes.at(i));
			pipes.at(i)->removeFromParentAndCleanup(true);
        }
    }
}

void GameScene::generatePipe(float t)
{
    if(!enable)
        return;
    
    auto pipe = Sprite::create("pipe.png");
    pipe->setScaleX(0.8);
    pipe->setAnchorPoint(Vec2::ZERO);
	pipe->setPosition(750, -rand() % 660);
    this->addChild(pipe);
    pipes.pushBack(pipe);
    
    auto physicBody = PhysicsBody::create();
    physicBody->setDynamic(false);
    auto phyTop = PhysicsShapeBox::create(Size(145, 767), PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2(0, 610));
    phyTop->setContactTestBitmask(0x0010);
    auto phyBottom = PhysicsShapeBox::create(Size(145, 767), PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2(0, -610));
    phyBottom->setContactTestBitmask(0x0010);
    physicBody->addShape(phyTop);
    physicBody->addShape(phyBottom);
    pipe->setPhysicsBody(physicBody);
}

bool GameScene::onContactBegin(const PhysicsContact& contact)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    pause();
    UserDefault::getInstance()->setIntegerForKey("Score", score);
    auto layer = ScoreBoard::create();
    getScene()->addChild(layer, 30);
    
    return true;
}

void GameScene::update(float t)
{
    if(!enable)
        return;
    
    //If body is not enabled then do not change the posture
    if(!body->isEnabled())
        return;
    
    //Create the speed limit when jumping upward, realse the limit when falling
    //Create the rotation of the bird. Should rotate from +60 degrees to -60 degrees
    if(body->getVelocity().y > 100) {
        body->setVelocityLimit(800);
        if(body->getRotation() > -60)
            body->getNode()->setRotation(body->getNode()->getRotation()-10);
    }
    else {
        body->setVelocityLimit(INFINITY);
        if(body->getRotation() < 60)
            body->getNode()->setRotation(body->getNode()->getRotation()+5);
    }
}

bool GameScene::onTouchDown(Touch* touch, Event *event)
{
    SimpleAudioEngine::getInstance()->playEffect("due.mp3");
    
    if(body == NULL)
        return false;
    
    if(!enable) {
        enable = true;
        body->setEnable(true);
    }
    
    if(body->getVelocity().y < 0)
        body->applyImpulse(Vec2(0, 1500000));
    else
        body->applyImpulse(Vec2(0, 500000));
    
    return true;
}
