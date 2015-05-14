/* 
 * File:   main.cpp
 * Author: rga001
 *
 * Created on November 30, 2012, 1:25 PM
 */

#include <cstdlib>
#include "MusicLibrary.h"
#include "Song.h"
#include "utility.h"


using namespace std;

/*
 * 
 */
template <typename type>
class stack{
public:
    stack();
    ~stack();
    bool empty() const;
    unsigned int size() const;
    type& top();
    const type& top() const;
    void push(const type& x);
    void pop();
    void checkStack() const;
private:
    type *stackArray;
    int sizeArray;
    int index;
};
template <typename type>
stack<type>::stack(){
    sizeArray=10;
    stackArray=new type[sizeArray];
    index=0;
}
template <typename type>
stack<type>::~stack(){
    delete stackArray;
}
template <typename type>
bool stack<type>::empty() const{
    if(sizeArray==0||index==0)
        return true;
    else
        return false;
}
template <typename type>
unsigned int stack<type>::size() const{
    return sizeArray;
}
template <typename type>
type& stack<type>::top(){
    return stackArray[0];
}
template <typename type>
const type& stack<type>::top() const{
    return stackArray[0];
}
template <typename type>
void stack<type>::push(const type& x){
    if(sizeArray==index)
    {
        type array[sizeArray];
        for(int i=0;i<sizeArray;i++)
            array[i]=stackArray[i];
        sizeArray*=2;
        stackArray = new type[sizeArray];
        stackArray[0]=x;
        for(int i=1;i<sizeArray/2;i++)
            stackArray[i]=array[i-1];
    }
    else
    {
        type temp = stackArray[0];
        type temp2;
        stackArray[0]=x;
        for(int i=1;i<sizeArray;i++){
            temp2 = stackArray[i];
            stackArray[i]=temp;
            temp=temp2;
        }
    }
    index++;

}
template <typename type>
void stack<type>::pop(){
    if(stack::empty())
        return;
    type array[sizeArray];
    for(int i=1;i<sizeArray;i++,stackArray++)
        array[i-1]=stackArray[i];
    sizeArray--;
    stackArray=new type[sizeArray];
    for(int i=0;i<sizeArray;i++)
        stackArray[i]=array[i];
    index--;
}
template <typename type>
void stack<type>::checkStack() const{
    if(stack<type>::empty()){
        cout << "\nempty stack!!\n";
        return;
    }
    cout << "\nprinting stack...\n";
    
    for(int i=0;i<sizeArray;i++){
        cout << i+1 << ": " << stackArray[i] << endl;
    }

  }

template <typename type>
class queue{
public:
    queue();
    ~queue();
    bool empty() const;
    unsigned int size() const;
    type& front();
    const type& front() const;
    type& back();
    const type& back() const;
    void push(const type& x);
    void pop();
    void checkQueue() const;
private:
    struct node{
        node*next;
        node*prev;
        type data;
    };
    node *head;
    node *tail;
    int sizeQueue;
};
template <typename type>
queue<type>::queue(){
    head = new node;
    tail = new node;
    head->next=tail;
    tail->prev=head;
    head->prev=NULL;
    tail->next=NULL;
    sizeQueue = 0;
}
template <typename type>
queue<type>::~queue(){
    delete head;
    delete tail;
}
template <typename type>
bool queue<type>::empty() const{
    if(sizeQueue==0)
        return true;
    else
        return false;
}
template <typename type>
unsigned int queue<type>::size() const{
    return sizeQueue;
}
template <typename type>
type& queue<type>::front(){
    return head->next->data;
}
template <typename type>
const type& queue<type>::front() const{
    return head->next->data;
}
template <typename type>
type& queue<type>::back(){
    return tail->prev->data;
}
template <typename type>
const type& queue<type>::back() const{
    return tail->prev->data;
}
template <typename type>
void queue<type>::push(const type& x){
    node *temp = new node;
    temp->data=x;
    temp->next=head->next;
    temp->prev=head;
    head->next->prev=temp;
    head->next=temp;
    sizeQueue++;
}
template <typename type>
void queue<type>::pop(){
    if(queue<type>::empty()){
        cout << "\nempty stack!!\n";
        return;
    }
    node *temp=head->next;
    head->next=head->next->next;
    head->next->prev=head;
    delete temp;
    sizeQueue--;
}
template <typename type>
void queue<type>::checkQueue() const{

    cout << "printing queue..." << endl;
    if(queue<type>::empty()){
        cout << "\nempty queue!!\n";
        return;
    }
    node *current=head->next;
    for(int i=0;i<sizeQueue;i++)
    {
        cout << "queue " << i+1 << ": " << current->data << endl;
        current=current->next;
    }
}

