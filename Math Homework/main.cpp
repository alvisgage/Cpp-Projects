/* 
 * File:   main.cpp
 * Author: Rage Gage
 *
 * Created on September 29, 2012, 10:07 AM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

float z(float mean,float dev, float num){
    return (num-mean)/dev;    
}
int main(int argc, char** argv) {

    
    float mean;
    float dev;
    float zscore1;
    float num1;
    cout << "mean: ";
    cin >> mean;
    cout << "deviation: ";
    cin >> dev;
    cout << "first prob: ";
    cin >> num1;
    cout << endl << endl;
    zscore1 = z(mean,dev,num1);
    cout << num1 << " zscore: " << zscore1;
    
    return 0;
}

