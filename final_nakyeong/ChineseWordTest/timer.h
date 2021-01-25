#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

//Timer object to check the
class Timer : public QObject
{
    Q_OBJECT

public:
    //constructor
    Timer();
    // QTimer object to show how many seconds passed from start
    QTimer *timer;
    // label for the timer
    QLabel *label;
    // Show how many seconds passed
    int counter;

public slots:
    // sets to zero for the game to restart
    void reset();
};

#endif // TIMER_H
