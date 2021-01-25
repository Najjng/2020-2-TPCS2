/****
2020-2 TPCS2 final-02
2018-15185 Nakyeong Kim
This project still needs more improvement.
I attached this project because I want to show that I worked on it a little.
I'm planning to work on it this winter and
if you want to see the codes working, different project(word test) would be the one for that.
****/

#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QMainWindow>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QSize>

#include "grid.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow *mw = new QMainWindow;
    QWidget *qw = new QWidget;

    // vertical and horizontal box that holds cards
    QVBoxLayout *vb = new QVBoxLayout(qw);
    QHBoxLayout *hb = new QHBoxLayout;

    // new grid for the cards to be viewed
    Grid *layout = new Grid();




    // add layout so that boxes and widgets set above can be viewed
    vb->addLayout(hb);
    vb->addLayout(layout);

    mw->setCentralWidget(qw);
    // the name of the window would be "Chinese Words"
    mw->setWindowTitle("Chinese Words");
    mw->show();

   return app.exec();
}
