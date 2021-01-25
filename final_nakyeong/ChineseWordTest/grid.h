/***
I first made struct GridContainer as advised after class and after making that struct,
I found out that making it an independent header/cpp file would be better.
And this is the output of separating Grid from others.
***/


#ifndef GRID_H
#define GRID_H

#include <QGridLayout>
#include <QMessageBox>
// to switch words randomly
#include <QRandomGenerator>
#include <QTimer>
// to save words
#include <QStringList>

#include "score.h"
#include "timer.h"

class Grid : public QGridLayout
{
    Q_OBJECT

public:
    Grid(Timer* timer, Score *point);
    // timer object from timer.h
    Timer* timer;
    //Score object for the score from score.h
    Score *point;

public slots:
    // check every click
    void check();
    // start a new game
    void new_game();
    // count the seconds passed
    void count_time();

private:
    // create new starting board with random cards
    void initialize();
};

#endif // GRID_H
