#ifndef GRID_H
#define GRID_H

#include <QGridLayout>
#include <QStringList>
#include <QVector>

#include "card.h"


class Grid : public QGridLayout
{
    Q_OBJECT

public:
    // constructor
    Grid();

private:
    // view cards that Grid has
    void view_cards();
};

#endif // GRID_H
