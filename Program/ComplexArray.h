#include "Complex.h"
#include <string>
using namespace std;

const int SIZE = 20;
class ComplexArray
{
private:
   Complex SafeArray[SIZE];
public:
   ComplexArray (); // default Constructor
   ComplexArray (const ComplexArray &orig); //Copy Constructor
   ~ ComplexArray (); // Destructor
   void Read(string Filename);
   void Print(); // Print function
   Complex GetValue(int index); // return index value in array
};
