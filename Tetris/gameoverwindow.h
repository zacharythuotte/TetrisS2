#ifndef	GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>
#include <qlayout.h>
#include <Qpushbutton.h>
#include <Qlabel.h>
#include <qlineedit.h>
#include <iostream>
#include <string>

//#include "MainWindow.h"

using namespace std;

class GameOverWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameOverWindow(QWidget *parent = nullptr);
	~GameOverWindow();
	void setGameScore(int imputScore);

public slots:
	void verifyName();
	void closeGameOver();

signals:
	void endGameOver(string pName);

private:
	int gameScore;

	QWidget *mainWindow;
	QWidget *gameOverWidget;
	QLabel *gameOverLabel;
	QLabel *gameScoreLabel;
	QLabel *instructionLabel;
	QLineEdit *nameEdit;
	QVBoxLayout *layoutGameOver;
	QPushButton *acceptButton;
	string playerName;

	QLabel *createLabel(const QString &text);
};
#endif // GAMEOVERWINDOW_H
