#include "ComplexArray.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

ComplexArray::ComplexArray() 
{
    int i = 0;
    for (int x = 0; x < SIZE; x++)
    {
        SafeArray[x].SetA(i+1);
        SafeArray[x].SetB(i+2);
    }
        
}

ComplexArray::ComplexArray(const ComplexArray& orig) 
{
    for (int i = 0; i < SIZE; i++)
        SafeArray[i] = orig.SafeArray[i];
}

ComplexArray::~ComplexArray() {
}

void ComplexArray::Read(string filename)
{
    double TempA, TempB;
    ifstream infile;
    int i = 0;    
    infile.open(filename.c_str());
    if (!infile)
    {
        cerr << "Could not open file." << endl;
    }
    while(!infile.eof()&& i < SIZE)
    {
        infile >> TempA;
        SafeArray[i].SetA(TempA);
        infile >> TempB;
        SafeArray[i].SetB(TempB);
        i++;
    }
    infile.close();
}
void ComplexArray::Print()
{
    cout << "Complex numbers in array: " << endl;
    for (int i = 0; i < SIZE; i++)
         cout << "(" << SafeArray[i].GetA() << " + " << SafeArray[i].GetB() << "i) " << endl;
}
Complex ComplexArray::GetValue(int index)
{
    return SafeArray[index];
}

