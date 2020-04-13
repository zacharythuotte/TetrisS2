#include "gamewindow.h"
GameWindow::GameWindow(QWidget *parent)
	: QMainWindow(parent), jeu(new Game)
{

	//LAYOUT PRINCIPAL
	GPLayout = new QGridLayout;
	
	////BACKGROUND DE LINTERFACE
	//QPixmap bkgnd("./Image/Background.jpg");
	//bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	//QPalette palette;
	//palette.setBrush(QPalette::Background, bkgnd);
	//this->setPalette(palette);

	//INITIALISATION DU JEU
	labelProchaineForme = new QLabel;
	jeu->setLabelProchaineForme(labelProchaineForme);
	jeu->setFocusPolicy(Qt::StrongFocus);
	jeu->repaint();

	//connect et definition des widgets
	gameWidget = new QWidget;

	scoreLcd = new QLCDNumber();
	scoreLcd->display(0);
	connect(jeu, &Game::scoreChange, scoreLcd, QOverload<int>::of(&QLCDNumber::display));

	niveauLcd = new QLCDNumber();
	niveauLcd->display(jeu->level.getLevelNumber());
	connect(jeu, &Game::levelChange, niveauLcd, QOverload<int>::of(&QLCDNumber::display));

	lignesLcd = new QLCDNumber();
	lignesLcd->display(0);
	connect(jeu, &Game::linesChange, lignesLcd, QOverload<int>::of(&QLCDNumber::display));

	BoutonPause = new QPushButton("&Pause");
	connect(BoutonPause, &QPushButton::clicked, this, &GameWindow::pause);
	BoutonPause->setFocusPolicy(Qt::NoFocus);

	BoutonContinuer = new QPushButton("&Continuer");
	connect(BoutonContinuer, &QPushButton::clicked, this, &GameWindow::continuer);
	BoutonContinuer->setFocusPolicy(Qt::NoFocus);

	BoutonMenu = new QPushButton("&Menu");
	connect(BoutonMenu, &QPushButton::clicked, this, &GameWindow::menu);
	BoutonMenu->setFocusPolicy(Qt::NoFocus);

	//PLACEMENT LAYOUT PRINCIPAL
	GPLayout->addWidget(createLabel(tr("Prochaine Forme:")), 0, 0);
	GPLayout->addWidget(labelProchaineForme, 1, 0);
	GPLayout->addWidget(createLabel(tr("Score:")), 0, 2);
	GPLayout->addWidget(scoreLcd, 1, 2);
	GPLayout->addWidget(createLabel(tr("Niveau:")), 2, 0);
	GPLayout->addWidget(niveauLcd, 3, 0);
	GPLayout->addWidget(createLabel(tr("Lignes completes:")), 2, 2);
	GPLayout->addWidget(jeu, 0, 1, 6, 1);
	GPLayout->addWidget(lignesLcd, 3, 2);
	GPLayout->addWidget(BoutonPause, 5, 2);
	GPLayout->addWidget(BoutonContinuer, 4, 0);
	GPLayout->addWidget(BoutonMenu, 4, 2);

	gameWidget->setLayout(GPLayout);
	setCentralWidget(gameWidget);
	resize(825, 555);
}
void GameWindow::start()
{
	jeu->setLevel(lvl);
	jeu->loop();
}

void GameWindow::pause()
{
	jeu->pause = true;
};
void GameWindow::continuer()
{
	jeu->pause = false;
	start();
};
void GameWindow::menu()
{
	if (jeu->pause == true || jeu->alive == false)
	{
		this->hide();
		isClosed = true;
	}
};

//CREER LABEL
QLabel *GameWindow::createLabel(const QString &text)
{
	QLabel *label = new QLabel(text);
	label->setFrameStyle(QFrame::Box | QFrame::Raised);
	label->setStyleSheet("QLabel { background-color : white; color : black; font: 13pt; }");
	return label;
}


GameWindow::~GameWindow()
{	
	delete GPLayout;
	delete gameWidget;
}

