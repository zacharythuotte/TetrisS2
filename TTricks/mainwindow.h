#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qdebug.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <QSoundEffect.h>
#include <qtoolbar.h>
#include <qstackedwidget.h>
#include <qsizepolicy.h> //Voir pour resizer les menus eventuellement
#include <qheaderview.h>
#include <qwindow.h>
#include <qapplication.h>
#include <qstylefactory.h>
#include <string>

#include "optionwindow.h"
#include "gamewindow.h"
#include "gameoverwindow.h"
#include "leaderboardwindow.h"
#include "leaderboard.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	string lastPlayerScore;
	Leaderboard *leaderboardScores;

public slots:
	void showOption();
	void showGame();
	void showGameOver();
	void showMainWindow();
	void showLeaderboard();
	void sendNewScore(string newName);
	void saveTempScore(int tempScore);

	void changeVolume();

private:
	const int BUTTON_MAX_WIDTH = 200; //Largeur maximale des boutons
	int lastScore;

	QWidget *centralWidget; //Le widget central de la fenetre de menu
	QStackedWidget *pagesStack; //Stack pour les pages du jeu (1 affichee a la fois)
	QVBoxLayout *layoutPrincipal; //
	QSoundEffect *musique; //
	QPushButton *startButton; //
	QPushButton *leaderboardButton; //
	QPushButton *exitButton; //
	QLabel *screenTitle; //
	QLabel *creditsLabel; //
	OptionWindow *optionPage; //
	GameWindow *gamePage; //
	GameOverWindow *gameOverPage; //
	LeaderboardWindow *leaderboardPage; //
	QToolBar *toolBar;
	QSlider *sliderVolume;
};
#endif // MAINWINDOW_H
