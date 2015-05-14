/* 
 * File:   main.cpp
 * Author: Rage Gage
 *
 * Created on November 13, 2012, 6:46 PM
 */

#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

typedef int element_type;
struct linkedlist{
    typedef element_type& reference;
    typedef const element_type& const_reference;
    linkedlist();
    explicit linkedlist(unsigned int n);
    ~linkedlist();
    bool empty() const;
    void clear();
    //getters for front and back elements
    //returns -1 and outputs error msg if list is empty
    reference back(){if(empty())cout<<"List is empty!!\n";return tail->prev->element;}
    const_reference back() const{if(empty())cout<<"List is empty!!\n";return tail->prev->element;}
    reference front(){if(empty())cout<<"List is empty!!\n";return head->next->element;}
    const_reference front() const{if(empty())cout<<"List is empty!!\n";return head->next->element;}
    linkedlist& operator=(const linkedlist& i);
    void pop_back ();
    void pop_front();
    void push_back(const element_type& x);
    void push_front(const element_type& x);
    void sort();    
    void check() const;
    void rcheck() const;
    struct Node{
        Node *next;
        Node *prev;
        element_type element;
    };
    Node *head,*tail;
    int size;
};
linkedlist::linkedlist(){
    //default constructor creates empty list
    head = new Node;
    tail = new Node;
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;
    //head and tail elements used for error checking
    head->element=-1;
    tail->element=-1;
    size=0;
}
linkedlist::~linkedlist(){
    
}
bool linkedlist::empty() const{
    //checks size if empty
    if(size==0)
        return true;
    else
        return false;
}
void linkedlist::clear(){
    Node *temp=head->next;
    Node *temp2=temp->next;
    //deletes every node except head and tail
    for(int x=0;x<size;x++)
    {
        delete temp;
        temp=temp2;
        temp2=temp->next;
    }
    //reset head and tail pointers
    head->next=tail;
    tail->prev=head;
    size=0;
}
linkedlist& linkedlist::operator =(const linkedlist& i){
    //basically a copy constructor
    Node *current = (&i)->head->next;
    head = new Node;
    tail = new Node;
    head->prev=NULL;
    tail->next=NULL;
    head->element=-1;
    tail->element=-1;
    Node *temp = head;
    //copy every node element to new list
    for(int x=0;x<(&i)->size;x++){
        temp->next=new Node;
        temp=temp->next;
        temp->element=current->element;
        current=current->next;
    }
    temp->next=tail;
    tail->prev=temp;
    size=(&i)->size;
}
void linkedlist::pop_back(){
    //remove last node from list, then delete
    Node *temp = tail->prev;
    temp->prev->next = tail;
    tail->prev=temp->prev;
    delete temp;
    size--;
}
void linkedlist::pop_front(){
    //remove first node from list, then delete
    Node *temp = head->next;
    temp->next->prev = head;
    head->next = temp->next;
    delete temp;
    size--;
}
void linkedlist::push_back(const element_type& x){
    //declare new node, insert before tail node
    Node *temp = new Node;
    temp->element = x;
    temp->next = tail;
    temp->prev = tail->prev;
    tail->prev->next = temp;
    tail->prev = temp;
    size++;
}
void linkedlist::push_front(const element_type& x){
    //declare new node, insert after head node
    Node *temp = new Node;
    temp->element = x;
    temp->next = head->next;
    temp->prev = head;
    head->next->prev = temp;
    head->next = temp;
    size++;
}
void linkedlist::sort(){
    //for sort, array of elements in node list
    //sort array, clear list
    //create new list with sorted array elements
    int a[size];
    int min,index,size2=size;
    Node *current=head->next;
    for(int i=0;i<size;i++){
        a[i]=current->element;
        current=current->next;}
    for(int i=0;i<size;i++){
        min=a[i];
        for(int j=i;j<size;j++){
            if(a[j]<min){
                min=a[j];
                index=j;
            }
        }
        a[index]=a[i];
        a[i]=min;
    }
    this->clear();
    for(int x=0;x<size2;x++)
        this->push_back(a[x]);
    size=size2;
}
linkedlist::linkedlist(unsigned int n){
    //explicit constructor for n nodes
    head = new Node;
    tail = new Node;
    head->prev = NULL;
    tail->next = NULL;
    head->element=-1;
    tail->element=-1;
    size=n;
    Node *temp = head;
    for(int x=0;x<size;x++){
        temp->next = new Node;
        temp->next->prev=temp;
        temp=temp->next;
        temp->element=x;
    }
    temp->next=tail;
    tail->prev=temp;    
}
void linkedlist::check() const{
    Node *current=head->next;
    //output if empty list and return
    if(empty()){cout<<"\nThe list is empty!!\n"; return;}
    else
    for(int x=0;x<size;x++)
    {
        cout << "Node " << x+1 << ": " << current->element << endl;
        current=current->next;
    }
    cout << endl;
}
void linkedlist::rcheck() const{
    Node *current=tail->prev;
    //output if empty list and return
    if(empty()){cout<<"\nThe list is empty!!\n"; return;}
    else
    for(int x=size;x>0;x--)
    {
        cout << "Node " << x << ": " << current->element << endl;
        current=current->prev;
    }
    cout << endl;
}
int main(int argc, char** argv) {

    cout << "checking a...\n\n";
    linkedlist a;
    cout << a.front() << endl;    
    for(int i=0;i<20;i++)
        a.push_front(i);
    a.check();
    a.rcheck();
    
    cout << "\n\nchecking b...\n\n";
    linkedlist b=a;
    b.check();
    for(int i=0;i<5;i++)
        b.pop_back();
    b.rcheck();
    
    cout << "\n\nchecking c...\n\n";
    linkedlist c(40);
    c.check();
    
    cout <<"\n\nchecking d...\n\n";
    linkedlist d;
    srand(time(NULL));
    for(int i=0;i<20;i++)
        d.push_back(rand()%100);
    d.check();
    d.sort();
    d.check();
    d.rcheck();
    d.clear();
    d.check();
    
    return 0;
}

