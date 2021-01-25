
#include <QTime>

// create application without a graphical ui
#include <QCoreApplication>

 // for pop up alert
#include <QMessageBox>

#include "timer.h"
#include "grid.h"
#include "word.h"


// grid constructor with timer and score
// this is for basic grid layout
// there is a timer and score board
// words will be viewed with initialize function
Grid::Grid(Timer *timer, Score *p) : QGridLayout(){
    // get timer
    this->timer = timer;

    // change count every second
    connect(timer->timer, SIGNAL(timeout()),
            this, SLOT(count_time()));

    this->point = p;

    // create Word objects in the grid
    initialize();
}

// when two words are clicked, check if they are a right match
// if so, remove two cards from the grid
// if not, unclick the two cards
void Grid::check(){

    // count the clicked word buttons
    int clicked_word_count = 0;
    // store the clicked ones
    QWidgetList *clicked_widgets = new QWidgetList;


    // for every card
    for (int i = 0; i < this->count(); i++) // scan all cards
    {
        // cast type as Word, looking at each card
        Word *widget = qobject_cast<Word*>
                (this->itemAt(i)->widget());

        // if card is already clicked,(count=1)
        if(widget->is_clicked != 0){
            // make the card count 2 by increasing 1
            clicked_word_count++;
            // add the card to the collections of clicked
            clicked_widgets->append(widget);
        }

    }

    // if two words are clicked
    if(clicked_word_count == 2){

        // to compare two words
        // save two words at word1 and word2
        Word *word1 = qobject_cast<Word*>(clicked_widgets->at(0));
        Word *word2 = qobject_cast<Word*>(clicked_widgets->at(1));

        // since C++ doesn't have tuple,
        // I just typed them all to compare
        // If the program gets bigger (the number of words gets bigger),
        // using list would be good for extension
        // some words are not recognized as right pairs though they are
        // maybe because of long and/or statement

        // if two clicked cards are a match
        if((word1->text == "我" && word2->text == "I") ||
           (word1->text == "你" && word2->text == "you") ||
           (word1->text == "你好"&& word2->text == "hello") ||
           (word1->text == "好" && word2->text == "good") ||
           (word1->text == "谢谢" && word2->text == "thank you") ||
           (word1->text == "爱" && word2->text == "love") ||
           (word1->text == "看"&& word2->text == "watch") ||
           (word1->text == "吃" && word2->text == "eat") ||
           (word1->text == "他" && word2->text == "he") ||
           (word1->text == "她" && word2->text == "she") ||
           (word1->text == "它" && word2->text =="it") ||
           (word1->text == "喝" && word2->text == "drink") ||
           (word1->text == "水" && word2->text == "water") ||
           (word1->text == "书" && word2->text == "book") ||
           (word1->text == "再见"&& word2->text == "goodbye")){


            // setDisable(true) doesn't allow widget input events
            // except for already clicked words
            // I referred to QT document related to setDisabled
            for (int i = 0; i < this->count(); i++)
            {
                Word *widget = qobject_cast<Word*>
                        (this->itemAt(i)->widget());

                if(QString::compare(word1->text, widget->text) != 0)
                    widget->setDisabled(true);

            }

            // need a second for time to compare and check
            // if the player chose right pair
            QTime waitTime= QTime::currentTime().addSecs(1);
            while (QTime::currentTime() < waitTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            // event loop is started with the start of exec
            // Here I set 50 at the thread of milisecond but it can be changed

            // setDisable(false) allows widget input events
            // I tried to erase these codes because it's not clear to me
            // but without it, the program performs poorly
            for (int i = 0; i < this->count(); i++)
            {
                Word *widget = qobject_cast<Word*>
                        (this->itemAt(i)->widget());

                if(QString::compare(word1->text, widget->text) != 0)
                    widget->setDisabled(false);

            }

            // change the fields of the word1 and word2 each
            // so that new words can be selected
            word1->is_clicked = false;
            word1->is_matched = true;
            word1->close();
            word2->is_clicked = false;
            word2->is_matched = true;
            word2->close();

            // give 10 points for the match
            point->value += 10;
            // change label accordingly
            point->label->setText("Point: " + QString::number(point->value));

            // to check whether the game is finished
            bool is_finished = false;

            for (int i = 0; i < this->count(); i++)
            {
                Word *widget = qobject_cast<Word*>
                        (this->itemAt(i)->widget());

                // if not finished (if not mached)
                if(widget->is_matched == 0){
                    is_finished = false;
                    break;
                }
                // set is_finished true
                is_finished = true;
            }


            // if every pair is matched before the time runs out
            if(is_finished != 0){

                // stop the timer
                this->timer->timer->stop();

                // make a message box for the results
                QMessageBox *box = new QMessageBox;

                // tell the player he won
                box->setWindowTitle("You Won!");
                // and ask if he wants another match
                box->setText("Want Another Game?");

                // act as the player chose
                QAbstractButton* play_again = box->addButton(tr("Play again."), QMessageBox::YesRole);
                QAbstractButton* cancel = box->addButton(tr("No thanks."), QMessageBox::NoRole);

                box->exec();

                if (box->clickedButton()== play_again) {
                    // start a new game
                    new_game();
                } else if(box->clickedButton() == cancel){
                    // quit game
                    timer->reset();
                    timer->timer->stop();
                }

            }


            // if two clicked cards are not a match
        } else {

            // disability to true
            // which doesn't allow the widget input events
            for (int i = 0; i < this->count(); i++)
            {
                Word *widget = qobject_cast<Word*>
                        (this->itemAt(i)->widget());

                if(widget != word1 && widget != word2)
                    widget->setDisabled(true);

            }

            // wait a second
            QTime waitTime= QTime::currentTime().addSecs(1);
            while (QTime::currentTime() < waitTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);


            // disability to false
            // which allows the widget input events
            for (int i = 0; i < this->count(); i++)
            {
                Word *widget = qobject_cast<Word*>
                        (this->itemAt(i)->widget());

                if(widget != word1 && widget != word2)
                    widget->setDisabled(false);

            }

            // unclick the not-matched pair each
            word1->setText(word1->text);
            word1->is_clicked = false;
            word2->setText(word2->text);
            word2->is_clicked = false;
        }
    }
}

// to show words inside grid, use initialize function
// words inside QStringList words will be viewed
void Grid::initialize(){

    // the list of pairs of words to be written under the cards
    QStringList words = {"我", "I", "你", "you", "你好", "hello",
                         "好", "good", "谢谢", "thank you", "爱", "love",
                         "看","watch", "吃", "eat", "他","he", "她", "she",
                         "它","it", "喝", "drink", "水", "water", "书", "book",
                         "再见", "goodbye"};

    // since the game deals with 15 pairs, 30 words
    int total_num = 30;

    // 5 x 6 table full of WordButton objects
    for(int row=0; row<5; row++){
        for(int col=0; col<6; col++){

            // generate a random number so that the words will be located randomly
            // int random can be translated as a random index
            int random = QRandomGenerator::global()->bounded(total_num);
            QString word = words[random];

            // word object to locate
            Word *w = new Word(word, word);

            // remove the word form the list
            words.removeAt(random);
            // decrease total index
            total_num--;

            // QSizePolicy is to regulate the word size
            // so that the size of word buttons won't be changed
            // not to make the grid a mess
            QSizePolicy size = w->sizePolicy();
            size.setRetainSizeWhenHidden(true);
            w->setSizePolicy(size);

            // connect word, signal and slot
            // so that the game works properly:
            // clicking, checking if matched, game end or new game, etc
            QObject::connect(w, SIGNAL(clicked()), w, SLOT(click()));
            QObject::connect(w, SIGNAL(clicked()), this, SLOT(check()));

            // add words to the grid
            this->addWidget(w, row, col, 1, 1);

        }
    }
}

// starts a new game when the user wants to play again or start
void Grid::new_game(){

    // reset the timer to -3
    // -3 is because of the delay I set in timer.h
    this->timer->reset();

    // wait a second
    QTime waitTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < waitTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    // set the point collected to zero
    this->point->value = 0;
    this->point->label->setText("Point: " + QString::number(this->point->value));

    // close widgets from the previous game
    // so that they won't disturb the current game
    for (int i = 0; i < this->count(); i++)
    {
        Word *widget = qobject_cast<Word*>
                (this->itemAt(i)->widget());

        widget->close();
    }

    // make the words to be viewed for the new game
    initialize();
}


// using timer, show how many seconds passed
void Grid::count_time(){

    timer->counter += 1;
    timer->label->setText("Seconds: "+ QString::number(timer->counter));

    // time is up when 100 seconds passed
    if(timer->counter>=100){
        // stop the timer
        timer->timer->stop();

        // setDisabled(true) not to allow other event input
        for (int i = 0; i < this->count(); i++)
        {
            Word *widget = qobject_cast<Word*>
                    (this->itemAt(i)->widget());

            widget->setDisabled(true);
        }

        // when 100 seconds has passed, pop up the alert saying that time is up
        QMessageBox msgBox;
        msgBox.setWindowTitle("Time's up!");

        // show the amount of points the player collected for 100 seconds
        msgBox.setText("You collected " + QString::number(point->value)
                       + " points. You can try again to get more points.");

        // new game
        QAbstractButton* retry = msgBox.addButton(tr("Retry"), QMessageBox::YesRole);
        // stop
        QAbstractButton* cancel = msgBox.addButton(tr("Cancel"), QMessageBox::NoRole);

        msgBox.exec();

        // follow the player's choice
        if (msgBox.clickedButton()== retry) {
            // start a new game if the player wants
            new_game();
        } else if(msgBox.clickedButton() == cancel){
            // or stop the timer and the game
            timer->reset();
            timer->timer->stop();
        }
    }
}
