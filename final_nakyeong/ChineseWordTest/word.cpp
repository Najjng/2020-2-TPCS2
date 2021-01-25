#include "word.h"

Word::Word(QString initialize ,const QString& text, QWidget* parent)
    : QPushButton(initialize, parent)
{
    // Word contains its own text
    this->text = text;
    // is_clicked is set to be false in default
    this->is_clicked = false;
    // is_matched is set to be false in default
    this->is_matched = false;
    // to make the button border is raised
    setFlat(true);
    // painting background with the same color of word buttons
    setAutoFillBackground(true);
    // update with the changes above
    update();
}

// click function that acts as the Word is clicked
void Word::click(){
    // set text with Word
    this->setText(text);
    //when clicked, is_clicked becomes true
    this->is_clicked = true;
    // update with the changes above
    update();
}
