/* 
 * File:   Expression.h
 * Created on November 30, 2012, 12:18 PM
 */

#ifndef EXPRESSION_H
#define	EXPRESSION_H

#include <vector>
#include <stack>
#include <string>
#include "Token.h"

using namespace std;
bool is_defined (char c);
void define (char c, int v);

enum exp_type {assignment, arithmetic, illegal};

class Expression{
private: // files
    vector<Token> tokenized;
    string original;
    vector<Token> postfix;
    vector<Token> prefix;
    vector<Token> par;
    bool valid;
    exp_type type;

public: // methods
    Expression();
    Expression(const string& s);
    void set(const string& s);
    void display() const;
    string get_original() const;
    vector<Token> get_tokenized() const;
    vector<Token> get_postfix() const;
    exp_type get_type() const;

    // for hw5
    void pre() const; // output prefix
    void post() const; // output postfix
    void fully() const; // output fuuly parenthezised
    void eval() const; // pass in a symbol table class


private: // methods
    // for tokenize
    int next_token_start(const string& s, int pos) const;
    int next_token_end(const string& s, int pos) const;
    string stringvalue(exp_type t) const;
    // for convert legal infix to postfix, HW5
    void convert_postfix(const vector<Token> & infix, vector<Token>& postfix);
    // check the syntex of the expressoin, HW5
    void syntax_check();

};



#endif	/* EXPRESSION_H */
