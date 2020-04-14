#include "game.h"
#define FLECHE_GAUCHE 75
#define FLECHE_DROITE 77
#define FLECHE_HAUT 72
#define FLECHE_BAS 80

using namespace std;

Game ::Game() : QFrame()
{
	//initialisations
    srand(time(NULL));
    curForme = new Forme(rand() % FORMEZ);
    prochaineForme = new Forme(rand() % FORMEZ);
    curForme->setX(4);
    curForme->setY(2);
    lastAction = std::chrono::high_resolution_clock::now();
	alive = true;
    score = 0;
    linesCleared = 0;
	linesClearedLvl = 0;

	//mise a jour interface
	//emit levelChange(levelNumber);
	emit scoreChange(score);
	emit linesChange(linesCleared);
	this->repaint();

	//this->setSizeIncrement(40, 40);
	this->setGeometry(50, 120, 100, 240);
}

//void Game::resizeEvent(QResizeEvent *event)
//{
//	/*int a  = event->size().width();
//
//	QRect *a = new QRect(0,0, 10, 240);*/
//
//	cout << "TEST1 ICI";
//
//	//this->setGeometry(0, 0, 10, 240);
//	this->resize(event->size().height() / 2.4, event->size().height());
//	//this->setBaseSize(event->size().width(), 2.4 * event->size().width());
//
//	//a->setSize(event->size().width(), 2.4 * event->size().width());
//
//	/*this->setFrameRect();
//	this->adjustSize(event->size().width(), event->size().width());*/
//}

Game::~Game()
{
    delete curForme;
}

void Game ::afficher()
{
	//affichage dans le terminal sans qt, en commentaire dans loop  
    preview = curForme->copy();
    preview->setPreview(true);
    bougerForme(preview, 0, 23);
    cout << "__" << setw(5) << score << "__" << '\n';
    for (int i = 0; i < HAUTEUR; i++)
    {
        cout << setw(2) << i << setw(1) << '|';
        for (int j = 0; j < LARGEUR; j++)
        {
            if (board[i][j] == 1|| board[i][j] == 2|| board[i][j] == 3|| board[i][j] == 4|| board[i][j] == 5|| board[i][j] == 6|| board[i][j] == 7  
				|| curForme->getTileGlobal(i,j) == 1|| curForme->getTileGlobal(i, j) == 2|| curForme->getTileGlobal(i, j) == 3||
				curForme->getTileGlobal(i, j) == 4|| curForme->getTileGlobal(i, j) == 5|| curForme->getTileGlobal(i, j) == 6|| curForme->getTileGlobal(i, j) == 7)
            {
                cout << "#";
            }
            else if (preview->getTileGlobal(i,j) == 1|| preview->getTileGlobal(i, j) == 2|| preview->getTileGlobal(i, j) == 3|| preview->getTileGlobal(i, j) == 4
				|| preview->getTileGlobal(i, j) == 5|| preview->getTileGlobal(i, j) == 6|| preview->getTileGlobal(i, j) == 7)
            {
                cout << "o";
            }
            else
            {
                cout << " ";
            }
        }
        cout << "|";
        for(int j = 0; j < LARGEUR; j++)
        {
        
           if(prochaineForme->getTileGlobal(i,j) == 1|| prochaineForme->getTileGlobal(i, j) == 2|| prochaineForme->getTileGlobal(i, j) == 3|| 
			   prochaineForme->getTileGlobal(i, j) == 4|| prochaineForme->getTileGlobal(i, j) == 5|| prochaineForme->getTileGlobal(i, j) == 6||
			   prochaineForme->getTileGlobal(i, j) == 7)
           {
               cout << "o";
           }
           else
           {
               cout << " ";
           }
        }
        cout << '\n';
    }
    cout << "______" << "Level: " << level.getLevelNumber() << '\n';
    cout << "Lines cleared: " << linesCleared;
    cout << flush;
    delete preview;
}

void Game::paintEvent(QPaintEvent *)
{
	

	//creation du preview
	preview = curForme->copy();
	preview->setPreview(true);
	bougerForme(preview, 0, 23);

	//activation prochaine piece au repaint
	this->afficherProchaineForme();

	//peinture de la grille et des pieces et preview au repaint
	QPainter painter(this);
	QRect rect = contentsRect();
	QRgb TableCouleur[7] = {
		0xff66ff, 0x66ff33, 0xff0000, 0x0000ff,
		0xffff00, 0x00ffff,0xffffff};

	int topTableau = rect.bottom() - HAUTEUR * hauteurCarre();

	for (int i = 0; i < HAUTEUR; i++)
	{
		for (int j = 0; j < LARGEUR; j++)
		{
			int x = rect.left() + j * largeurCarre() + 1;
			int y = topTableau + i * hauteurCarre();
			int largeur = largeurCarre() - 2;
			int hauteur = hauteurCarre() - 2;

			if (board[i][j] == 1 || curForme->getTileGlobal(i, j) == 1)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[0]);
			}
			else if (board[i][j] == 2 || curForme->getTileGlobal(i, j) == 2)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[1]);
			}
			else if (board[i][j] == 3 || curForme->getTileGlobal(i, j) == 3)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[2]);
			}
			else if (board[i][j] == 4 || curForme->getTileGlobal(i, j) == 4)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[3]);
			}
			else if (board[i][j] == 5 || curForme->getTileGlobal(i, j) == 5)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[4]);
			}
			else if (board[i][j] == 6 || curForme->getTileGlobal(i, j) == 6)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[5]);
			}
			else if (board[i][j] == 7 || curForme->getTileGlobal(i, j) == 7)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[6]);
			}

			else if (preview->getTileGlobal(i, j) == 1 || preview->getTileGlobal(i, j) == 2 || preview->getTileGlobal(i, j) == 3 || preview->getTileGlobal(i, j) == 4
				|| preview->getTileGlobal(i, j) == 5 || preview->getTileGlobal(i, j) == 6 || preview->getTileGlobal(i, j) == 7)
			{
				painter.fillRect(x, y, largeur, hauteur, QColor(0, 0, 0, 130));
			}

			else
			{
				painter.fillRect(x, y, largeur, hauteur, QColor(0, 0, 0, 45));
			}
		}
	}

};

