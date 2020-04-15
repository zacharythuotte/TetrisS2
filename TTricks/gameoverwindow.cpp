#include "GameOverWindow.h"

GameOverWindow::GameOverWindow(QWidget *parent) : QMainWindow(parent)
{
	gameOverWidget = new QWidget();

	//LAYOUT PRINCIPAL
	layoutGameOver = new QVBoxLayout();

	//LABEL GAME OVER
	gameOverLabel = createLabel("Votre score est de :");
	gameScoreLabel = createLabel(" ");
	instructionLabel = createLabel("Entrez un nom valide pour le sauvegarder");

	//BOUTON D OPTION
	acceptButton = new QPushButton("Accepter");
	QObject::connect(acceptButton, SIGNAL(clicked()), this, SLOT(closeGameOver()));
	acceptButton->setEnabled(false);
	acceptButton->setMaximumWidth(300);

	//LINE EDIT DE NOM POUR LE SCORE
	nameEdit = new QLineEdit();
	nameEdit->setPlaceholderText("Votre nom");
	nameEdit->setMaxLength(32);
	nameEdit->setMaximumWidth(300);
	QObject::connect(nameEdit, SIGNAL(textEdited(const QString &)), this, SLOT(verifyName()));

	//PLACEMENT LAYOUT PRINCIPAL
	layoutGameOver->addWidget(gameOverLabel);
	layoutGameOver->setAlignment(gameOverLabel, Qt::AlignHCenter);
	layoutGameOver->addWidget(gameScoreLabel);
	layoutGameOver->setAlignment(gameScoreLabel, Qt::AlignHCenter);
	layoutGameOver->addWidget(instructionLabel);
	layoutGameOver->setAlignment(instructionLabel, Qt::AlignHCenter);
	layoutGameOver->addWidget(nameEdit);
	layoutGameOver->setAlignment(nameEdit, Qt::AlignHCenter);
	layoutGameOver->addWidget(acceptButton, Qt::AlignCenter);
	layoutGameOver->setAlignment(acceptButton, Qt::AlignHCenter);

	gameOverWidget->setLayout(layoutGameOver);
	setCentralWidget(gameOverWidget);
}

GameOverWindow::~GameOverWindow()
{
	delete gameOverLabel;
	delete gameScoreLabel;
	delete instructionLabel;
	delete nameEdit;
	delete acceptButton;

	delete layoutGameOver;
	delete gameOverWidget;
}

void GameOverWindow::verifyName()
{
	//Si le nom entre est valide seulement
	if (!nameEdit->text().isEmpty())
	{
		acceptButton->setEnabled(true);
		playerName = (nameEdit->text()).toStdString();
	}
	else
	{
		acceptButton->setEnabled(false);
	}
}

void GameOverWindow::closeGameOver() 
{
	emit endGameOver(playerName);
	//cout << nameEdit->text();
	//this->close();
}

void GameOverWindow::setGameScore(int imputScore)
{
	gameScore = imputScore;

	gameScoreLabel->setText(QString::number(imputScore));
}

//CREER LABEL
QLabel *GameOverWindow::createLabel(const QString &text)
{
	QLabel *label = new QLabel(text);
	label->setFrameStyle(QFrame::Box | QFrame::Raised);
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("QLabel { background-color : white; color : black; font: 20pt; }");
	label->setFixedSize(700, 100);
	return label;
}
