#include"ScoreBoard.h"
USING_NS_CC;

bool ScoreBoard::init()
{
    auto colorLayer = LayerColor::create(Color4B::WHITE);
	colorLayer->setOpacity(80);
    colorLayer->setAnchorPoint(Point::ZERO);
    colorLayer->setPosition(Point::ZERO);
    colorLayer->setContentSize(Size(750, 1334));
    addChild(colorLayer);
    
    setAnchorPoint(Point::ZERO);
    setPosition(Point::ZERO);
    setContentSize(Size(750, 1334));
    
    int score = UserDefault::getInstance()->getIntegerForKey("Score");
    int highestScore = UserDefault::getInstance()->getIntegerForKey("Hscore");
    
    if(score > highestScore) {
        highestScore = score;
        UserDefault::getInstance()->setIntegerForKey("Hscore", highestScore);
        auto metal = Sprite::create("medal.png");
        metal->setScale(0.5);
        metal->setPosition(375, 200);
        metal->runAction(ScaleTo::create(1.5, 1));
        metal->runAction(RotateTo::create(1.5, 720));
        addChild(metal);
    }



    auto labelY = Label::createWithTTF("Your Survived:", "fonts/JOKERMAN.TTF", 90);
    labelY->setPosition(375, 1000);
    addChild(labelY);
    
    auto labelS = Label::createWithTTF(
                        StringUtils::format("%d", score), "fonts/JOKERMAN.TTF", 90);
    labelS->setPosition(375, 870);
    addChild(labelS);
    
    auto labelH = Label::createWithTTF("Highest Record:", "fonts/JOKERMAN.TTF", 70);
    labelH->setPosition(375, 650);
    addChild(labelH);
    
    auto labelHS = Label::createWithTTF(
                    StringUtils::format("%d", highestScore), "fonts/JOKERMAN.TTF", 70);
    labelHS->setPosition(375, 570);
    addChild(labelHS);

	auto tips1 = Label::createWithTTF("mouse to left: reset highscore", "fonts/arial.ttf", 40);
	tips1->setPosition(375, 290);
	tips1->setColor(Color3B::YELLOW);
	addChild(tips1);

	auto tips2 = Label::createWithTTF("mouse to right: return menu", "fonts/arial.ttf", 40);
	tips2->setPosition(375, 260);
	tips2->setColor(Color3B::YELLOW);
	addChild(tips2);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *t, Event *e){
        beginPX = t->getLocation().x;
        beginPY = t->getLocation().y;
        return true;
    };
  
    listener->onTouchEnded = [&](Touch *t, Event *e){   
        if(t->getLocation().x - beginPX > 400 && t->getLocation().y - beginPY < 100)
            Director::getInstance()->replaceScene(TransitionCrossFade::create(1, MenuScene::createScene()));
		else if (t->getLocation().x - beginPX < -400 && t->getLocation().y - beginPY < 100)
			UserDefault::getInstance()->setIntegerForKey("Hscore", 0);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}