int main(int argc, char** argv) {

    cout << "Sample main test file for lab 12.  Please notice the checkQueue and checkStack functions\n";
    cout << "This is specifically testing for integers.  You will still need to check strings, doubles, chars, etc\n";

//none of these lines should break your code - check against c++ stack to see what is supposed to be returned

    cout << "**********STARTING STACKS**********\n";
    stack<int> s;
    cout << "Is the stack empty? (1: yes, 0: no) - " << s.empty() << endl;
    cout << "The size is " << s.size() << endl;
    s.checkStack();

    cout << "Add 20 elements to the array\n";
    for (int i = 0; i < 20; i++)
    {
        s.push(i);
        cout << s.top() << ",";
    }
    cout << endl;
    cout << "Is the stack empty? (1: yes, 0: no) - " << s.empty() << endl;
    cout << "The size is " << s.size() << endl;
    cout << "The top element is " << s.top() << endl;
    s.checkStack();

    cout << "Edit the top element!\n";
    s.top() = -17;
    cout << "The new top element is " << s.top() << endl;
    s.checkStack();

    cout << "Removing all elements\n";
    while(!s.empty())
        s.pop();
    cout << "Is the stack empty? (1: yes, 0: no) - " << s.empty() << endl;
    cout << "The size is " << s.size() << endl;
    s.checkStack();

    cout << "**********ENDING STACKS**********\n\n";
    cout << "**********STARTING QUEUES**********\n";


//None of these lines should break your code - check against c++ queue to see what is supposed to be returned
    queue<int> q ;
    cout << "Is the queue empty? (1: yes, 0: no) - " << q.empty() << endl;
    cout << "The size is " << q.size() << endl;
    cout << "The front element is " << q.front() << endl;
    cout << "The back element is " << q.back() << endl;
    cout << "Display the elements of the queue\n";
    q.checkQueue();
//if your code doesn't bring out the next line, add a \n to the end of the cout - you'll see that the code actually is breaking on
//the line q.pop();
    cout << "If we pop when there's nothing in the queue, does it work?  ";
    q.pop();
    cout << "yep!\n";

    cout << "Adding 10 numbers to the queue\n";
    for(int i = 0; i < 10; i++)
    {
        q.push(i);
    }
    cout << "Is the queue empty? (1: yes, 0: no) - " << q.empty() << endl;
    cout << "The size is " << q.size() << endl;
    cout << "The front element is " << q.front() << endl;
    cout << "The back element is " << q.back() << endl;
    cout << "Display the elements of the queue\n";
    q.checkQueue();

    cout << "Changing the front and back elements\n";
    q.front() = -100;
    q.back() = 200;
    cout << "The front element is " << q.front() << endl;
    cout << "The back element is " << q.back() << endl;
    q.checkQueue();

    cout << "Removing all elements\n";
    while(!q.empty())
        q.pop();

    cout << "Is the queue empty? (1: yes, 0: no) - " << q.empty() << endl;
    cout << "The size is " << q.size() << endl;
    cout << "The front element is " << q.front() << endl;
    cout << "The back element is " << q.back() << endl;
    cout << "Display the elements of the queue\n";
    q.checkQueue();

    cout << "**********ENDING QUEUES**********\n";

    
    cout <<"\n**********song queue**********\n";
    queue<Song> songQ;
    Song a;
    Song b;
    b.set_title("New Title");
    songQ.push(a);
    songQ.push(b);
    songQ.checkQueue();
    songQ.pop();
    songQ.checkQueue();
    songQ.pop();
    songQ.checkQueue();
}


