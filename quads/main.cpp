#include <iostream>
#include <cmath>
using namespace std;

class quadratic
{
public:
    quadratic();
    quadratic(const quadratic &orig);
    ~quadratic();
    int getQuad() const;
    void setQuad(const int a, const int b, const int c);
    void Add(const quadratic &equation);
    void Sub(const quadratic &equation);
    int Eval();
    void Print() const;
    int Derive();
    void Zeros(float&,float&);

    private:
        float A,B,C;
};
quadratic::quadratic()
{

   A = 0;
   B = 0;
   C = 0;
}
quadratic::quadratic(const quadratic &orig)
{
   A = orig.A;
   B = orig.B;
   C = orig.C;
}

quadratic::~quadratic()
{

}

int quadratic::getQuad() const
{
   return(A, B, C);
}

void quadratic::setQuad(const int a, const int b, const int c)
{
   A = a;
   B = b;
   C = c;
}

void quadratic::Print() const
{
   cout << A << "x^2+" << B << "x+" << C;
}


void quadratic::Add(const quadratic &equation)
{
   A+=equation.A;
   B+=equation.B;
   C+=equation.C;
}


void quadratic::Sub(const quadratic &equation)
{
   A-=equation.A;
   B-=equation.B;
   C-=equation.C;
}


int quadratic::Eval()
{

   const int x = 5;

   A = A * (x*x);
   B = B * x;
   C = C;
   int total=A+B+C;

   return total;

}
int quadratic::Derive(){
    int d = 2*A + B;
    return d;
}
void quadratic::Zeros(float& pos_z, float& neg_z){       
    pos_z = ((B*-1) + sqrt(B*B - 4*A*C))/2*A;
    neg_z = ((B*-1) - sqrt(B*B - 4*A*C))/2*A;   
}


int main()
{

   quadratic equation1;
   quadratic equation2;
   quadratic equation3;
   quadratic orig;

   equation2.setQuad(-5, 3, 8);
   equation1.setQuad(2, 5, 1);
   equation1.Print();
   cout << endl;
   equation2.Print();
   cout << endl;


   equation1.getQuad();
   equation2.getQuad();
   equation1.Add(equation2);
   equation1.Print();
   cout << endl;
   
   equation1.Sub(equation2);
   equation1.Print();
   
   int tot = equation1.Eval();
   cout <<"\ntotal: " << tot << endl;
   
   float pos_z,neg_z;
   equation1.Zeros(pos_z,neg_z);
   cout <<"\npositive z: " << pos_z << "\nnegative z: " << neg_z << endl;

   return(0);
}
