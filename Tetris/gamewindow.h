#ifndef	GAMEWINDOW_H
#define GAMEWINDOW_H


#include <qlayout.h>
#include <QPushbutton.h>
#include <qlabel.h>
#include <QLCDNumber>
#include <qframe.h>
#include <chrono>
#include <iostream>

#include "game.h"

using namespace std;

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameWindow(QWidget *parent = nullptr);
	~GameWindow(); 
	void setLvl(int lvlOpt) {  lvl = lvlOpt; };
	QLabel *createLabel(const QString &text);
	Game *jeu = new Game();
	bool isClosed = false;
	void start();
public slots:

	void pause();
	void continuer();
	void menu();
private:
	int lvl = 0;
	QWidget *gameWidget;
	QLabel *labelProchaineForme;
	QGridLayout *GPLayout;
	QLCDNumber *scoreLcd;
	QLCDNumber *niveauLcd;
	QLCDNumber *lignesLcd;
	QPushButton *BoutonPause;
	QPushButton *BoutonContinuer;
	QPushButton *BoutonMenu;
	
};
#endif // MAINWINDOW_H
