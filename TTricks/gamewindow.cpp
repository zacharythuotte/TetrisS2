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
	jeu->setBaseSize(100, 240);
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

	BoutonPlay = new QPushButton("&Play");
	connect(BoutonPlay, &QPushButton::clicked, this, &GameWindow::play);
	BoutonPlay->setFocusPolicy(Qt::NoFocus);

	BoutonMenu = new QPushButton("&Retour menu principal");
	QObject::connect(BoutonMenu, SIGNAL(clicked()), parent, SLOT(showMainWindow()));
	BoutonMenu->setFocusPolicy(Qt::NoFocus);

	BoutonContinuer = new QPushButton("&Continuer");
	BoutonContinuer->setStyleSheet("QPushButton {background-color : rgb(0, 255, 0)}");
	QObject::connect(BoutonContinuer, SIGNAL(clicked()), parent, SLOT(showGameOver()));
	BoutonMenu->setFocusPolicy(Qt::NoFocus);
	BoutonContinuer->hide();

	QObject::connect(jeu, SIGNAL(death()), this, SLOT(endGame()));

	//PLACEMENT LAYOUT PRINCIPAL
	GPLayout->addWidget(createLabel(tr("Prochaine Forme:")), 0, 0);
	GPLayout->addWidget(labelProchaineForme, 1, 0);
	GPLayout->addWidget(createLabel(tr("Score:")), 0, 2);
	GPLayout->addWidget(scoreLcd, 1, 2);
	GPLayout->addWidget(createLabel(tr("Niveau:")), 2, 0);
	GPLayout->addWidget(niveauLcd, 3, 0);
	GPLayout->addWidget(createLabel(tr("Lignes completes:")), 2, 2);

	GPLayout->addWidget(jeu, 0, 1, 6, 1); //,Qt::AlignHCenter);
	GPLayout->addWidget(lignesLcd, 3, 2);
	GPLayout->addWidget(BoutonPause, 5, 0);
	GPLayout->addWidget(BoutonPlay, 4, 0);
	GPLayout->addWidget(BoutonMenu, 4, 2);
	GPLayout->addWidget(BoutonContinuer, 5, 2);

	//POUR ESSAYER DE CENTRE LA SURFACE DE JEU
	//QVBoxLayout *LLayout = new QVBoxLayout();
	//LLayout->addWidget(createLabel(tr("Prochaine Forme:")));
	//LLayout->addWidget(labelProchaineForme);
	//LLayout->addWidget(createLabel(tr("Niveau:")), 2, 0);
	//LLayout->addWidget(niveauLcd);
	//LLayout->addWidget(BoutonPause);
	//LLayout->addWidget(BoutonPlay);
	//QWidget *LWidget = new QWidget();
	//LWidget->setLayout(LLayout);

	//QVBoxLayout *MLayout = new QVBoxLayout();
	//MLayout->addWidget(jeu, Qt::AlignCenter); //,Qt::AlignHCenter);
	//QWidget *MWidget = new QWidget();
	//MWidget->setLayout(MLayout);

	//QVBoxLayout *RLayout = new QVBoxLayout();
	//RLayout->addWidget(createLabel(tr("Score:")));
	//RLayout->addWidget(scoreLcd);
	//RLayout->addWidget(createLabel(tr("Lignes completes:")));
	//RLayout->addWidget(lignesLcd);
	//RLayout->addWidget(BoutonMenu);
	//RLayout->addWidget(BoutonContinuer);
	//QWidget *RWidget = new QWidget();
	//RWidget->setLayout(RLayout);

	//QHBoxLayout *LayoutGame = new QHBoxLayout();
	//LayoutGame->addWidget(LWidget);
	//LayoutGame->addWidget(MWidget); // , Qt::AlignCenter);
	//LayoutGame->addWidget(RWidget);

	gameWidget->setLayout(GPLayout);
	setCentralWidget(gameWidget);
	//resize(825, 555);
}

GameWindow::~GameWindow()
{
	delete labelProchaineForme;
	//delete labelGameOver;
	delete scoreLcd;
	delete niveauLcd;
	delete lignesLcd;

	delete BoutonPause;
	delete BoutonPlay;
	delete BoutonContinuer;
	delete BoutonMenu;

	delete GPLayout;
	delete gameWidget;
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
void GameWindow::play()
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

void GameWindow::endGame()
{
	labelGameOver = createLabel("Game Over");
	labelGameOver->setAlignment(Qt::AlignCenter);
	labelGameOver->setStyleSheet("background-color: rgba(255, 0, 0, 128); font: 25pt;");

	emit gameEnded(scoreLcd->intValue());

	GPLayout->addWidget(labelGameOver, 0, 1, 6, 1);
	//cout << "Fin";
	BoutonPause->setEnabled(false);
	BoutonPlay->setEnabled(false);
	BoutonMenu->setEnabled(false);

	BoutonContinuer->show();
}

