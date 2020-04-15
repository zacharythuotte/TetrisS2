#ifndef	LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <QMainWindow>
#include <qlayout.h>
#include <Qpushbutton.h>
#include <Qlabel.h>
#include <QTableWidget>
#include <qheaderview.h>
#include <qsizepolicy.h>

#include "leaderboard.h"

using namespace std;

class LeaderboardWindow : public QMainWindow
{
	Q_OBJECT

public:
	LeaderboardWindow(QWidget *parent = nullptr);
	~LeaderboardWindow();
	void setLeaderboard(Leaderboard iLeaderboard);

public slots:

private:
	QWidget *leaderboardWidget;
	QVBoxLayout *layoutLeaderboard;
	QTableWidget *tableLeaderboard;
	QLabel * titleLabel;
	QPushButton *acceptButton;
	QLabel *createLabel(const QString &text);
};
#endif // LEADERBOARDWINDOW_H
