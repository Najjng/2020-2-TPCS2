#include "card.h"

Card::Card(const QString Hanzi, const QString meaning, const QString pinyin, const QVector<int> tone)
{
    this->Hanzi = Hanzi;
    this->meaning = meaning;
    this->pinyin = pinyin;
    this->tone = tone;

}

CardButton::CardButton(const QString initialize, const QString &text, QWidget *parent)
        : QPushButton(initialize, parent)
{
    clicked_num = 0;
    // Word contains its own text
    this->label = text;
    // is_clicked is set to be false in default
    this->is_clicked = false;
    // to make the button border is raised
    setFlat(true);
    // painting background with the same color of word buttons
    setAutoFillBackground(true);
    // update with the changes above
    update();
}

// if the CardButton is clicked
// is_clicked becomes true
// and the clicked number gets bigger
// except for the case that the clicked number is three
// so that four features can be viewed in order
void CardButton::click()
{
    if (clicked_num != 3) {
        is_clicked = true;
        this->clicked_num+=1;
    } else {
        is_clicked = false;
        clicked_num = 0;
    }

    update();
}


QString Card::label()
{
    // when the card is not clicked
    // the label is Hanzi
    if (clicked_num == 0) {
        return this->Hanzi;
    }

    // when the card is clicked once
    // the label is meaning in english
    else if (clicked_num == 1) {
        return this->meaning;
    }

    // when the card is clicked twice
    // the label is pronunciation, pinyin
    else if (clicked_num == 2) {
        return this->pinyin;
    }

    // when the card is clicked three times
    // the label is tones of the word
    else {
        QString output;
        // make the QVector into QString
        // because I set label as QString
        // to be viewed as a label of the QPushbutton
        for (int i=0; i<this->tone.count(); i++) {
            std::string t = std::to_string(this->tone[i]);
            QString to_append = QString::fromUtf8(t.c_str());
            output.append(to_append);
        }
        return output;
    }
}

/***
 * it doesn't work well and since the codes are almost the same with Card::label()
 * I made it as comment
 * I think integrating card and cardbutton is necessary
 * so that the codes can better work
 *
void CardButton::change_label(const Card &c) {
    if (clicked_num == 0) {
        this->setText(c.Hanzi);
    }

    else if (clicked_num == 1) {
        this->setText(c.meaning);
    }

    else if (clicked_num == 2) {
        this->setText(c.pinyin);
    }

    else {
        QString output;
        for (int i=0; i<c.tone.count(); i++) {
            std::string t = std::to_string(c.tone[i]);
            QString to_append = QString::fromUtf8(t.c_str());
            output.append(to_append);
        }
        this->setText(output);
    }
    update();
}
****/
