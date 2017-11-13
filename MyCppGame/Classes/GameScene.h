#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"
#include "Definition.h"

USING_NS_CC;
class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
    CREATE_FUNC(GameScene);
    
    bool onTouchDown(Touch* touch, Event *event);
    bool onContactBegin(const PhysicsContact& contact);
    
    void initBackground();
	void moveBackground(float t);
    void initFlappyObj(float t);
    void generatePipe(float t);
    void update(float t);
    
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    bool enable = false;
    int score = 0;
    Sprite* obj = NULL;
    PhysicsBody* body = NULL;
    Label* scoreLabel;
    Vector<Sprite*> pipes;
};
#endif