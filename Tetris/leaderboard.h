#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

using namespace std;

struct ComboScore
{
	std::string playerName;
	int nbPoints;

	bool operator < (const ComboScore& a) const 
	{
		return nbPoints > a.nbPoints;
	}
};

class Leaderboard
{
    public:
		Leaderboard();

		void addScore(string n, int nb);
		void saveToFile();
		void loadFromFile();

		vector<ComboScore> highScores;

    private:
};

#endif