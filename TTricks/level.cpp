#include "level.h"


Level::Level()
{
	tickTime = 700;
	levelNumber = 0;
}


//void Level::update(int linesCleared)
//{
//    if(linesCleared / 10 > levelNumber)
//    {
//        next();
//    }
//}

void Level::next()
{
    levelNumber += 1;
	updateTickTime();
}

int Level::getLevelNumber()
{
    return levelNumber;
}

int Level::getTickTime()
{
    return tickTime;
}

void Level::setLevelNumber(int entree) 
{
	levelNumber = entree;
	updateTickTime();
}

int Level::getScore(int lines)
{
	if(lines == 1)
	{
		return 40*(levelNumber + 1);
	}
	else if(lines == 2)
	{
		return 100*(levelNumber + 1);
	}
	else if(lines == 3)
	{
		return 300*(levelNumber + 1);
	}
	else if(lines > 3)
	{
		return 300*lines*(levelNumber + 1);
	}
    else
    {
        return 0;
    }
}

void Level::updateTickTime()
{
	tickTime = 1000 * (48 - (5 * levelNumber)) / 60;
}