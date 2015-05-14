/* 
 * File:   main.cpp
 * Author: Gage
 *
 * Created on October 9, 2012, 6:59 PM
 */

#include <cstdlib>
#include "Token.h"
#include <iostream>
#include "Expression.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {    
    
    Token a("+");
    a.display();
    Token b("123");
    b.display();
    Token c("abc");
    c.display();
    Expression d("(1+2=3)");
    d.display();
    Token e(" 4 5 6");
    e.display();
    Expression f("( 1 + 2 = 3 )");
    f.display();

    return 0;
}

