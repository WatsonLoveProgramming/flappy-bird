#include "MenuScene.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MenuScene::init()
{
    if ( !Layer::init() )
        return false;
    
    auto backGround = Sprite::create("background.png");
    backGround->setAnchorPoint(Vec2::ZERO);
    backGround->setPosition(Vec2::ZERO);
    this->addChild(backGround);
    auto gameName = Label::createWithTTF("Flappy Oliver","fonts/JOKERMAN.TTF", 100);
    gameName->setPosition(375, 1100);
    this->addChild(gameName);

	auto playItem = MenuItemLabel::create(Label::createWithTTF("PLAY", "fonts/JOKERMAN.TTF", 60), 
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	auto helpItem = MenuItemLabel::create(Label::createWithTTF("HELP", "fonts/JOKERMAN.TTF", 60),
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	auto moreItem = MenuItemLabel::create(Label::createWithTTF("MORE", "fonts/JOKERMAN.TTF", 60),
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

    playItem->setPosition(375, 900);
    helpItem->setPosition(375, 700);
    moreItem->setPosition(375, 500);	
    playItem->setColor(Color3B::RED);
    helpItem->setColor(Color3B::YELLOW);
    moreItem->setColor(Color3B::BLUE);
    playItem->setTag(1);
    helpItem->setTag(2);
    moreItem->setTag(3);

    auto menu = Menu::create(playItem, helpItem, moreItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    return true;
}

void MenuScene::menuCloseCallback(cocos2d::Ref* pSender){
//    auto nowItem = (MenuItem*)pSender;
    //gameScene = TransitionCrossFade::create(0, GameScene::createScene());
    gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(gameScene);
//    switch (nowItem->getTag()){
//        case 1:
//            
//            break;
//        case 2:
//            break;
//        case 3:
//            break;
//    }
}
