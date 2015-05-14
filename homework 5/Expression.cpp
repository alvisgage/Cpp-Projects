#include "Expression.h"

using namespace std;
// start is position from which the next token is searched
int Expression::next_token_start(const string& s, int start)const {
    // find the first nonblank character
    while (start < s.size() && s[start] == ' ')
        start++;
    return start;
}
// start is the index of a nonblank character
int Expression::next_token_end(const string& s, int start)const {
    const string ops = "()+-*/% ";
    int pos = start;
    // find the next operator
    while (start < s.size() && s[start] != '(' && s[start] != ')' && s[start] != '+'
                            && s[start] != '-' && s[start] != '*' && s[start] != '/'
                            && s[start] != '%' && s[start] != '=' && s[start] != ' '){
        start++;
    };
    if ( start != pos) // next token is not an operator
        start--;
    return start;
}
// for diaplay enum
string Expression::stringvalue(exp_type t) const{
    switch (t) {
        case assignment:
            return "assignment";
        case arithmetic:
            return "arithmetic";
        case illegal:
            return "illegal";
        default:
            return "logic error and should not reach here!";
    }
}

void Expression::set(const string& str){

    original = str;
    tokenized.clear();
    postfix.clear();
    // both values below could be changed by syntax_check
    valid = true;
    type = illegal;

    // remove all spaces from s
    string s = str;
    for (int i = s.size()-1; i >= 0; i--){
        if (s[i] == ' ')
            s.erase(s.begin()+i);
    }
  
    Token t;
    int token_start = 0;
    int token_end;
    string token_str;

    // tokenize
    token_start = next_token_start(s, token_start);
    while ( token_start < s.size() ) {
        // getting next token
        token_end = next_token_end(s,token_start);
//        cout << "token_end = " << token_end << endl;
        token_str.clear();
        for (int i = token_start; i <= token_end; i++){
            token_str.push_back(s[i]);
        };
//        cout << "token = " << token_str << endl;
        t.set(token_str);      

        // update expression
        tokenized.push_back(t);

        // find the first position of the next token
        token_start = token_end+1;
        token_start = next_token_start(s, token_start);
    };
    
    // added for hw5

//    syntax_check();
//    if (type == arithmetic ){
//        convert_postfix(tokenized, postfix);
//    }

 }
Expression::Expression(const string& s){
    set(s);
}

Expression::Expression(){
    original.clear();
    tokenized.clear();
    postfix.clear();
    valid = false;
    type = illegal;
}
// for debugging use
void Expression::display() const{
    cout << "  original = " << original << endl;
    cout << "  type = " << stringvalue(type) << endl;
    cout << "  valid = " << valid << endl;
    cout << "  # of token: " << tokenized.size() << endl;
    for (int i = 0; i < tokenized.size(); i++)
        tokenized[i].display();
}

string Expression::get_original() const{
    return original;
}

exp_type Expression::get_type() const{
    return type;
}

vector<Token> Expression::get_tokenized() const{
    return tokenized;
}

vector<Token> Expression::get_postfix() const{
    return postfix;
}
void Expression::post() const{
    token_type type;
    Token front;
    vector<Token> tokens = tokenized;
    cout << "\npostfix: ";
    while(!tokens.empty()){
        type=tokens.front().get_type();
        front = tokens.front();
        switch (type){
            case letter:
                tokens.front().display();
                break;
            case integer:
                tokens.front().display();
                break;
            case op:{
                if (postfix.empty())
                    postfix.push_back(front);
                if (postfix.back().get_priority()<=tokens.front().get_priority())
                {
                    postfix.back().display();
                    postfix.pop_back();
                    postfix.push_back(front);
                }
                if (tokens.front()==')'){
                    while(postfix.back()!='('){
                        postfix.back().display();
                        postfix.pop_back();
                    }
                    if(postfix.back=='(')
                        postfix.pop_back();
                }
                break;
            }
        }
        tokens.erase(0);
    }
    while(!postfix.empty()){
        postfix.back().display();
        postfix.pop_back();
    }
}

void Expression::pre() const{
    token_type type;
    Token front;
    vector<Token> tokens = tokenized;
    cout << "\nprefix: ";
    while(!tokens.empty()){
        type=tokens.front().get_type();
        front = tokens.front();
        switch (type){
            case letter:
                prefix.push_back(front);
                break;
            case integer:
                prefix.push_back(front);
                break;
            case op:{
                cout << tokens.front();
                for(int x=0;x<2;x++){
                    prefix.back().display();
                    prefix.pop_back();
                }
            }
        }
        tokens.erase(0);
    }
    while(!prefix.empty()){
        prefix.back().display();
        prefix.pop_back();
    }
}








