/* 
 * Created on November 30, 2012, 12:19 PM
 */

#ifndef TOKEN_H
#define	TOKEN_H
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;


enum token_type {letter, integer, op, eq, openbrace, closebrace, invalid};

class Token{
private:
    token_type type;
    string token;
    int priority;
public:
    Token();
    Token(string s);
    void set(string s);
    int value() const;
    void display() const;
    token_type get_type() const;
    string get_token() const;
    int get_priority() const;
    int lookup_value(char c); // for hw5
private:
    bool numeric (const string& s) const;
    string stringvalue(token_type t) const;

};


#endif	/* TOKEN_H */
