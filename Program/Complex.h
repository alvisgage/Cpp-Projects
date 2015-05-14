#ifndef Complex_h
#define Complex_h

class Complex
{
private:
   double NumberA;
   double NumberB;
public:
   Complex(); // default Constructor
   Complex(double A, double B); // non-default constructor
   Complex(const Complex &orig); //Copy Constructor
   ~ Complex(); // Destructor
   void SetA(double A);
   void SetB(double B);
   double GetA();
   double GetB();
   Complex Add(Complex &Obj); // addition
   Complex Sub(const Complex &Obj); // Subtraction
   Complex Mul(const Complex &Obj);  // Multiplication
   Complex operator/(const Complex &right); // Overloaded / operator
   void Print(); // Print function
};

#endif
