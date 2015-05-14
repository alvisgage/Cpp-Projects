/* 
 * File:   main.cpp
 * Author: rga001
 *
 * Created on November 9, 2012, 1:23 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

struct stack{
    stack();
    ~stack();
    bool empty() const;
    unsigned int size() const;
    int& top();
    const int& top() const;
    void push(const int& x);
    void pop();
private:
    int *stackArray;
    int sizeArray;
    int index;
};
stack::stack(){
    //default constructor, empty stack
    sizeArray=0;
    stackArray=new int[sizeArray];
    index=0;
}
stack::~stack(){
    delete stackArray;
}
bool stack::empty() const{
    //check size for empty
    if(sizeArray==0)
        return true;
    else
        return false;
}
//getters for size and top elements
unsigned int stack::size() const{
    return sizeArray;
}
int& stack::top(){
    return stackArray[0];
}
const int& stack::top() const{
    return stackArray[0];
}
void stack::push(const int& x){
    //check for empty array
    //declare array of size ten if empty
    if(sizeArray==0)
    {
        sizeArray=10;
        stackArray=new int[sizeArray];
        stackArray[0]=x;
    }
    //if stack is full, declare new stack 2 times the current size
    else if(sizeArray==index)
    {
        int array[sizeArray];
        for(int i=0;i<sizeArray;i++,stackArray++)
            array[i]=*stackArray;
        sizeArray*=2;
        stackArray = new int[sizeArray];
        stackArray[0]=x;
        for(int i=0;i<sizeArray/2;i++)
            stackArray[i]=array[i];
    }
    //or, add element to front of stack
    else
    {
        int temp = stackArray[index];
        int temp2;
        stackArray[0]=x;
        for(int i=1;i<sizeArray;i++){
            temp2 = stackArray[i];
            stackArray[i]=temp;
            temp=temp2;
        }
    }
    //increase index
    index++;
    //out put size for error checking
    //cout << "size of array is currently: " << sizeArray << endl;
}
void stack::pop(){
    //if stack is empty do nothing
    if(stack::empty())
        return;
    //declare new array, copy elements after first
    int array[sizeArray];
    for(int i=1;i<sizeArray;i++,stackArray++)
        array[i-1]=stackArray[i];
    sizeArray--;
    stackArray=new int[sizeArray];
    //copy array elements back to stack
    for(int i=0;i<sizeArray;i++)
        stackArray[i]=array[i];
    //decrease index and stack size above
    index--;
}

struct queue{
    queue();
    ~queue();
    bool empty() const;
    unsigned int size() const;
    int& front();
    const int& front() const;
    int& back();
    const int& back() const;
    void push(const int& x);
    void pop();
    void print();
private:
    struct node{
        node*next;
        node*prev;
        int data;
    };
    node *head;
    node *tail;
    int sizeQueue;
};
queue::queue(){
    //default constructor
    //empty list
    head = new node;
    tail = new node;
    head->next=tail;
    tail->prev=head;
    head->prev=NULL;
    tail->next=NULL;
    sizeQueue = 0;
}
queue::~queue(){
    delete head;
    delete tail;
}
bool queue::empty() const{
    //check size for empty
    if(sizeQueue==0)
        return true;
    else
        return false;
}
//getters for size, front and back elements
unsigned int queue::size() const{
    return sizeQueue;
}
int& queue::front(){
    return head->next->data;
}
const int& queue::front() const{
    return head->next->data;
}
int& queue::back(){
    return tail->prev->data;
}
const int& queue::back() const{
    return tail->prev->data;
}
void queue::push(const int& x){
    //declare temp node with data x
    node *temp = new node;
    temp->data=x;
    //insert temp at beginning of list
    temp->next=head->next;
    temp->prev=head;
    head->next=temp;
    sizeQueue++;
}
void queue::pop(){
    //declare temp node to first element
    node *temp=head->next;
    //remove pointers to first node then delete
    head->next=head->next->next;
    head->next->prev=head;
    delete temp;
    sizeQueue--;
}
void queue::print(){
    //output elements in queue
    cout << "printing queue..." << endl;
    node *current=head->next;
    for(int i=0;i<sizeQueue;i++)
    {
        cout << "queue " << i+1 << ": " << current->data << endl;
        current=current->next;
    }
}


int main(int argc, char** argv) {

    stack a;
    if(a.empty())
        cout << "a is empty." << endl;
    else
        cout << "a is not empty." << endl;
    cout << "pushing 5..." << endl;
    a.push(5);
    cout << a.top() << endl;
    cout << "pushing 10..." << endl;
    a.push(10);
    cout << a.top() << endl;
    cout << "popping..." << endl;
    a.pop();
    cout << a.top() << endl;
    cout << "added elements 20 to 40..." << endl;
    for (int x=20;x<40;x++)
    {
        a.push(x);
        cout << a.top() << endl;
    }

    cout << "\nqueue error checking:" << endl << endl;
    queue b;
    if(b.empty())
        cout << "b is empty." << endl;
    else
        cout << "b is not empty." << endl;
        cout << "pushing 5..." << endl;
    b.push(5);
    cout << b.front() << endl;
    cout << "pushing 10..." << endl;
    b.push(10);
    cout << b.front() << endl;
    cout << "popping..." << endl;
    b.pop();
    cout << b.front() << endl;
    cout << "added elements 20 to 40..." << endl;
    for (int x=20;x<40;x++)
    {
        b.push(x);
        cout << b.front() << endl;
    }
    cout << endl << endl;
    b.print();


    return 0;
}

