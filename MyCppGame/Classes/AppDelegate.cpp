#include "AppDelegate.h"
#include "MenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::createWithRect("FlappyGame", Rect(0, 0, 320, 480));
		director->setOpenGLView(glview);
	}


	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(750, 1334, ResolutionPolicy::NO_BORDER);

	auto scene = MenuScene::createScene();
	director->runWithScene(scene);

	return true;
}


void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}
