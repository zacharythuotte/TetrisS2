#include "leaderboard.h"

Leaderboard::Leaderboard()
{
	loadFromFile();
}

//Pour ajouter un nouveau ComboScore au vecteur
void Leaderboard::addScore(string name, int score)
{
	struct ComboScore newScore = { name, score };
	//cout << highScores;
	highScores.push_back(newScore);

	std::sort(highScores.begin(), highScores.end());

	saveToFile();
}

////Comparateur pour le vecteur des ComboScore s
//bool compareScore(const ComboScore &a, const ComboScore &b)
//{
//	return a.nbPoints < b.nbPoints;
//}

//Pour sauvegarder les scores dans un fichier .txt
void Leaderboard::saveToFile()
{
	ofstream output("Meilleurs_Scores.log");

	if (output.is_open())
	{
		for (int i = 0; i < highScores.size(); i++)
		{
			output << highScores[i].playerName << "\n";;
			output << highScores[i].nbPoints << "\n";
		}

		output.close();
	}
}

//Pour recuperer les scores du fichier .log
void Leaderboard::loadFromFile()
{
	ifstream imput("Meilleurs_Scores.log");

	if (imput.is_open())
	{
		string line;
		ComboScore tempComboScore;

		while (getline(imput, line))
		{
			cout << line;
			tempComboScore.playerName = line;
			getline(imput, line);
			cout << line;

			istringstream(line) >> tempComboScore.nbPoints;
			//tempComboScore.nbPoints = stoi(line);

			highScores.push_back(tempComboScore);
		}
		cout << "Chargement des meilleurs scores reussi a partir du fichier existant";
		imput.close();
	}
}