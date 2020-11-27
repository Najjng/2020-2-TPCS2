//
// Created by Nakyeong Kim on 2020/11/27.
//

#include <iostream>
#include <utility>
#include <vector>
#include <string>

class Hanzi{
public:
    std::string words;
    Hanzi() = default;
    Hanzi(std::string &word){
        words = word;
    }
};


class meaning{
public:
    std::string meanings;
    meaning() = default;
    meaning(std::string &mean_in_eng){
        meanings = mean_in_eng;
    }
};


class pinyin{
public:
    std::string pinyins;
    pinyin() = default;
    pinyin(std::string &pinyin_in_eng){
        pinyins = pinyin_in_eng;
    }
};


class tone{
public:
    std::vector<int> tones_vec;
    tone() = default;
    tone(std::vector<int> &tones){
        tones_vec = tones;
    }

};


template <class Type>
class Card{
public:
    Card() = default;
    Card(const Hanzi, const meaning, const pinyin, const tone);
};


int main() {

}