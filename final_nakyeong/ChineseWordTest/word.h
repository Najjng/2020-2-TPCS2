/****
I used QPushButton instead of making cards because of two reasons below:
First, I think it looks better when the effect of button pushed is shown while playing game
as I didn't have any idea of visualizing the opening effect of cards.
Second, I wanted to try using QPushButton since I've never used it before.
****/

#ifndef WORD_H
#define WORD_H

#include <QPushButton>

class Word : public QPushButton
{
    Q_OBJECT

public:

    // constructor with QString
    // Unlike word cards, Word here only have one text each
    // So "我" and "I" are different cards that have to be matched in the game.
    Word(const QString initialize, const QString& text, QWidget* parent = 0);

    // word in Chinese and its meaning
    // ex) 我 and I
    QString text;

    // true if this card is clicked right now
    bool is_clicked;
    // true when the Hanzi and meaning cards were matched correctly
    bool is_matched;

public slots:
    // action of opening a card by clicking the QPushButton
    void click();
};

#endif // WORD_H
