
#include "Token.h"
//created string array for displaying type instead of integer
string strType[]={"letter","integer","op","eq","openbrace","closebrace","invalid"};
//token priority equal to token type-values can be changed
int token_priority[]={1,1,2,3,4,4,-1};

Token::Token() { //set values to invalid/empty/-1
    type = invalid;
    token="";
    priority=-1;
}
Token::Token(string s){//set token
    token=s;
    clearSpace();
    bool isLetter=true,isInt=true; 
    for(int i=0;i<token.size();i++) //check if string is all integers
        if(!isdigit(token[i]))      //if not isInt is false
            isInt=false;
    for(int i=0;i<token.size();i++) //check if string is all char
        if(!isalpha(token[i]))      //if not isLetter is false
            isLetter=false;
    if(isLetter)                //set type to string or int if possible
        type=letter;
    else if(isInt)
        type=integer;
    else if(token=="+"||token=="-"||token=="*"||token=="/"||token=="%") //check for operators
        type=op;
    else if(token=="=") //check for equals
        type=eq;
    else if(token=="(")   //check for braces
        type=openbrace;
    else if(token==")")
        type=closebrace;
    else                    //if nothing fits type is invalid
        type=invalid;
    priority=token_priority[type];    //set priority
}
Token::Token(char c){ //same as string constructor - char constructor
                      //used for Expression class or parsing strings as tokens
    token=c;
    bool isLetter=true,isInt=true;
    for(int i=0;i<token.size();i++)
        if(!isdigit(c))
            isInt=false;
    for(int i=0;i<token.size();i++)
        if(!isalpha(c))
            isLetter=false;
    if(isLetter)
        type=letter;
    else if(isInt)
        type=integer;
    else if(token=="+"||token=="-"||token=="*"||token=="/"||token=="%")
        type=op;
    else if(token=="=")
        type=eq;
    else if(token=="(")
        type=openbrace;
    else if(token==")")
        type=closebrace;
    else
        type=invalid;
    priority=token_priority[type];    
}
Token::Token(const Token& orig) { //copy constructor
    type=orig.type;
    token=orig.token;
    priority=orig.priority;
}

Token::~Token() {
}
void Token::set(string s){ //change token value
    token=s;
}
int Token::value() const{ //if token is an integer, return value
    int t;                //if token is letters, return 0
    if (type==integer)    //otherwise return -1
        for(int i=0;i<token.size();i++)
            t+=static_cast<int>(token[i]);
    else if(type==letter)
        return 0;
    else
        return -1;
    return t;
}
void Token::display() const{ //print values
    cout << "\nToken: " << token <<
            "\nType: " << strType[type] <<
            "\nPriority: " << priority << endl;
}
void Token::clearSpace(){ //clears spaces in 
    string s=token;       //because == is not overloaded, string must be used
    for(int i=0;i<s.size();i++)
        if(s[i]==' ')
            s.erase(i,1);
    token=s;
}