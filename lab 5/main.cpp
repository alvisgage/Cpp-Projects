/* 
 * File:   main.cpp
 * Author: vista
 *
 * Created on September 19, 2012, 9:53 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "mystring.h"
#define string mystring

using namespace std;

/*
 *
 */
void check (string s, string name){
    cout << "checking " << name << endl;
    cout << name << " contains " << s << endl;
    cout << name << " capacity() is " << s.capacity() << endl;
    cout << name << " length() is " << s.length() << endl;
    cout << name << " size() is " << s.size() << endl;
    cout << name << " max_size() is " << s.max_size() << endl << endl;

}

int main(int argc, char** argv) {
        cout <<"This is Lab 5\n";


    string s1("Hello, World!");
    string s1name("s1");

    check(s1,s1name);
    check(s1,s1name);

    string s2(s1);
    string s2name("s2");
    check(s2,s2name);

    cout<<"Lab 5 ends\n";
    return 0;
}