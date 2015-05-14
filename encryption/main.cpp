/* 
 * File:   main.cpp
 * Author: Rage Gage
 *
 * Created on September 29, 2012, 7:25 PM
 */

#include <cstdlib>
#include <string.h>
#include <iostream>


using namespace std;

/*
 * 
 */
int main() {
    string orig,en,de;
    orig="H";
    char key='a';
    en=orig[0]^int(key)%255;
    de=en[0]^key;

    cout << orig << endl;
    cout << key << endl;
    cout << en << endl;
    cout << de << endl;
    
    return 0;
}

