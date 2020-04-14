//#include "leaderboard.h"
//
//using namespace std;
//
//Leaderboard::Leaderboard()
//{
//
//}
//
//Leaderboard::~Leaderboard()
//{
//}
//
//void Leaderboard::addScore(string name, int score)
//{
//	//int i = 0;
//	//while (i > highScores[i].nbPoints && i < highScores.size)
//	//{
//	//	i++;
//	//}
//
//	struct ComboScore newScore = { name, score };
//	//cout << highScores;
//	highScores.push_back(newScore);
//
//	sort(highScores.begin(), highScores.end(), compareScore);
//}
//
////Pour sauvegarder les scores dans un fichier .txt
//void Leaderboard::saveToFile()
//{
//	ofstream output("Meilleurs_Scores.txt");
//
//	for (int i = 0; i < highScores.size; i++)
//	{
//		output << highScores[i].playerName << " " << highScores[i].nbPoints;
//	}
//
//	output.close();
//}
//
////Pour recuperer les scores du fichier .txt
//void Leaderboard::loadFromFile()
//{
//	ofstream output("Meilleurs_Scores.txt");
//
//	for (int i = 0; i < highScores.size; i++)
//	{
//		output << highScores[i].playerName << " " << highScores[i].nbPoints;
//	}
//
//	output.close();
//}