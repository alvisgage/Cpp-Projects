/* 
 * File:   main.cpp
 * Author: Rage Gage
 *
 * Created on October 8, 2012, 5:01 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;



void selection(int *p){
    //selection sort method
    int min,prev;
   
    for(int x=0;x<10;x++){
        min=p[x];
        for(int i=x;i<10;i++){
            if(p[i]<=min){
            min=p[i];
            prev=i;}
        }
        p[prev]=p[x];
        p[x]=min;
    }   
}

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int intArray[10]={1,-4,5,30,12,-5,5,100,24};
    selection(intArray);
    for(int i=0;i<10;i++)
        cout << intArray[i] << endl;

    return 0;
}