void Game::afficherProchaineForme()
{
	//afficher la prochaine forme
	if (!labelProchaineForme)
		return;

	setLabelProchaineForme(labelProchaineForme);
	int dx = 6;
	int dy = 6;
	QPixmap pixmap(dx * largeurCarre(), dy * hauteurCarre());
	QPainter painter(&pixmap);
	painter.fillRect(pixmap.rect(), labelProchaineForme->palette().window());
	QRgb TableCouleur[7] =
	{ 0xff66ff, 0x66ff33, 0xff0000, 0x0000ff,0xffff00, 0x00ffff };


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = j * largeurCarre() + 1;
			int y = i * hauteurCarre();
			int largeur = largeurCarre() - 2;
			int hauteur = hauteurCarre() - 2;

			if (prochaineForme->getMatrice()[i][j] == 1 || prochaineForme->getTileGlobal(i, j) == 1)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[0]);
			}
			if (prochaineForme->getMatrice()[i][j] ==2 || prochaineForme->getTileGlobal(i, j) == 2)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[1]);
			}
			if (prochaineForme->getMatrice()[i][j] == 3 || prochaineForme->getTileGlobal(i, j) == 3)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[2]);
			}
			if (prochaineForme->getMatrice()[i][j] == 4 || prochaineForme->getTileGlobal(i, j) == 4)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[3]);
			}
			if (prochaineForme->getMatrice()[i][j] == 5 || prochaineForme->getTileGlobal(i, j) == 5)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[4]);
			}
			if (prochaineForme->getMatrice()[i][j] == 6 || prochaineForme->getTileGlobal(i, j) == 6)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[5]);
			}
			if (prochaineForme->getMatrice()[i][j] == 7 || prochaineForme->getTileGlobal(i, j) == 7)
			{
				painter.fillRect(x, y, largeur, hauteur, TableCouleur[6]);
			}

		}
	}

	labelProchaineForme->setPixmap(pixmap);
}

void Game::setLabelProchaineForme(QLabel *label)
{
	labelProchaineForme = label;
}

bool Game::collision(Forme *forme)
{
	//gestion des collisions
    int xCentreForme = forme->getX();
    int yCentreForme = forme->getY();
    int xGlobal;
    int yGlobal;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            xGlobal = xCentreForme + (j - 2);
            yGlobal = yCentreForme + (i - 2);
            if ((forme->getTile(i, j) == 1|| forme->getTile(i, j) == 2|| forme->getTile(i, j) == 3|| forme->getTile(i, j) == 4|| forme->getTile(i, j) == 5
				|| forme->getTile(i, j) == 6|| forme->getTile(i, j) == 7) && (board[yGlobal][xGlobal] == 1|| board[yGlobal][xGlobal] == 2|| board[yGlobal][xGlobal] == 3
					|| board[yGlobal][xGlobal] == 4|| board[yGlobal][xGlobal] == 5|| board[yGlobal][xGlobal] == 6|| board[yGlobal][xGlobal] == 7 
					|| yGlobal > 23 || xGlobal < 0 || xGlobal > 9))
            {
                return true;
            }
        }
    }

    return false;
}

void Game::ligneComplete()
{
	//gestion lignes complete
    int lignePleine = 1;
    int nmbLignes = 0;
    for (int i = 0; i < HAUTEUR; i++)
    {
        lignePleine = 1;
        for (int j = 0; j < LARGEUR; j++)
        {
           if(board[i][j] != 1&& board[i][j] != 2&& board[i][j] != 3&& board[i][j] != 4&& board[i][j] != 5&& board[i][j] != 6&& board[i][j] != 7)
           {
              lignePleine = 0;
           }
        }
        if(lignePleine == 1)
        {
            shiftBoard(i);
            nmbLignes++;
            i--;
        }
    }
    score += level.getScore(nmbLignes);
    linesCleared += nmbLignes;
	linesClearedLvl += nmbLignes;

	//mise a jour widgets
	emit scoreChange(score);
	emit linesChange(linesCleared);
}

