#ifndef	GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>
#include <qlayout.h>
#include <Qpushbutton.h>
#include <Qlabel.h>
#include <Qdebug.h>

class GameOverWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameOverWindow(QWidget *parent = nullptr);
	~GameOverWindow();
public slots:
	void goToMainWindow();

private:
	QWidget *mainWindow;
	QWidget *gameOverWidget;
	QGridLayout *layoutGameOver;
	QGridLayout *layoutSlider;
	QPushButton *acceptButton;
};
#endif // GAMEOVERWINDOW_H
