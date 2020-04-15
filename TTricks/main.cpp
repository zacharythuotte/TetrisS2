#include <QApplication>
#include <iostream>
#include "test.h"
#include "mainwindow.h"

using namespace std;


int main(int argc, char ** argv)
{
    //Test tests;
    //tests.testFormes();
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();

    /*Game jeu;
    jeu.loop();*/
    return 0;
}
