
#include "Complex.h"
#include <cstdlib>
#include <iostream>
#include "ComplexArray.h"
using namespace std;

/*
 * 
 */
int main() {

    int first, second;
    string op;
    Complex c1(4.0,6.0),c2, add,sub,mult,div, answer;
    c2.SetA(4.23);
    c2.SetB(5.76);

    cout << "c1: ";
    c1.Print();
    cout << "c2: ";
    c2.Print();
    
    cout << "c1 + c2: ";
    add = c1.Add(c2);
    add.Print();

    cout << "c1 - c2: ";
    sub = c1.Sub(c2);
    sub.Print();

    cout << "c1 * c2: ";
    mult = c1.Mul(c2);
    mult.Print();
    
    cout << "c1 / c2: ";
    div = c1/c2;
    div.Print();
    
    
    ComplexArray arr;
    arr.Read("ComplexNumbers.txt");
    arr.Print();
  
    cout << "Enter index of first number(1-20): ";
    cin >> first;
    Complex user1(arr.GetValue(first-1));
    cout << endl << "Enter index of second number(1-20): ";
    cin >> second;
    Complex user2(arr.GetValue(second-1));
    cout << endl << "Add(a), Subtract(s), Multiply(m), or Divide(d) these? ";
    cin >> op;
    cout << endl << endl;
    if (op == "a")
        answer = user1.Add(user2);
    else if (op == "s")
        answer = user1.Sub(user2);
    else if (op == "m")
        answer = user1.Mul(user2);
    else if (op == "d")
        answer = user1/user2;
    else
        cerr << "Invalid answer." << endl;
    cout << "The answer is: ";
    answer.Print();
    return 0;
}

