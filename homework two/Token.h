
#ifndef TOKEN_H
#define	TOKEN_H
#include <string>
#include <ctype.h>
#include <iostream>

using namespace std;

class Token {
enum token_type {letter, integer, op, eq, openbrace, closebrace, invalid};

public:
    Token(); //default
    Token(const Token& orig); //copy
    Token(string s); //non default constructor for string
    Token(char c); //non default constructor for char or string[index]
    void set(string s); //change/set original
    int value() const; 
    void display() const; //print function
    token_type get_type() const{return type;}
    string get_token() const{return token;}
    int get_priority() const{return priority;}
    virtual ~Token();
    void clearSpace(); //deletes all spaces
    
private:
    token_type type;
    string token;
    int priority;
};

#endif	/* TOKEN_H */

