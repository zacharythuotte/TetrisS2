#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
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
	screenTitle->setAlignment(Qt::AlignCenter);

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

	//optionButton = new QPushButton("Options");
	//optionButton->setMaximumWidth(BUTTON_MAX_WIDTH);
	//QObject::connect(optionButton, SIGNAL(clicked()), this, SLOT(showOption()));

	leaderboardButton = new QPushButton("Voir meilleurs scores");
	leaderboardButton->setFixedWidth(BUTTON_MAX_WIDTH);
	QObject::connect(leaderboardButton, SIGNAL(clicked()), this, SLOT(showLeaderboard()));
	//QObject::connect(volumeButton, SIGNAL(clicked()), musique, SLOT(stop()));

	exitButton = new QPushButton("Quitter");
	exitButton->setFixedWidth(BUTTON_MAX_WIDTH);
	QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

	//PLACEMENT LAYOUT PRINCIPAL
	layoutPrincipal->addWidget(screenTitle, BUTTON_MAX_WIDTH, Qt::AlignCenter);
	layoutPrincipal->addWidget(startButton, BUTTON_MAX_WIDTH, Qt::AlignCenter);
	//layoutPrincipal->addWidget(optionButton, BUTTON_MAX_WIDTH, Qt::AlignCenter);
	layoutPrincipal->addWidget(leaderboardButton, BUTTON_MAX_WIDTH, Qt::AlignCenter);
	layoutPrincipal->addWidget(exitButton, BUTTON_MAX_WIDTH, Qt::AlignCenter);
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
	//gamePage->show();

	pagesStack->addWidget(gamePage);
	pagesStack->setCurrentWidget(gamePage);
	/*gamePage = new GameWindow();
	setCentralWidget(gamePage);*/
	//gamePage->show();
}

void MainWindow::showLeaderboard()
{
	pagesStack->setCurrentWidget(leaderboardPage);
}

//CETTE FONCTION MONTRE LA FENETRE DE FIN DE JEU
void MainWindow::showGameOver()
{
	gameOverPage = new GameOverWindow(this);
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

void MainWindow::showMainWindow()
{
	pagesStack->setCurrentWidget(centralWidget);
	//setCentralWidget(centralWidget);
}
