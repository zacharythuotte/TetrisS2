#ifndef	LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <QMainWindow>
#include <qlayout.h>
#include <Qpushbutton.h>
#include <Qlabel.h>
#include <qtablewidget.h>

class LeaderboardWindow : public QMainWindow
{
	Q_OBJECT

public:
	LeaderboardWindow(QWidget *parent = nullptr);
	~LeaderboardWindow();
public slots:
	void goToMainWindow();

private:
	QWidget *leaderboardWidget;
	QGridLayout *layoutLeaderboard;
	QTableWidget *tableLeaderboard;
	QPushButton *acceptButton;
};
#endif // LEADERBOARDWINDOW_H
