/****
2020-2 TPCS2 final-01
2018-15185 Nakyeong Kim
Here I tried to make UI, not using mainwindow.ui based on QVBoxLayout and QHBoxLayout
link: https://doc.qt.io/qt-5/qhboxlayout.html
****/


#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QMainWindow>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QSize>

#include "mainwindow.h"
#include "timer.h"
#include "grid.h"
#include "word.h"
#include "score.h"


// main function to view what I've created
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // new window and widget for the program to be viewed
    QMainWindow *mw = new QMainWindow;
    QWidget *qw = new QWidget;

    QVBoxLayout *vb = new QVBoxLayout(qw);

    // timer to count the seconds
    Timer *mt = new Timer();
    // score to count the points the player got
    Score *p = new Score();

    // grid layout with timer and point inside it
    Grid *layout = new Grid(mt, p);

    // horizontal box for buttons: new game, quit game, timer and score(point)
    QHBoxLayout *hb = new QHBoxLayout;

    // fix size for the widgets in the horizontal box
    // it can be changed as preferred
    // here I put (250, 50)
    const QSize size = QSize(250,50);


    // point(score) box
    p->label->setFixedSize(size);
    hb->addWidget(p->label);

    // timer box
    mt->label->setFixedSize(size);
    hb->addWidget(mt->label);

    // new game button
    QPushButton *ng = new QPushButton("New Game"); // new game button
    QObject::connect(ng, SIGNAL(clicked()), layout, SLOT(new_game()));
    ng->setFixedSize(size);

    //quit game button
    QPushButton *qg = new QPushButton("Quit Game"); // quit game button
    QObject::connect(qg, SIGNAL(clicked()), mw, SLOT(close()));
    qg->setFixedSize(size);

    //add the buttons above to widget and layout
    hb->addWidget(ng);
    hb->addWidget(qg);
    vb->addLayout(hb);
    vb->addLayout(layout);

    //mainwindows
    mw->setCentralWidget(qw);
    mw->setWindowTitle("Chinese Words - Meaning Linking Game");
    mw->show();

    return app.exec();
}

