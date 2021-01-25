#include "timer.h"
#include <QTime>
#include <QCoreApplication>

Timer::Timer()
{
    timer = new QTimer(this);
    label = new QLabel("Seconds: 0");
    //start from 0 to 1000
    counter = 0;
    timer->start(1000);
}

// reset function sets the start of the timer to -1
// I made 3 seconds delay here for the player to get ready for the new game
// when the player clicked for a new game
void Timer::reset(){
    counter = -3;
    timer->start(1000);
}
