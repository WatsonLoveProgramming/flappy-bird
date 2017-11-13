#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "Definition.h"
USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MenuScene);
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
private:
    Scene* gameScene;
};

#endif // __MENU_SCENE_H__
