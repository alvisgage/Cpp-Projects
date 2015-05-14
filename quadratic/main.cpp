/* 
 * File:   main.cpp
 * Author: Rage Gage
 *
 * Created on November 19, 2012, 6:07 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

class quad{
private:
    int a,b,c;
public:
    quad(int,int,int);
    void add(quad&,quad&);
    void sub(quad&,quad&);
    void print();
    void set(int,int,int);
    void mult(quad&,quad&);
    quad operator+(const quad&);
    quad operator-(quad&);
    quad operator*(quad&);
};
quad::quad(int x=1, int y=1, int z=1){
    a=x;
    b=y;
    c=z;
}
quad quad::operator *(quad&other){
    quad newquad;
    newquad.mult(*this,other);
    return newquad;
}
quad quad::operator -(quad&other){
    quad newquad;
    newquad.sub(*this,other);
    return newquad;
}
quad quad::operator +(const quad&other){
    quad newquad(this->a+other.a,this->b+other.b,this->c+other.c);
    return newquad;
}
void quad::mult(quad&one,quad&two){
    a=one.a*two.a;
    b=one.b*two.b;
    c=one.c*two.c;
}
void quad::print(){
    cout <<a<<"x^2 + " <<b<<"x + " <<c;
}
void quad::add(quad &one,quad &two){
    a=one.a+two.a;
    b=one.b+two.b;
    c=one.c+two.c;
}
void quad::sub(quad &one,quad &two){
    a=one.a-two.a;
    b=one.b-two.b;
    c=one.c-two.c;
}
void quad::set(int x,int y,int z){
    a=x;
    b=y;
    c=z;
}



int main() {
    
    //ask for x, xsqd, xcub
    //display function
    //add and subtract functions
    //reduce function possible
    

    quad a;
    a.set(1,2,3);
    quad b;
    b.set(1,2,3);
    cout << "\na:";
    a.print();
    cout << "\nb:";
    b.print();
    quad c;
    c.add(a,b);
    cout << "\nc:";
    c.print();
    quad d;
    d.sub(c,b);
    cout << "\nd:";
    d.print();
    quad e;
    e.mult(a,d);
    cout << "\ne:";
    e.print();
    quad f = a+b;
    cout << "\nf:";
    f.print();
    quad g=f-d;
    cout << "\ng:";
    g.print();
    quad h=g*a;
    cout << "\nh:";
    h.print();
    
    return 0;
}

