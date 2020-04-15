#ifndef	OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QMainWindow.h>
#include <qlayout.h>
#include <Qpushbutton.h>
#include <Qlabel.h>
#include <QSound.h>
#include <QSlider.h>
#include <qpalette.h>
#include <qapplication.h>

class OptionWindow : public QMainWindow
{
	Q_OBJECT

public:
	OptionWindow(QWidget *parent = nullptr);
	~OptionWindow();
	int startDifficulty; //Vitesse entre 1000 (lent) et 100 (rapide)
	int startLevel; //Niveau entre 0 (lent) et 9 (rapide)

	int difficultyToLevel(int d);
	int levelToDifficulty(int l);

public slots:
	void changeSpeed();

private:
	const int BUTTON_MAX_WIDTH = 200;

	QWidget *optionWidget; //widget central
	QWidget *sliderWidget; //Widget pour le groupe de widgets relies au slider
	QGridLayout *layoutOption; //layout principal d options
	QGridLayout *layoutSlider; //layout des widgets relies au slider
	QPushButton *returnButton;
	QPushButton *acceptButton;
	QSlider *sliderSpeed;
	QLabel *labelSliderTitle;
	QLabel *labelSliderSpeed;
	QLabel *labelInstructions;
};
#endif // MAINWINDOW_H
