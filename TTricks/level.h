#include <math.h>
class Level
{

    public:
        Level();
        void next();
        //void update(int linesCleared);
        int getLevelNumber();
        int getTickTime();
        int getScore(int lines);
		void setLevelNumber(int entree);
		void updateTickTime();
   private:
        int levelNumber;
        int tickTime;
        
};