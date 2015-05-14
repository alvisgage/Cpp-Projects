#include "Token.h"

using namespace std;

bool Token::numeric (const string& s) const {
    // a numeric string has no leading 0
    if (s[0] == '0')
        return false;
    for (int i = 0; i < s.size(); i++)
        // only decimal digits are allowed
        if ( !(s[i] >= '0' && s[i] <= '9') )
            return false;
    return true;
}

Token::Token(): type(invalid), token(""), priority(-1){
// example of constructor initializer list above
}
Token::Token(string s){
    set(s);
}
void Token::set(string s){
    // handle multiple character token
    if (s.length() > 1) {
        if ( numeric(s) )
            type = integer;
        else
            type = invalid;
        token = s;
        return;
    }

    // single character case
    if (s[0] == '(') {
        type = openbrace;
        priority = 0;
    } else if (s[0] == ')') {
        type = closebrace;
    } else if (s[0] == '+') {
        type = op;
        priority = 1;
    } else if (s[0] == '-') {
        type = op;
        priority = 1;
    } else if (s[0] == '*') {
        type = op;
        priority = 2;
    } else if (s[0] == '/') {
        type = op;
        priority = 2;
    } else if (s[0] == '%') {
        type = op;
        priority = 2;
    } else if (s[0] == '='){
        type = eq;
    } else if ( (s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z') ) {
        type = letter;
        s[0] = tolower(s[0]);
    } else if ( s[0] >= '0' && s[0] <= '9' ){
        type = integer;
    } else {
        type = invalid;
    }
    token = s;
}
string Token::stringvalue(token_type t) const{
    switch (t) {
        case letter:
            return "letter";
        case integer:
            return "integer";
        case op:
            return "op";
        case eq:
            return "eq";
        case openbrace:
            return "openbrace";
        case closebrace:
            return "closebrace";
        case invalid:
            return "invalid";
        default:
            return "logic error and should not reach here!";
    }
}

void Token::display() const{
    cout << "type = " << stringvalue(type) << endl;
    cout << "token = " << token << endl;
    cout << "priority = " << priority << endl;
}

token_type Token::get_type() const{
    return type;
}

string Token::get_token() const{
    return token;
}

int Token::get_priority() const{
    return priority;
}

int Token::value() const{
    // if token type is not integer or letter return, usage error
    // if token type is integer, convert string to int
    // if token type is letter, consult symbol table
    // in the last assignment, need to pass in the symbol table or use a global variable
    if (type!=letter || type!=integer){
        cout << "\ninvalid value\n";
        return;
    }
    if (type=integer)
        return atoi(token);
}
int Token::lookup_value(char c){//checks if token is equal to char
    if(token[0]==c)
        return 0;
    else
        return -1;
}