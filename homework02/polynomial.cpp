//
// Created by Nakyeong Kim on 2020/10/09.
//

#include <iostream>
#include <vector>
#include <cmath> //to use pow in evaluate function
#include "polynomial.h"
using namespace std;

Polynomial::Polynomial()
{
    m_data_count = 0;
}

//make a polynomial with given order
//all the values are 1 in default
Polynomial::Polynomial(size_t order) {
    m_data_count = order+1;
    m_data.assign(m_data_count, 1);
}

//make a polynomial with given order and given value
//for example, Polynomial p(2, 1) is equal to 1 + x + x^2
Polynomial::Polynomial(size_t order, const double &fillValue){
    m_data_count = order+1;
    m_data.assign(m_data_count, fillValue);
}

//make a polynomial with given vector of doubles in an ascending order
Polynomial::Polynomial(const std::vector<double> &vector){
    m_data_count = vector.size();
    for (int i=0; i < m_data_count; i++){
        m_data[i] = vector[i];
    }
}

//make a polynomial with given initializer list of doubles in an ascending order
Polynomial::Polynomial(const initializer_list<double> &list){
    m_data_count = list.size();
    for (double x: list){
        m_data.push_back(x);
    }
}

//make a copy of the input polynomial
Polynomial::Polynomial(const Polynomial &poly){
    m_data_count = poly.m_data_count;
    m_data = poly.m_data;
}


//Operators/Constructors


//operator = between two polynomials
//for example, p1 = p2 form
Polynomial Polynomial::operator=(Polynomial &b){
    if (this == &b){
        return *this;
    }
    else{
        m_data_count = b.m_data_count;
        m_data = b.m_data;
        return *this;
    }
}

//operator += between two polynomials
//add the right hand side(RHS) polynomial to left hand side(LHS) polynomial
//LHS += RHS
Polynomial Polynomial:: operator+=(Polynomial &b){
    //when the length of RHS polynomial is equal to or longer than LHS polynomial
    if (this->size() <= b.size()){
        //add values of RHS at each coefficient existing in LHS
        for (int i=0; i<this->size(); i++) {
            m_data[i] += b.m_data[i];
        }
        //add surplus values of RHS, which were not added before, at the end of LHS
        for (int i = this->size(); i < b.size(); i++){
            m_data.push_back(b.m_data[i]);
        }
    }
    //when the length of LHS is longer than RHS
    else {
        //add existing values of RHS at corresponding coefficient in LHS
        for (int i = 0; i < b.size(); i++) {
            m_data[i] += b.m_data[i];
        }
    }
    return *this; //return self
}

//operator -= between two polynomials
//subtract the right hand side(RHS) polynomial from left hand side(LHS) polynomial
//LHS -= RHS
Polynomial Polynomial:: operator-=(Polynomial &b){
    //when the length of RHS polynomial is equal to or longer than LHS polynomial
    if (this->size() <= b.size()){
        //subtract values of RHS from each coefficient existing in LHS
        for (int i=0; i<this->size(); i++) {
            m_data[i] -= b.m_data[i];
        }
        //subtract surplus values of RHS, which were not subtracted before, at the end of LHS
        for (int i = this->size(); i < b.size(); i++){
            m_data.push_back((-1) * b.m_data[i]);
        }
    }
    //when the length of LHS is longer than RHS
    else{
        //subtract existing values of RHS from corresponding coefficient in LHS
        for (int i=0; i<b.size(); i++) {
            m_data[i] -= b.m_data[i];
        }
    }
    return *this;
}

//operator + between two polynomials
//return a new polynomial, which is the addition between two
Polynomial Polynomial::operator+(Polynomial &b){
    //declare bigger and smaller count of polynomials for better calculation hereafter
    //bigger count means the bigger count between two polynomials
    //small count as well
    int bigger_count = (this->size() > b.size()) ? this->size()  : b.size();
    int smaller_count = (this->size()  > b.size()) ? b.size() : this->size();

    //declare Polynomial c with order for the output
    //if the order is not given, here comes a bad access error
    //because of allocated memory
    Polynomial c(bigger_count-1);
    //count is automatically loaded as below
    //c.m_data_count = bigger_count;

    //add coefficients from two polynomials
    // til there's no corresponding coefficient to each other
    for (int i=0; i < smaller_count; i++){
        c.m_data[i] = m_data[i] + b.m_data[i];
    }
    //when the counts of two polynomials are different
    //the surplus values of the polynomial with bigger counts are put into a new polynomial
    for (int i = smaller_count;i<c.m_data_count;i++){
        if (this->size() > b.size()){
            c.m_data[i] = m_data[i];
        }
        //
        else {
            c.m_data[i] = b.m_data[i];
        }
    }
    return c; //return new polynomial as an output
}

