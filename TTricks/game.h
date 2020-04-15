#include "forme.h"
#include "level.h"
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <QMainWindow>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QRect>
#include <QPainter>
#include <QColor>
#include <QLabel>
#include <QPointer>
#include <QEventLoop>
#define LARGEUR 10
#define HAUTEUR 24  

class Game : public QFrame
{
	Q_OBJECT

	signals:
		void scoreChange(int score);
		void linesChange(int numLines);
		void levelChange(int level);
		void death();

    public:
        Game();
        ~Game();
		void setLevel(int l) { levelNumber = l; level.setLevelNumber(levelNumber); };
		bool pause = false;
		bool alive;
		bool debute = false;
		Level level;
        void afficher();
		void paintEvent(QPaintEvent *);
		void keyPressEvent(QKeyEvent *event) override;
        bool collision(Forme *forme);
        void ligneComplete();
        void shiftBoard(int index);
        void input();
        void mort();
        void bougerForme(Forme *forme, int x, int y);
        void changerForme();
        void tournerForme(Forme *forme);
        void tournerForme(Forme *forme, int direction);
		void formeVersBoard(Forme *forme);
		void loop();
		void setLabelProchaineForme(QLabel *label);
		int largeurCarre() { return contentsRect().width() / LARGEUR; };
		int hauteurCarre() { return contentsRect().height() / HAUTEUR; }; 
		void afficherProchaineForme();
		QPointer<QLabel> labelProchaineForme;
		/*void resizeEvent(QResizeEvent *event);*/
    private:
        Forme *curForme;
        Forme *preview;
        Forme *prochaineForme;
        int board[HAUTEUR][LARGEUR] = {0};
		int levelNumber;
        int score;
        int linesCleared; //Le nombre total de lignes eliminees
		int linesClearedLvl; //Le nombre de ligne temporaire du niveau
        std::chrono::time_point<std::chrono::high_resolution_clock> lastAction, curTime;

};
