//
// Created by Nakyeong Kim on 9/30/20.
// SNU-ID: 2018-15185
// Homework 02
//
// In this homework we will solve several problems related to polynomials
//
// (1) I made a Polynomial class that can be made with various parameters
// such as vector, order, order with fillvalue and initializer list.
//
// (2) To check if the operators work well, there's a print function.
// Polynomials are printed in an ascending order.
// for example, 1 + 2x - 3x^2 + 4x^3
//
// (3) Polynomials can be added, subtracted, multiplied and divided.
// Addition and Subtraction are also working in unary way.
//
// (4) evaluate, order, size, derivative functions are available as well.
//
// Other comments
// (1) I tried to save test functions in different source and header files
// but it didn't work well so I just decided to leave it in main.cpp
//
// (2) When I tried to use template in polynomial.h to make class,
// there was unknown type error which required forward declaration.
// but forward declaration caused another error called incomplete type error.
// Since these errors didn't occur when not using template,
// I decided not to use template in Polynomial class.
// You can check it in polynomial.h
//

#include <iostream>
#include <string>
#include "polynomial.h"
using namespace std;

//functions to test
//all the functions to test were written in boolean

//test_zero_input() is making two polynomials
//whose orders are 2 but filled with 0s
//and two zero polynomials are equal
bool test_zero_input() {
    Polynomial p1(2, 0);
    Polynomial p2(2, 0);
    return p1 == p2;
}

//test_simple_input() is making two polynomials by different ways
//whose orders are 2 and filled with 1
//and two polynomials are equal
bool test_simple_input() {
    Polynomial p1(2, 1.0);
    Polynomial p2{1.0, 1.0, 1.0};
    return p1 == p2;
}

//test_addition() is to see if the addition of two polynomials is equal to
//the one I calculated by hand
bool test_addition() {
    Polynomial p1(2, 1.0);
    Polynomial p2{2.0, 1.0};
    Polynomial p3{3.0, 2.0, 1.0};
    Polynomial p4 = p1 + p2;
    return p3 == p4;
}

//test_subtraction() is to see if the subtraction of one polynomial from the other is equal to
//the one I calculated by hand
bool test_subtraction() {
    Polynomial p1{1.5, 2.5, 3.3};
    Polynomial p2(2, 1.0);
    Polynomial p3 = p1 - p2;
    Polynomial p4{0.5, 1.5, 2.3};
    return p3 == p4;
}

//test_multiplication() is to see if the multiplication of two polynomials is equal to
//the one I calculated by hand
bool test_multiplication() {
    Polynomial p1(1, 1.0);
    Polynomial p2{1.0, 2.0, 1.0};
    return p1*p1 == p2;
}

//I made three test_division functions
//test_division1() is a division of polynomial by a double
bool test_division1() {
    Polynomial p1(2, 2.0);
    Polynomial p2(2, 1.0);
    return (p1/2) == p2;
}

//test_division2() is as division of 2nd order polynomial by 1st order polynomial
bool test_division2() {
    Polynomial p1{1.0, 2.0, 1.0};
    Polynomial p2(2, 1.0);
    return (p1/p2) == p2;
}


//test_division3() is as division of 3rd order polynomial by 2nd order polynomial
bool test_division3() {
    Polynomial p1{1, 3, 3, 1};
    Polynomial p2{1, 2, 1};
    Polynomial p3(1, 1);
    Polynomial p4 = p1/p2;
    return p4 == p3;
}

//test_unary_addition() is to see if p1 and +p1 are the same
bool test_unary_addition() {
    Polynomial p1(5, 3);
    Polynomial p2 = +p1;
    return p1 == p2;
}

//test_unary_subtraction() is to see
//if p2 whose absolute values are same with p1's but are actually negative and -p1 are the same
bool test_unary_subtraction() {
    Polynomial p1(5, 3);
    Polynomial p2(5, -3);
    Polynomial p3 = -p1;
    return p2 == p3;
}

//test_evaluation() is to see if the evaluation functions evaluates correctly
bool test_evaluation() {
    Polynomial p1(4, 1);
    return p1.evaluate(3) == 121;
}

//test_derivative1() is to see if a polynomial made by derivative function is really a derivative
bool test_derivative1() {
    Polynomial p1(4, 1);
    Polynomial p2 = p1.derivative();
    Polynomial p3{1, 2, 3, 4};
    return p2 == p3;
}

//test_derivative2() is to see the evaluation of a derivative works correctly
bool test_derivative2() {
    Polynomial p1(2, 1);
    return p1.derivative(1) == 3;
}

//function that prints the result of testing
template <class TestFunction>
void run_test(TestFunction test_function, const string& test_name) {
    if (test_function()){
        cout << "PASS: " << test_name << "\n";
    }
    else{
        cout << "FAIL: " << test_name << "\n";
    }
}