//operator - between two polynomials
//return a new polynomial, which is the result of subtraction
Polynomial Polynomial::operator-(Polynomial &b){
    //declare bigger and smaller count of polynomials for better calculation hereafter
    int bigger_count = (this->size() > b.size()) ? this->size()  : b.size();
    int smaller_count = (this->size()  > b.size()) ? b.size() : this->size();

    //declare Polynomial c with order for the output
    Polynomial c(bigger_count-1);
    //count is automatically loaded as below
    //c.m_data_count = bigger_count;

    //subtract coefficients of the latter from the former
    //til there's no corresponding coefficient to each other
    for (int i=0; i < smaller_count; i++){
        c.m_data[i] = m_data[i] - b.m_data[i];
    }
    //when the counts of two polynomials are different
    //the surplus values * (-1) of the polynomial with bigger counts are put into a new polynomial
    for (int i = smaller_count; i<c.size(); i++){
        if (this->size() > b.size()){
            c.m_data[i] = (-1) * m_data[i];
        }
        else {
            c.m_data[i] = (-1) * b.m_data[i];
        }
    }
    return c; //return new polynomial as an output
}

//operator * between two polynomials
//return a new polynomial, which is the result of multiplication
Polynomial Polynomial::operator*(Polynomial &b){

    //declare Polynomial c with order for the output
    Polynomial c(this->order() + b.order());
    //count is automatically loaded as below
    //c.m_data_count = m_data_count + b.m_data_count;
    c.m_data.assign(c.size(), 0); //initialize the polynomial with zeros

    //nested for loop for multiplication
    for (int i = 0; i<this->size(); i++){
        for (int j = 0; j<b.size(); j++){
            c.m_data[i+j] += m_data[i]*b.m_data[j];
        }
    }
    return c; //return new polynomial as an output
}

//operator / between a polynomial and a double
//return a new polynomial, which is the result of division
Polynomial Polynomial::operator/(double x){

    //declare Polynomial c with order for the output
    Polynomial c(this->order());

    //divide every coefficient with x
    for (int i=0; i<this->size(); i++){
        c.m_data[i] = m_data[i]/x;
    }
    return c; //return new polynomial as an output
}

//operator / between two polynomials
//return a new polynomial, which is a quotient from polynomial division
Polynomial Polynomial::operator/(Polynomial &b){
    Polynomial c(this->order() - b.order());
    //here I tried to write codes based on polynomial long divisions
    for (int i=0; i<c.size(); i++) {
        c.m_data[c.order()-i] = m_data[this->order()-i]/ b.m_data[b.order()]; //start dividing from highest order
        for (int j=1; j<b.size(); j++){
            m_data[this->order()-i-j] -= c.m_data[c.order()-i]*b.m_data[b.order()-j];
            //subtract (calculated quotient * coefficients of divisor) for further calculation
        }
    }
    return c;
}


//unary operators +
//return a polynomial as a copy of the given polynomial
Polynomial Polynomial::operator+(){

    //declare Polynomial c with order for the output
    Polynomial c(this->order());

    //copy the data
    c.m_data = m_data;
    return c; //return new polynomial as an output
}

//unary operators -
//return a polynomial as a copy of the given polynomial
Polynomial Polynomial::operator-(){

    //declare Polynomial c with order for the output
    Polynomial c(this->order());

    //copy the data with multiplying (-1) on each element
    for (int i=0; i < this->size(); i++) {
        c.m_data[i] = (-1) * m_data[i];
    }
    return c; //return new polynomial as an output
}

bool Polynomial::operator==(Polynomial &b){
    for (int i=0; i<this->size(); i++){
        if (m_data[i] != b.m_data[i]){
            return 0;
        }
    }
    return 1;
}

bool Polynomial::operator!=(Polynomial &b){
    if (*this == b){
        return 0;
    }
    else{
        return 1;
    }
}



//Functions

//function order() returns the order
//which is m_data_count+1
int Polynomial::order(){
    return static_cast<int>(m_data_count) -1; //to change size_t into int
}

//function size() returns the size of the polynomial
//which is m_data_count
int Polynomial::size() {
    return m_data_count;
}

//function evaluate(x)
//evaluate the polynomial with given integer x
double Polynomial::evaluate(int x){
    double e = 0; //double e for the output
    e += m_data[0]; //add the constant to the output
    for (int i=1; i<m_data_count; i++){
        //evaluate the multiplication of coefficient and power of x
        //and add it to e
        e += m_data[i] * pow(x, i);
    }

    return e; //return the output
}

