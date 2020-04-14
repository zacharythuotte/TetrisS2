#include "GameOverWindow.h"
#include "MainWindow.h"

using namespace std;

GameOverWindow::GameOverWindow(QWidget *parent) : QMainWindow(parent)
{
	mainWindow = parent;

	gameOverWidget = new QWidget();

	//LAYOUT PRINCIPAL
	layoutGameOver = new QVBoxLayout();

	//LABEL GAME OVER
	string labelText = "Bravo votre score est de :\n ";
	labelText.append("METTRE SCORE ICI\n");
	labelText.append("Entrez votre nom pour continuer :");
	gameOverLabel = new QLabel(QString::fromStdString(labelText));
	gameOverLabel->setAlignment(Qt::AlignCenter);
	gameOverLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
	gameOverLabel->setStyleSheet("QLabel { background-color : white; color : black; font: 25pt; }");
	//gameOverLabel->setMaximumSize(500, 500);

	//gameOverLabel->setText

	//BOUTON D OPTION
	acceptButton = new QPushButton("Accepter");
	QObject::connect(acceptButton, SIGNAL(clicked()), this, SLOT(closeGameOver()));
	acceptButton->setEnabled(false);
	acceptButton->setMaximumWidth(300);

	//LINE EDIT DE NOM POUR LE SCORE
	nameEdit = new QLineEdit();
	nameEdit->setPlaceholderText("Votre nom");
	nameEdit->setMaximumWidth(300);
	QObject::connect(nameEdit, SIGNAL(textEdited(const QString &)), this, SLOT(verifyName()));


	//PLACEMENT LAYOUT PRINCIPAL
	layoutGameOver->addWidget(gameOverLabel, Qt::AlignCenter);
	layoutGameOver->addWidget(nameEdit, Qt::AlignCenter);
	layoutGameOver->addWidget(acceptButton, Qt::AlignCenter);

	gameOverWidget->setLayout(layoutGameOver);
	setCentralWidget(gameOverWidget);
}

GameOverWindow::~GameOverWindow()
{
	delete acceptButton;
	delete layoutGameOver;
}

void GameOverWindow::verifyName()
{
	if (!nameEdit->text().isEmpty())
	{
		acceptButton->setEnabled(true);
	}
	else
	{
		acceptButton->setEnabled(false);
	}
}

void GameOverWindow::closeGameOver() 
{
	cout << "TEST";
	//cout << nameEdit->text();
	//this->parent.showMainWindow();
}
