#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	leaderboardScores = new Leaderboard();

	centralWidget = new QWidget();
	pagesStack = new QStackedWidget();
	optionPage = new OptionWindow(this);
	pagesStack->addWidget(optionPage);
	leaderboardPage = new LeaderboardWindow(this);
	pagesStack->addWidget(leaderboardPage);
	
	//MUSIQUE
	musique = new QSoundEffect();
	musique->setSource(QUrl::fromLocalFile("./Image/TetrisMetal.wav"));
	musique->play();
	musique->setLoopCount(QSoundEffect::Infinite);

	//LAYOUT
	layoutPrincipal = new QVBoxLayout();

	//BACKGROUND DE LINTERFACE
	QPixmap bkgnd("./Image/Background.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);
	
	//IMAGE TITRE
	screenTitle = new QLabel();
	screenTitle->setPixmap(QPixmap("./Image/Screentitle.png"));
	screenTitle->setScaledContents(true);
	screenTitle->setFixedSize(800, 300);
	screenTitle->setAlignment(Qt::AlignCenter);

	//CREDITS
	creditsLabel = new QLabel();
	creditsLabel->setAlignment(Qt::AlignCenter);
	creditsLabel->setText("Projet de session equipe P-04 S2 GEGI H2020 USherbrooke\nInterface graphique par GI (joli1801 - phas2401 - thuz3401)");
	creditsLabel->setStyleSheet("QLabel { color : white }");
	creditsLabel->setFixedSize(400, 40);


	//SLIDER (VOLUME)
	sliderVolume = new QSlider(Qt::Horizontal);
	QObject::connect(sliderVolume, SIGNAL(valueChanged(int)), this, SLOT(changeVolume()));
	sliderVolume->setRange(0, 100);
	sliderVolume->setValue(10); //Volume initial a 10 sur 100

	//BARRE OUTILS (VOLUME)
	toolBar = new QToolBar("Volume");
	this->setContextMenuPolicy(Qt::NoContextMenu); //Empeche utilisateur denlever la toolbar
	toolBar->addWidget(new QLabel("Volume"));
	toolBar->addSeparator();
	toolBar->addWidget(sliderVolume);
	toolBar->setMaximumWidth(400);
	toolBar->setMovable(false);
	toolBar->setAutoFillBackground(true);
	//toolBar->setStyleSheet("background-color: gray");
	this->addToolBar(Qt::BottomToolBarArea, toolBar);

	//BOUTONS MENU PRINCIPAL
	startButton = new QPushButton("Jouer!");
	startButton->setFixedWidth(BUTTON_MAX_WIDTH);
	QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(showOption()));

	leaderboardButton = new QPushButton("Voir meilleurs scores");
	leaderboardButton->setFixedWidth(BUTTON_MAX_WIDTH);
	QObject::connect(leaderboardButton, SIGNAL(clicked()), this, SLOT(showLeaderboard()));

	exitButton = new QPushButton("Quitter");
	exitButton->setFixedWidth(BUTTON_MAX_WIDTH);
	QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

	//PLACEMENT LAYOUT PRINCIPAL
	layoutPrincipal->addWidget(screenTitle, Qt::AlignHCenter);
	layoutPrincipal->addWidget(creditsLabel);
	layoutPrincipal->setAlignment(creditsLabel, Qt::AlignHCenter);
	layoutPrincipal->addWidget(startButton, BUTTON_MAX_WIDTH, Qt::AlignHCenter);
	//layoutPrincipal->addWidget(optionButton, BUTTON_MAX_WIDTH, Qt::AlignCenter);
	layoutPrincipal->addWidget(leaderboardButton, BUTTON_MAX_WIDTH, Qt::AlignHCenter);
	layoutPrincipal->addWidget(exitButton, BUTTON_MAX_WIDTH, Qt::AlignHCenter);
	layoutPrincipal->setAlignment(Qt::AlignCenter);
	
	centralWidget->setLayout(layoutPrincipal);
	//centralWidget->setMaximumHeight(300);
	pagesStack->addWidget(centralWidget);

	setCentralWidget(pagesStack);
	pagesStack->setCurrentWidget(centralWidget);
}

MainWindow::~MainWindow()
{
	delete startButton;
	delete leaderboardButton;
	delete sliderVolume;
	delete toolBar;

	delete exitButton;
	delete musique;

	delete screenTitle;
	delete layoutPrincipal;
	delete centralWidget;
}

//CETTE FONCTION MONTRE LA FENETRE D OPTIONS
void MainWindow::showOption()
{
	pagesStack->setCurrentWidget(optionPage);
	//setCentralWidget(optionPage);
	//optionPage->show();
}

//CETTE FONCTION MONTRE LA FENETRE DE JEU
void MainWindow::showGame()
{
	gamePage = new GameWindow(this);
	gamePage->setLvl(optionPage->startLevel);
	QObject::connect(gamePage, SIGNAL(gameEnded(int)), this, SLOT(saveTempScore(int)));

	pagesStack->addWidget(gamePage);
	pagesStack->setCurrentWidget(gamePage);
	/*gamePage = new GameWindow();
	setCentralWidget(gamePage);*/
	//gamePage->show();
}

void MainWindow::showLeaderboard()
{
	leaderboardPage->setLeaderboard(*leaderboardScores);
	pagesStack->setCurrentWidget(leaderboardPage);
}

//CETTE FONCTION MONTRE LA FENETRE DE FIN DE JEU
void MainWindow::showGameOver()
{
	gameOverPage = new GameOverWindow(this);
	QObject::connect(gameOverPage, SIGNAL(endGameOver(string)), this, SLOT(sendNewScore(string)));

	gameOverPage->setGameScore(lastScore);

	pagesStack->addWidget(gameOverPage);
	pagesStack->setCurrentWidget(gameOverPage);
	//gameOverPage = new GameOverWindow(centralWidget);
	//setCentralWidget(gameOverPage);
	//QObject::connect(gameOverPage, SIGNAL(closed()), this, SLOT(showMainWindow()));
	//gamePage->show();
}

void MainWindow::changeVolume()
{
	musique->setVolume((sliderVolume->value())/100.0);
}

void MainWindow::saveTempScore(int tempScore)
{
	//cout << tempScore;
	lastScore = tempScore;
}

//Ajoute au leadderboard le nouveau score et son auteur
void MainWindow::sendNewScore(string newName)
{
	//cout << newName;

	leaderboardScores->addScore(newName, lastScore);
	showMainWindow();
}

void MainWindow::showMainWindow()
{
	pagesStack->setCurrentWidget(centralWidget);
	//setCentralWidget(centralWidget);
}
