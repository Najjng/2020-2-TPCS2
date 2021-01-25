#ifndef CARD_H
#define CARD_H

#include <QRect>
#include <QString>
#include <QVector>
#include <QPushButton>

// Card object that has Chinese word and its features
// features are Hanzi(chinese character), meaning in English, pinyin(pronunciation), and a vector of tones
class Card : public QWidget
{
    Q_OBJECT
public:
    // constructor
    Card(const QString Hanzi, const QString meaning, const QString pinyin, const QVector<int> tone);

    // save features
    QString Hanzi;
    QString meaning;
    QString pinyin;
    QVector<int> tone;

    // to change the feature shown following the number clicked
    int clicked_num;


public slots:
    // get the label according to the number clicked
    QString label();

};

// CardButton object using QPushButton
// I made CardButton because Card(const QString initialize, const QString& text, QWidget* parent = 0) didn't work
// If the code above worked, I would not have made this separate class
// and the codes must have been easier
class CardButton : public QPushButton
{
    Q_OBJECT
public:
    // constructor
    CardButton(const QString initialize, const QString& text, QWidget* parent = 0);

    // label of the Qpushbutton
    QString label;

    // the number the button is clicked
    int clicked_num;
    // if the clicked_num is 0, is_clicked is false
    // else, it's true
    bool is_clicked;

    // this function was made to change the label of the QPushbutton
    // in order to use in QObject::connect
    // but it still doesn't work well
    // void change_label(const Card &c);

public slots:
    // to get the mouse click input
    void click();

};

/***
 * These features below will be used if the program grows bigger
 * In this simple initial program, I don't need to separate these small features as class
 * But as the program grows bigger and each feature needs to have their own feature,
 * (such as pinyin having its own file with the voice reading it)
 * the features can be separated at that point.
 *
 *
class Hanzi{
public:
    QString words;
    Hanzi() = default;
    Hanzi(QString &word){
        words = word;
    }
};


class meaning{
public:
    QString meanings;
    meaning() = default;
    meaning(QString &mean_in_eng){
        meanings = mean_in_eng;
    }
};


class pinyin{
public:
    QString pinyins;
    pinyin() = default;
    pinyin(QString &pinyin_in_eng){
        pinyins = pinyin_in_eng;
    }
};


class tone{
public:
    QVector<int> tones_vec;
    tone() = default;
    tone(QVector<int> &tones){
        tones_vec = tones;
    }

};
***/


#endif // CARD_H

