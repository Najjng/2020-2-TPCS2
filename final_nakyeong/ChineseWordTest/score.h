#ifndef SCORE_H
#define SCORE_H

#include <QString>
#include <QLabel>

// score is the sum of points
// getting one pair of cards matched correctly would get 10 points
class Score
{
public:
    // constructor
    Score();
    // points means the score you get when you get the right answer
    QLabel *label;

    // number of points that you got
    // I first tried to use 'point' as the name
    // but changed it into value
    // to avoid the confusion in grid.h
    int value;
};



#endif // SCORE_H
