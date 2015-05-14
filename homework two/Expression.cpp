
#include "Expression.h"

Expression::Expression() { //set fields to empty/false/illegal
    original="";
    tokenized.empty();
    postfix.empty();
    valid=false;
    type=illegal;
}

Expression::Expression(const Expression& orig) { //copy construct
    original=orig.original;
    tokenized=orig.tokenized;
    postfix=orig.postfix;
    valid=orig.valid;
    type=orig.type;
}
Expression::Expression(const string& s){       //this function calls Token(char c)
    original=s;                                //because it parses the string at an index
    clearSpace();                               
    for(int i=0;i<original.size();i++)
        tokenized.push_back(Token(original[i]));
}

Expression::~Expression() {
}
void Expression::set(const string& s){ //same as above for setting new string
    original=s;                        //and tokenizing each character
    for(int i=0;i<original.size();i++)
        tokenized.push_back(Token(original[i]));
}
void Expression::display() const{ //print values
    cout << "\nDisplaying Expression...\n";
    cout << "\nOriginal: " << original << endl;
    for(int i=0;i<tokenized.size();i++){
        cout << "\nToken " << i+1 << ": ";
        tokenized[i].display();
    }    
    cout << "\nEnd of Expression\n";
}
void Expression::clearSpace(){
    string s=original;       
    for(int i=0;i<s.size();i++)
        if(s[i]==' ')
            s.erase(i,1);
    original=s;
}