int main(void)
{
    run_test(test_zero_input, "test_zero_input(Making Polynomials only with Zeros)");
    run_test(test_simple_input, "test_simple_input(Making Simple Polynomials)");
    run_test(test_addition, "test_addition(Addition between Two Polynomials)");
    run_test(test_subtraction, "test_subtraction(Subtraction of One Polynomial from the Other)");
    run_test(test_multiplication, "test_multiplication(Multiplication between Two Polynomials)");
    run_test(test_division1, "test_division1(Division of a Polynomial by a Double)");
    run_test(test_division2, "test_division2(Division of a Polynomial by a Polynomial)");
    run_test(test_division3, "test_division3(Division of a Polynomial by a Polynomial)");
    run_test(test_unary_addition, "test_unary_addition(Showing a Polynomial p2=+p1 is equal to Polynomial p1)");
    run_test(test_unary_subtraction, "test_unary_subtraction(Showing a Polynomial p2=-p1 is equal to Polynomial -p1)");
    run_test(test_evaluation, "test_evaluation(Evaluation of a Polynomial with an Integer");
    run_test(test_derivative1, "test_derivation1(Derivative of a Polynomial)");
    run_test(test_derivative2, "test_derivation2(Evaluation of a Derivative of a Polynomial");

    cout << "\n";

    //lines below are added to show the printing function
    cout << "Print Functions Works as Below \n";
    Polynomial p1(2, 1);
    p1.print();
    Polynomial p2(11, 1);
    p2.print();

    /***

    //Below is the original code I wrote before learning testing.
    //I tried to write testing functions based on what I wrote before.

    //making polynomials
    cout<<"Test of Making Polynomials \n";

    Polynomial p1(2, 1.0);
    Polynomial p2 {1.0, 0, 1.5, 3, 2};

    cout<<"p1 is: ";
    p1.print();

    cout<<"p2 is: ";
    p2.print();

    //addition
    cout<<"Test of Adding TWo Polynomials \n";
    cout<<"The result of p1 + p2 is:  ";
    Polynomial p3 = p1 + p2;
    p3.print();

    //subtraction
    cout<<"Test of Subtracting One Polynomial from the Other \n";
    cout<<"The result of p2 - p1 is:  ";
    Polynomial p4 = p2 - p1;
    p4.print();

    //multiplication
    cout<<"Test of Multiplying Two Polynomials \n";
    cout<<"The result of p1 * p2 is:  ";
    Polynomial p5 = p1 * p2;
    p5.print();

    //division
    cout<<"Test of Dividing One Polynomial by Double \n";
    cout<<"The result of p1 / 2.0 is:  ";
    Polynomial p6 = p1 / 2.0;
    p6.print();


    //unary operators
    cout<<"Test of += and -= operators \n";
    cout<<"The result of p2 += p1 is:  ";
    p2 += p1;
    p2.print(); //returns p2 + p1

    cout<<"The result of p2 -= p1 is:  ";
    p2 -= p1;
    p2.print(); //back to original p2

    cout<<"Test of Unary + and - Operators \n";
    Polynomial p7 = +p1;
    p7.print();
    Polynomial p8 = -p1;
    p8.print();

    //assignment overloading
    cout<<"Test of Assignment Operators \n";
    cout<<"When p3=p2;, p3 is:  ";
    p3 = p2;
    p3.print();

    //boolean operators
    cout<<"Test of Boolean Operators \n";
    cout<<"p1==p2 is:  ";
    bool a = (p1 == p2);
    cout<< a << "\n";
    cout<<"p1!=p2 is:  ";
    bool b = (p1 != p2);
    cout<< b << "\n";


    //evaluate(x)
    cout<<"Test of Evaluation \n";
    cout<<"The result of p1(3) is: ";
    p1.evaluate(3);
    cout<<"\n";
    cout<<"The result of p2(5) is: ";
    p2.evaluate(5);
    cout<<"\n";

    //derive()
    cout<<"Test of Derivation \n";
    cout<<"The result of p1.derive() is: ";
    p1.derive();

    cout<<"The result of p1.derive(3) is: ";
    p1.derive(3);

    cout<<"\n";

    //division between polynomials
    //the division below is the only correct output that I can get with the codes I wrote
    //When I run the codes with different polynomials,
    //there often come wrong coefficients.
    //I tried to fix it for a few days, but couldn't fix it on time.
    cout<<"The result of p1{1, 2, 1} / p2{1, 1} is: ";
    Polynomial p9 {1, 2, 1};
    Polynomial p10 {1, 1};
    Polynomial p11 = p1 / p2;
    p3.print();
     ***/
}
