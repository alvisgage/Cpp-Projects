/* 
 * File:   myString.cpp
 * Author: vista
 * 
 * Created on September 19, 2012, 9:53 AM
 */

#include "myString.h"
#include <iostream>

using namespace std;
myString::myString(char* orig){
    len = 0;
    while (orig[len]!= '\0')
        len++;
    chars = new char[len];
    for (int i=0;i<len;i++)
        chars[i] = orig[i];
}
myString::myString(const myString& orig) {
    len = orig.len;
    if(len==0)
        chars = NULL;
    else
    {
        chars = new char[len];
        for (int i=0;i<len;i++)
            chars[i] = orig.chars[i];
    }    
}

myString::~myString() {
    if(len>0)
        delete [] chars;
}
myString myString::operator+(const myString& rhs){
    myString str;
    int i=0;
    if (len==0 && rhs.len==0)
    {
        str.len=0;
        str.chars = NULL;
    }
    else
    {
        str.len=len+rhs.len;
        str.chars=new char[str.len];
        
        for(i=0;i<len;i++)        
            str.chars[i] = chars[i];
        int j=0;
        while(j<rhs.len)
        {
            str.chars[i]=rhs.chars[i];
            i++;
            j++;
        }        
    }
    return str;
}
char myString::operator [](int index){
    char c;
    c='\0';
    if(index>=0 && index <len)
    {
        c=chars[index];
    }
    return c;
}
myString& myString::operator=(const myString& rhs){
    if(chars!=NULL)
        delete [] chars;
    len=rhs.len;
    chars = new char[len];
    for(int i=0;i<len;i++)
        chars[i]=rhs.chars[i];
    return *this;
}
int myString::size(){
    return len;
}
