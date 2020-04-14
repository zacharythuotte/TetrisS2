#include "leaderboardwindow.h"
//#include "MainWindow.h"

LeaderboardWindow::LeaderboardWindow(QWidget *parent) : QMainWindow(parent)
{
	leaderboardWidget = new QWidget();

	//LAYOUT PRINCIPAL
	layoutLeaderboard = new QVBoxLayout();

	//TITRE FENETRE
	titleLabel = createLabel("Meilleurs Scores");
	titleLabel->setFixedSize(350, 100);
	//titleLabel->setMaximumSize(350, 100);
	titleLabel->setAlignment(Qt::AlignCenter);
	//layoutLeaderboard->setAlignment()

	layoutLeaderboard->addWidget(titleLabel); // , Qt::AlignHCenter);
	layoutLeaderboard->setAlignment(titleLabel, Qt::AlignCenter);

	//GRILLE MEILLEURS SCORES
	tableLeaderboard = new QTableWidget();
	tableLeaderboard->setRowCount(10);
	tableLeaderboard->setColumnCount(2);
	tableLeaderboard->horizontalHeader()->setVisible(false);
	tableLeaderboard->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableLeaderboard->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableLeaderboard->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableLeaderboard->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	tableLeaderboard->setFixedSize(1000, 600);
	
	//tableLeaderboard->setMaximumSize(600, 600);
	//tableLeaderboard->setItem(0, 0, new QTableWidgetItem("Hello"));
	tableLeaderboard->setShowGrid(true);
	layoutLeaderboard->addWidget(tableLeaderboard);
	layoutLeaderboard->setAlignment(tableLeaderboard, Qt::AlignCenter);

	//MainWindow mWindow = parent;

	//BOUTON ACCEPTER
	acceptButton = new QPushButton("Accepter");
	acceptButton->setFixedWidth(200);
	QObject::connect(acceptButton, SIGNAL(clicked()), parent, SLOT(showMainWindow()));
	
	layoutLeaderboard->addWidget(acceptButton);
	layoutLeaderboard->setAlignment(acceptButton, Qt::AlignCenter);

	//PLACEMENT LAYOUT PRINCIPAL
	leaderboardWidget->setLayout(layoutLeaderboard);
	setCentralWidget(leaderboardWidget);
}

LeaderboardWindow::~LeaderboardWindow()
{
	delete acceptButton;
	delete layoutLeaderboard;
}

//Fonction pour changer les scores affiches dans le tableau (QTableWidget)
void LeaderboardWindow::setLeaderboard(Leaderboard iLeaderboard)
{
	for (int i = 0; i < iLeaderboard.highScores.size(); i++)
	{
		if (i >= tableLeaderboard->rowCount())
		{
			tableLeaderboard->setRowCount(tableLeaderboard->rowCount() + 1);
		}

		tableLeaderboard->setCellWidget(i, 0, createLabel(QString::fromStdString(iLeaderboard.highScores[i].playerName)));
		tableLeaderboard->setCellWidget(i, 1, createLabel(QString::number(iLeaderboard.highScores[i].nbPoints)));
	}
}

//CREER LABEL
QLabel *LeaderboardWindow::createLabel(const QString &text)
{
	QLabel *label = new QLabel(text);
	label->setFrameStyle(QFrame::Box | QFrame::Raised);
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("QLabel { background-color : white; color : black; font: 20pt; }");
	label->setMaximumHeight(50);
	return label;
}
