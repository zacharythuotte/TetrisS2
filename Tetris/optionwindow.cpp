#include "optionwindow.h"

OptionWindow::OptionWindow(QWidget *parent) : QMainWindow(parent)
{
	startLevel = 0;
	startDifficulty = levelToDifficulty(startLevel);
	optionWidget = new QWidget();

	//LAYOUT PRINCIPAL
	layoutOption = new QGridLayout();

	//BACKGROUND DE LINTERFACE
	//QPixmap bkgnd("./Image/Background.jpg");
	//bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	//QPalette palette;
	//palette.setBrush(QPalette::Background, bkgnd);
	//this->setPalette(palette);

	//BOUTON RETOUR
	returnButton = new QPushButton("Retour");
	returnButton->setFixedWidth(BUTTON_MAX_WIDTH);
	QObject::connect(returnButton, SIGNAL(clicked()), parent, SLOT(showMainWindow()));

	//BOUTON ACCEPTER
	acceptButton = new QPushButton("Accepter");
	acceptButton->setFixedWidth(BUTTON_MAX_WIDTH);
	QObject::connect(acceptButton, SIGNAL(clicked()), parent, SLOT(showGame()));

	//SLIDER CHOIX VITESSE
	layoutSlider = new QGridLayout();

	labelSliderTitle = new QLabel("Niveau de jeu");
	labelSliderTitle->setMaximumWidth(400);

	labelSliderSpeed = new QLabel(QString::number(difficultyToLevel(startDifficulty))); //Valeur par defaut est vitesse en memoire
	labelSliderSpeed->setFixedWidth(labelSliderSpeed->width());

	sliderSpeed = new QSlider(Qt::Horizontal);
	sliderSpeed->setTickPosition(QSlider::TicksBelow);
	sliderSpeed->setTickInterval(1);
	sliderSpeed->setRange(0, 9);
	sliderSpeed->setValue(0);
	sliderSpeed->setFixedWidth(500);
	sliderSpeed->setMaximumWidth(sliderSpeed->width());

	QObject::connect(sliderSpeed, SIGNAL(valueChanged(int)), this, SLOT(changeSpeed()));

	layoutSlider->addWidget(labelSliderTitle, 0, 0, Qt::AlignCenter);
	layoutSlider->addWidget(labelSliderSpeed, 0, 1, Qt::AlignRight);
	layoutSlider->addWidget(sliderSpeed, 1, 0, 1, 2, Qt::AlignCenter);
	
	sliderWidget = new QWidget();
	sliderWidget->setStyleSheet("background-color: white"); //Mettre par defaut A CORRIGER /////////////////////////////
	sliderWidget->setAutoFillBackground(true);
	sliderWidget->setLayout(layoutSlider);
	sliderWidget->setMaximumSize(600, 200);
	//QPalette palette;
	//palette.setColor(QPalette::Background, Qt::gray);
	//sliderWidget->setPalette(palette);
	//sliderWidget->setAutoFillBackground(true);
	//sliderWidget->setStyleSheet("border: 1px solid black; background-color: gray");
	layoutOption->addWidget(sliderWidget, 0, 0, 1, 2, Qt::AlignCenter);

	//LABEL INSTRUCTIONS
	labelInstructions = new QLabel("Instructions de jeu \n\n\nUtilisez les fleches gauche et droite pour deplacer la piece lateralement et la fleche du haut (ou [Z]) pour pivoter.\n\nVous pouvez deposer une piece avec [espace].");
	labelInstructions->setWordWrap(true);
	labelInstructions->setFrameStyle(QFrame::Box | QFrame::Raised);
	labelInstructions->setAlignment(Qt::AlignLeft);
	labelInstructions->setAlignment(Qt::AlignVCenter);
	labelInstructions->setStyleSheet("QLabel { background-color : white; color : black; font: 15pt; }");
	labelInstructions->setFixedSize(700, 250);

	//PLACEMENT LAYOUT PRINCIPAL
	layoutOption->addWidget(labelInstructions, 1, 0, 1, 2, Qt::AlignCenter);
	layoutOption->addWidget(returnButton, 2, 0, Qt::AlignRight);
	layoutOption->addWidget(acceptButton, 2, 1, Qt::AlignLeft);

	optionWidget->setLayout(layoutOption);
	//optionWidget->setStyleSheet("border: 2px solid blue");
	setCentralWidget(optionWidget);
}

OptionWindow::~OptionWindow()
{
	//qInfo() << "Window doptions se fait deleter";

	/*delete acceptButton;
	delete sliderSpeed;
	delete layoutSlider;
	delete layoutOption;
	delete optionWidget;*/
}

void OptionWindow::changeSpeed()
{
	startLevel = sliderSpeed->value();
	startDifficulty = levelToDifficulty(startLevel);
	
	labelSliderSpeed->setText(QString::number(sliderSpeed->value()));

	//labelSliderSpeed->setText(QString::number(difficulty));
}

//Fonction qui retourne la difficulte (tick time) selon le niveau
int OptionWindow::levelToDifficulty(int l)
{
	return 1000.0 * (48.0 - (5.0*l)) / 60.0;
}

//Fonction qui retourne le niveau selon la difficulte (tick time)
int OptionWindow::difficultyToLevel(int d)
{
	return ((60.0 * d / 1000.0) - 48.0) / -5.0;
}

