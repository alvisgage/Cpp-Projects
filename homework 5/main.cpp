/* 
 * File:   main.cpp
 * Author: Rage Gage
 *
 * Created on December 4, 2012, 5:23 PM
 */

#include <cstdlib>
#include <vector>
#include "Token.h"
#include "Expression.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    string input="",action="";
    Expression a;
    vector<Expression> e;
    while(input!="q"){
        cout << "input: ";
        cin >> input;
        
        e.push_back(input);
    }
        
    return 0;
}