//function print() prints the polynomial in ascending order
//and doesn't return anything
void Polynomial::print() {
    //if the number of coefficients is larger than or equal to 10
    //I want to show only the first two and last two coefficients
    if (this->size() >= 10) {
        //when the first coefficient is not zero
        if (m_data[0] != 0) {
            //and when the second coefficient is positive
            if (m_data[1] > 0) {
                if (m_data[1] == 1.0) {
                    cout << m_data[0] << " +x "; //when the value is 1, don't show 1
                } else {//it will be in a + bx ... form
                    cout << m_data[0] << " +" << m_data[1] << "x ";
                }
            }
                //or when the second coefficient is negative
            else if (m_data[1] < 0) {
                if (m_data[1] == -1.0) {
                    cout << m_data[0] << " -x "; //when the value is -1, don't show -1
                } else {
                    //it will be in a - bx ... form
                    cout << m_data[0] << " " << m_data[1] << "*x ";
                }
            }
                //or when the second coefficient is zero
            else {
                //it will be in a ... form
                cout << m_data[0] << " ";
            }
        }
            //when the first coefficient is zero
        else {
            //and the second coefficient is not zero
            if (m_data[1] != 0) {
                if (m_data[1] == 1.0) {
                    cout << "x "; //when the value is 1, don't show 1
                } else if (m_data[1] == -1.0) {
                    cout << "-x "; //when the value is -1, don't show -1
                }
                    // it will be in a bx ... form
                else {
                    cout << m_data[1] << "*x ";
                }
            }
                //when both first and second coefficients are zero
            else {
                //print nothing here
            }
        }

        cout << "... ";

        //for coefficients from the index 2
        for (int i = this->order()-1; i < this->size(); i++) {
            if (m_data[i] > 0) {
                if (m_data[i] == 1.0) {
                    cout << "+x^" << i << " "; //when the value is 1, don't show 1
                } else {
                    cout << "+" << m_data[i] << "*x^" << i << " ";
                }
            } else if (m_data[i] < 0) {
                if (m_data[i] == -1.0) {
                    cout << "-x^" << i << " "; //when the value is -1, don't show -1
                } else {
                    cout << m_data[i] << "*x^" << i << " ";
                }
            } else {
                //do nothing
            }
        }
    }
    //if the number of coefficients is smaller than 10
    else {
        //when the first coefficient is not zero
        if (m_data[0] != 0) {
            //and when the second coefficient is positive
            if (m_data[1] > 0) {
                if (m_data[1] == 1.0) {
                    cout << m_data[0] << " +x "; //when the value is 1, don't show 1
                } else {//it will be in a + bx ... form
                    cout << m_data[0] << " +" << m_data[1] << "x ";
                }
            }
                //or when the second coefficient is negative
            else if (m_data[1] < 0) {
                if (m_data[1] == -1.0) {
                    cout << m_data[0] << " -x "; //when the value is -1, don't show -1
                } else {
                    //it will be in a - bx ... form
                    cout << m_data[0] << " " << m_data[1] << "*x ";
                }
            }
                //or when the second coefficient is zero
            else {
                //it will be in a ... form
                cout << m_data[0] << " ";
            }
        }
            //when the first coefficient is zero
        else {
            //and the second coefficient is not zero
            if (m_data[1] != 0) {
                if (m_data[1] == 1.0) {
                    cout << "x "; //when the value is 1, don't show 1
                } else if (m_data[1] == -1.0) {
                    cout << "-x "; //when the value is -1, don't show -1
                }
                    // it will be in a bx ... form
                else {
                    cout << m_data[1] << "*x ";
                }
            }
                //when both first and second coefficients are zero
            else {
                //print nothing here
            }
        }

        //here I tried to write a code that works
        //when all coefficients in front of a positive coefficient are zero
        //so when Polynomial p {0, 0, 0, 0, 5} is given
        //I want it to be printed as 5x^4
        //not +5x^4
        //but it didn't work well
        //maybe because I separated codes with exponential by 0/1 and larger than 1

        //for coefficients from the index 2
        for (int i = 2; i < this->size(); i++) {
            if (m_data[i] > 0) {
                if (m_data[i] == 1.0) {
                    cout << "+x^" << i << " "; //when the value is 1, don't show 1
                } else {
                    cout << "+" << m_data[i] << "*x^" << i << " ";
                }
            } else if (m_data[i] < 0) {
                if (m_data[i] == -1.0) {
                    cout << "-x^" << i << " "; //when the value is -1, don't show -1
                } else {
                    cout << m_data[i] << "*x^" << i << " ";
                }
            } else {
                //do nothing
            }
        }
    }
    cout << "\n";
}

//function derivative() prints the derived form of the given polynomial
Polynomial Polynomial::derivative(){
    Polynomial c(this->order()-1);
    for (int i=1; i<this->size(); i++){
        c.m_data[i-1] = m_data[i] * i;
    }
    //c.print();
    return c;
}

//function derive(x) prints and returns the evaluated result of derived polynomial
double Polynomial::derivative(int x){
    Polynomial c(this->order()-1);
    for (int i=1; i<this->size(); i++){
        c.m_data[i-1] = m_data[i] * i;
    }
    return c.evaluate(x);
}