#include "score.h"

Score::Score()
{
     // start from0 point
    this->value = 0;
    // label to be shown at left top of the game screen
    QString str = "Score: " + QString::number(value);
    this->label = new QLabel(str);
}
