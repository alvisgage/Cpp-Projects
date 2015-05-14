/* 
 * File:   node.cpp
 * Author: Rage Gage
 * 
 * Created on September 30, 2012, 6:14 PM
 */

#include "node.h"
using namespace std;
node::node() {
    x=0;
    p=new char[x+1];
    next=0;
    size=1;
}
void node::addNode(){
    node *add;
    add.x=x+1;
    add.p=new char[add.x+1];
    next=add;
    add->next=0;
    size++;
}
void node::print(){
    node *a=next;
    while(next!=0)
    {
        cout << "x: " << next.x << endl;
        cout << "p: " << next.p << endl;
        next=a.next;
        a=a.next;
    }
}
void node::clear(){
}



node::~node() {
}

