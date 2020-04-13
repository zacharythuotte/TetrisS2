#include "leaderboardwindow.h"
#include "MainWindow.h"

LeaderboardWindow::LeaderboardWindow(QWidget *parent) : QMainWindow(parent)
{
	leaderboardWidget = new QWidget();

	//LAYOUT PRINCIPAL
	layoutLeaderboard = new QGridLayout();

	//BACKGROUND DE LINTERFACE
	/*QPixmap bkgnd("./Image/Background.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);*/

	//GRILLE MEILLEURS SCORES
	tableLeaderboard = new QTableWidget();
	tableLeaderboard->setRowCount(10);
	tableLeaderboard->setColumnCount(2);
	tableLeaderboard->setEditTriggers(QAbstractItemView::NoEditTriggers);

	tableLeaderboard->horizontalHeader()->setVisible(false);
	tableLeaderboard->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableLeaderboard->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	
	tableLeaderboard->setMaximumSize(600, 600);
	tableLeaderboard->setItem(0, 0, new QTableWidgetItem("Hello"));
	tableLeaderboard->setShowGrid(true);
	layoutLeaderboard->addWidget(tableLeaderboard);

	//BOUTON ACCEPTER
	acceptButton = new QPushButton("Accepter");
	QObject::connect(acceptButton, SIGNAL(clicked()), parent, SLOT(showMainWindow()));

	//PLACEMENT LAYOUT PRINCIPAL
	layoutLeaderboard->addWidget(acceptButton);

	leaderboardWidget->setLayout(layoutLeaderboard);
	setCentralWidget(leaderboardWidget);
}

LeaderboardWindow::~LeaderboardWindow()
{
	delete acceptButton;
	delete layoutLeaderboard;
}

void LeaderboardWindow::goToMainWindow()
{
	this->hide();
}

