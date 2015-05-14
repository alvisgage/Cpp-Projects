/* 
 * File:   main.cpp
 * Author: rga001
 *
 * Created on November 16, 2012, 1:22 PM
 */

#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

struct Node{
    Node();
    int data;
    Node *leftchild;
    Node *rightchild;
};
Node::Node(){ //default constructor
    data=-1;  //data set to -1 for error checking
    leftchild=NULL;
    rightchild=NULL;
}
Node* search(Node* t,int key,Node *&parent){ //searches for key, if found - returns
    if(t==NULL){ //if key not found, insert 
        Node *temp = new Node;
        temp->data=key;
        temp->leftchild=NULL;
        temp->rightchild=NULL;
        t=temp;
        return t;
    }
    else if(key < t->data){ //parent set to t before calling search again
        parent=t;
        t->leftchild=search(t->leftchild,key,parent);
    }        
    else if(key > t->data){ //parent set to t
        parent=t;
        t->rightchild=search(t->rightchild,key,parent);
    }        
    else
        return t;
    return t;
}
Node *insert(Node* t,int key){ //call search function to search for key
    Node *parent = t;
    t=search(t,key,parent);
    return t;
}

void inorder(Node *t){
    if(t->data==-1) //default node with default data
        cout << "\nbinary search tree in order: ";
    if(t!=NULL){
        if(t->leftchild)
            inorder(t->leftchild);
        if(t->data!=-1) //default node not displayed
            cout <<t->data << " ";
        if(t->rightchild)
            inorder(t->rightchild);
    }
    else 
        return;
}

int main(int argc, char** argv) {

    srand(time(0));
    Node*root = new Node;

    for(int x=0;x<10;x++) //insert 10 random numbers
        root=insert(root,rand()%100);
    inorder(root); //display in order
    
    root=insert(root,10); //insert 10 twice to check for duplicates
    root=insert(root,10);
    
    inorder(root);    
    cout << endl;
    return 0;
}

