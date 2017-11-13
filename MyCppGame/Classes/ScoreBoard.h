#ifndef __SCOREBOARD__
#define __SCOREBOARD__

#include "cocos2d.h"
#include "Definition.h"
USING_NS_CC;

class ScoreBoard : public Layer
{
public:
	virtual bool init();
    CREATE_FUNC(ScoreBoard);
private:
    int beginPX = 0;
    int beginPY = 0;
};
#endif