void Game::shiftBoard(int index)
{
    for(int i = index; i > 0; i--)
    {
        for(int j = 0; j < LARGEUR; j++)
        {
            board[i][j] = board[i-1][j];
        }
    }
}

void Game::mort()
{
    if(curForme->getY() < 3 && collision(curForme) == true)
    {
        alive = false;
    }
}

void Game::keyPressEvent(QKeyEvent *event)
{
	//input fait avec qt pour l interface

	if (alive && !pause && debute)
	{
		switch (event->key()) 
		{
		case Qt::Key_Left:
			bougerForme(curForme, -1, 0);
			this->repaint();
			break;

		case Qt::Key_Right:
			bougerForme(curForme, 1, 0);
			this->repaint();
			break;
		
		case Qt::Key_Down:
			bougerForme(curForme, 0, 1);
			this->repaint();
			break;
			
		case Qt::Key_Up:
			tournerForme(curForme);
			this->repaint();
			break;

		case Qt::Key_Z:
			tournerForme(curForme);
			this->repaint();
			break;

		case Qt::Key_Space:
			bougerForme(curForme, 0, 23);
			this->repaint();
			break;


		default:
			QFrame::keyPressEvent(event);
		}
	}
}

void Game :: input()
{
	//input pour le terminal sans qt
    if (kbhit())
    {
        int pressedChar;
        pressedChar = getch();
        switch (pressedChar)
        {
        case FLECHE_HAUT:
            tournerForme(curForme);
			this->repaint();
            afficher();
            break;
        case FLECHE_DROITE:
            bougerForme(curForme, 1, 0);
            afficher();
			this->repaint();
            break;
        case FLECHE_GAUCHE:
            bougerForme(curForme, -1, 0);
            afficher();
			this->repaint();
            break;
        case FLECHE_BAS:
            bougerForme(curForme, 0, 23);
            afficher();
			this->repaint();
            break;
        }
    }
}

void Game::bougerForme(Forme *forme, int x, int y)
{
    int xInitial = forme->getX();
    int yInitial = forme->getY();
    if (x > 0)
    {

        for (int i = 0; i <= x; i++)
        {
            forme->setX(xInitial + i);
            if (collision(forme) == true)
            {
                forme->setX(xInitial + i - 1);
                break;
            }
        }
    }
    else if (x < 0)
    {
        for (int i = 0; i >= x; i--)
        {
            forme->setX(xInitial + i);
            if (collision(forme) == true)
            {
                forme->setX(xInitial + i + 1);
                break;
            }
        }
    }
    for (int i = 0; i <= y; i++)
    {
        forme->setY(yInitial + i);
        if (collision(forme) == true)
        {
            forme->setY(yInitial + i - 1);
            if(!forme->isPreview())
            {
                formeVersBoard(forme);
                changerForme();
            }
            break;
        }
    }

}

void Game ::changerForme()
{
    int typeProchaineForme;
    delete curForme;
    curForme = prochaineForme;
    typeProchaineForme = rand() % FORMEZ;
    if(typeProchaineForme == curForme->getType())
    {  
        typeProchaineForme = rand()% FORMEZ;
    }
    prochaineForme = new Forme(typeProchaineForme);
}

void Game ::tournerForme(Forme *forme)
{
    tournerForme(forme, DROITE);
}

void Game ::tournerForme(Forme *forme, int direction)
{
    forme->tourner(direction);
    if(collision(forme) == true)
    {
        forme->tourner(direction * -1);
    }
}

void Game ::formeVersBoard(Forme *forme)
{
    int xforme = forme->getX();
    int yforme = forme->getY();

    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (forme->getTile(i, j) == 1|| forme->getTile(i, j) == 2|| forme->getTile(i, j) == 3|| forme->getTile(i, j) == 4|| forme->getTile(i, j) == 5||
				forme->getTile(i, j) == 6|| forme->getTile(i, j) == 7)
            {
                board[yforme + (i - 2)][xforme + (j - 2)] = forme->getTile(i, j);
            }
        }
    }
}

void Game :: loop()
{
	//loop du jeu afficher/input pour le terminal

	debute = true;
	level.setLevelNumber(levelNumber);
	this->repaint();
    //afficher();
	int i = 0;

    while (alive)
    {
		QCoreApplication::processEvents();
        //input();
        //level.update(linesCleared);
        if ((std::chrono::high_resolution_clock::now() - lastAction > std::chrono::milliseconds{level.getTickTime()}) && pause == false)
        {
            bougerForme(curForme, 0, 1);
            //afficher();
			this->repaint();
            ligneComplete();
            //afficher();
			this->repaint();
            mort();

			cout << linesClearedLvl;
			if (linesClearedLvl >= 10)
			{
				linesClearedLvl = linesClearedLvl - 10;
				level.next();
			}
            //level.update(linesCleared);
			if (level.getLevelNumber() != i)
			{
				//cout << level.getLevelNumber();
				emit levelChange(level.getLevelNumber());
				i = level.getLevelNumber();
			}
            lastAction = std::chrono::high_resolution_clock::now();
        }
    }

	emit death();

    cout << "GAME OVER" << endl;
}
