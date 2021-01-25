#include "grid.h"

// consturctor only has one function: view_cards
// which will construct the grid with cards when the program runs
Grid::Grid()
{
    view_cards();
}

// view_cards can be understood as initializing the window
void Grid::view_cards()
{
    // for initial version, I just typed all the cards that will be used by hand
    // if the program grows, we can get the file of data
    // and put the data of it as an input
    QVector<Card*> cards;
    Card *card1 = new Card("我", "I", "wo", {3});
    Card *card2 = new Card("你", "You", "ni", {3});
    Card *card3 = new Card("好", "Good", "hao", {3});
    Card *card4 = new Card("你好", "Hello", "nihao", {3, 3});
    Card *card5 = new Card("再见", "Goodbye", "zaijian", {4, 4});
    Card *card6 = new Card("爱", "love", "ai", {4});

    cards.push_back(card1);
    cards.push_back(card2);
    cards.push_back(card3);
    cards.push_back(card4);
    cards.push_back(card5);
    cards.push_back(card6);


    // view 6 cards
    for(int row=0; row<2; row++){
        for (int col=0; col<3; col++){
            int i = 3*row + col;

            // get the Card in order
            Card *to_locate = cards[i];
            // get the label of the Card
            QString card = to_locate->label();

            // make a CardButton with the card
            // I set the border line, font size and the default size of the cards
            CardButton *cb = new CardButton(card, card);
            cb->setStyleSheet("border:2px solid black; font-size: 36px; height: 300px; width: 200px;");

            // I made this connecting in order to make the feature change dynamically
            // this connecting doesn't work well
            // maybe because Card and CardButton are separated
            // if I continue this work,
            // I want to integrate Card and CardButton
            // and make a public slot so that connecting would work fine
            QObject::connect(cb, SIGNAL(clicked()), cb, SLOT(click()));
            QObject::connect(cb, SIGNAL(clicked()), to_locate, SLOT(label()));

            // add words to the grid
            this->addWidget(cb, row, col, 1, 1);

        }
    }
}



