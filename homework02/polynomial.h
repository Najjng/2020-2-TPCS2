//
// Created by Nakyeong Kim on 2020/10/09.
//

#ifndef HOMEWORK02_POLYNOMIAL_H
#define HOMEWORK02_POLYNOMIAL_H

#include <iostream>
#include <vector>
using namespace std;

//class Polynomial; //forward declaration
//I added this forward declaration due to unknown type error in polynomial.cpp (10/07)
//and deleted it again due to incomplete type error in polynomial.cpp (10/08)
//as well as <template class Type> and changed all the given types into int or double

//<template class Type>
class Polynomial
{
private:
    //m_data and m_data_count have data for polynomial
    std::vector<double> m_data;
    size_t m_data_count = 0; //order+1

public:
    //deleted two codes below because I found it redundant
    //Polynomial() = default;
    //Polynomial(size_t order) : m_data(order+1), m_data_count(order+1) {}

    explicit Polynomial(); //construct a polynomial p(x)=0
    Polynomial(const Polynomial &poly);
    explicit Polynomial(size_t order);
    explicit Polynomial(size_t order, const double &fillValue);
    explicit Polynomial(const std::vector<double> &vector);
    Polynomial(const initializer_list<double> &list);

    //operator overloading
    //binary
    Polynomial operator=(Polynomial &); //assignment
    Polynomial operator+=(Polynomial &); //addition assignment
    Polynomial operator-=(Polynomial &); //subtraction assignment

    Polynomial operator+(Polynomial &); //addition
    Polynomial operator-(Polynomial &); //subtraction
    Polynomial operator*(Polynomial &); //multiplication

    //division
    Polynomial operator/(double x); //division with double
    Polynomial operator/(Polynomial &); //quotient from polynomial division

    //comparing
    bool operator==(Polynomial &);
    bool operator!=(Polynomial &);

    //unary
    Polynomial operator+();
    Polynomial operator-();


    double evaluate(int x); //evaluate f(x)=0
    int order(); //order of f(x)
    int size(); //size of f(x)
    void print(); //print polynomials
    Polynomial derivative(); //print derivatives of the polynomial
    double derivative(int x); //evaluate f'(x)=0
};



#endif //HOMEWORK02_POLYNOMIAL_H