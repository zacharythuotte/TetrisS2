#ifndef	GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>
#include <qlayout.h>
#include <Qpushbutton.h>
#include <Qlabel.h>
#include <qlineedit.h>
#include <iostream>
#include <string>

class GameOverWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameOverWindow(QWidget *parent = nullptr);
	~GameOverWindow();
public slots:
	void verifyName();
	void closeGameOver();

private:
	QWidget *mainWindow;
	QWidget *gameOverWidget;
	QLabel *gameOverLabel;
	QLineEdit *nameEdit;
	QVBoxLayout *layoutGameOver;
	QPushButton *acceptButton;
};
#endif // GAMEOVERWINDOW_H
