/* 
 * File:   myString.h
 * Author: vista
 *
 * Created on September 19, 2012, 9:53 AM
 */

#ifndef MYSTRING_H
#define	MYSTRING_H
#include <iostream>

class myString {
public:
    myString():len(0),chars(NULL){};
    myString(const myString& orig);
    myString(char*);
    virtual ~myString();
//    iterator begin();
//    iterator end();
    int size();
    int length() const {return len;};
    char * reserve(int space);
    int capacity();
    bool empty();
    myString & operator=(const myString &rhs);
    myString & operator+=(const myString &rhs);
    myString operator+(const myString &rhs);
    char operator[](int i);
    
private:
    int len;
    char *chars;   
    typedef unsigned int size_type;
    typedef char * iterator;
    typedef const char * const_iterator;
};

#endif	/* MYSTRING_H */

