/* 
 * Gage Alvis
 * 
 * Basic linked list
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
// data element type, for now it is int
typedef int element_type;
// basic node
struct Node
{
    element_type elem;  // data part
    Node * next;        // pointer to the next node
    Node * prev;        // pointer to the previous node, not used for lab 6
};
// show the value of a singly linked list, one node per line
void show(Node * head){
    Node * current = head -> next;
    if (current == NULL)
        cout << "It is an empty list!" << endl;
    int i=1;
    while (current != NULL) {
        cout << "node " << i << "\telem: " << '\t' << current -> elem << "\tnode address value: " << current << "\tnext value: " << current -> next << endl;
        current = current->next;
        i++;
    }
}
void add(int index, Node *current,int num=10){
    Node *b=current;//new pointer set to current to search through
    bool found=false;//boolean to see if an element is found
    while(b->next!=NULL){
        if (b->elem==index)//test each element in list with index
            found=true;//set to true if found
        b=b->next;
    }
    if(found){//if the element was in the list, create and add node list
    //create new list with default 10 nodes, or specified number
    Node *a=new Node;
    b=a;
    for(int i=0;i<num;i++){
        b->next=new Node;
        b=b->next;
        b->elem=i;
    }
    b->next=NULL;
    b=current;
    //define pointer to previous node; *prev member not used in this lab
    Node *prev;
    //split original list at specified index element
    while(b->elem!=index){
        prev=b;
        b=b->next;
    } 
    //get the last node of the created list
    Node *c=a;
    while(c->next!=NULL)
        c=c->next;
    //set last node of created list to point to last half of original
    c->next=b->next;
    //set first half of original to the start of created list
    prev->next->next=a->next;
    }    
    else //if the element is not found, out put an error message
        cout <<"Element not found!"<<endl;
}
int main(int argc, char** argv) {

   
    const int size = 15;

    Node * head;
    head = new Node;
    Node * current = head;

    // making a linked list of size many nodes
    for (int i = 0; i < size; i++){
        current -> next = new Node;
        current = current -> next;
        current -> elem = i;
    }
    // make sure the next field of the last node is NULL
    current -> next = NULL;
    show(head);

   
    // actions for lab 6
    //1. remove first element
    cout << "1." << endl;
    current = head;
    head = head -> next;
    delete current;
    show(head);
    //2. remove last element
    cout << "2." << endl;
    current=head->next;
    while(current->next->next!=NULL)
        current=current->next;
    delete current->next->next;
    current->next=NULL;
    show(head);
    cout << "3." << endl;
    //3. insert 10 elements, or any amount specified
    int in = 10,x;
    Node *insert;
    insert = new Node;
    current=insert;
    for(x=0;x<in;x++)
    {
        current->next=new Node;
        current=current->next;
        current->elem=x;
    }
    current->next=head->next;
    head=insert;
    show(head);
    //4. insert 10 elements after the element with value 7
    cout << "4." << endl;
    add(7,head);
    show(head);    
    
    // free all space
    current = head -> next;
    delete head;
    while (current != NULL) {
        head = current;
        current = current->next;
        delete head;
    }
    return 0;
}
