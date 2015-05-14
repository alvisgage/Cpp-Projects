#include "Complex.h"
#include <iostream>
#include <math.h>
using namespace std;

Complex::Complex() 
{
    NumberA = 1.0;
    NumberB = 2.0;
}
Complex::Complex(double A, double B)
{
    NumberA = A;
    NumberB = B;
}

Complex::Complex(const Complex& orig) 
{
    NumberA = orig.NumberA;
    NumberB = orig.NumberB;
}
Complex::~Complex() {
}
void Complex::Print()
{
    cout << "(" << NumberA << " + " << NumberB << "i) " << endl;;
}
void Complex::SetA(double A)
{
    NumberA = A;
}
void Complex::SetB(double B)
{
    NumberB = B;
}
double Complex::GetA()
{
    return NumberA;
}
double Complex::GetB()
{
    return NumberB;
}
Complex Complex::Add(Complex& Obj)
{
    double a,b;
    a = NumberA + Obj.NumberA;
    b = NumberB + Obj.NumberB;
    Complex add(a,b);
    return add;
}
Complex Complex::Sub(const Complex& Obj)
{
    double a,b;
    a = NumberA - Obj.NumberA;
    b = NumberB - Obj.NumberB;
    Complex sub(a,b);
    return sub;
}
Complex Complex::Mul(const Complex& Obj)
{
    double a,b;
    a = (NumberA*Obj.NumberA) - (NumberB*Obj.NumberB);
    b = (NumberB*Obj.NumberA) + (NumberA*Obj.NumberB);
    Complex mul(a,b);
    return mul;
}
Complex Complex::operator /(const Complex& right)
{
    double a,b;
    a = ((NumberA*right.NumberA)+(NumberB*right.NumberB))/(pow(right.NumberA,2)+pow(right.NumberB,2));
    b = ((NumberB*right.NumberA)-(NumberA*right.NumberB))/(pow(right.NumberA,2)+pow(right.NumberB,2));
    Complex div(a,b);
    return div;
}
