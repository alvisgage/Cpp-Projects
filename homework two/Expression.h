
#ifndef EXPRESSION_H
#define	EXPRESSION_H
#include "Token.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
enum exp_type {assignment, arithmetic, illegal};
class Expression {
public:
    Expression(); //default
    Expression(const Expression& orig); //copy
    Expression(const string& s); //setter constructor
    virtual ~Expression();
    void set(const string& s); //setter
    void display() const; //print function
    string get_original() const{return original;}
    vector<Token> get_tokenized() const{return tokenized;}
    vector<Token> get_postfix() const{return postfix;}; // not used for this homework
    bool get_valid() const{return valid;} //variable not used
    exp_type get_type() const{return type;} //variable not used
    void clearSpace(); //clear any spaces in the expression
private:
    string original;
    vector<Token> tokenized;
    vector<Token> postfix; //not used for this homework
    bool valid; //not used for this homework
    exp_type type; //not used for this homework
};

#endif	/* EXPRESSION_H */

