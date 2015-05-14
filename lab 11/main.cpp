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
    int data;
    Node *leftchild;
    Node *rightchild;
};
Node* search(Node* t,int key,Node *&parent){
    if(t==NULL){
        parent=t;
        return t;
    }
    else if(key < t->data)
        t->leftchild=search(t->leftchild,key,parent);
    else if(key > t->data)
        t->rightchild=search(t->rightchild,key,parent);
    else
        return t;
    return t;
}
Node *insert(Node* t,int key){
    cout << key << endl;
    Node *root = t;
    t=search(root,key,t);
    if(t->data==key)
        return root;
    else
        if(key<t->data){
            t->leftchild=new Node;
            t->leftchild->leftchild=NULL;
            t->leftchild->rightchild=NULL;
            t->leftchild->data=key;
            return root;
        }
        else if(key> t->data){
            t->rightchild=new Node;
            t->rightchild->leftchild=NULL;
            t->rightchild->rightchild=NULL;
            t->rightchild->data=key;
            return root;
        }
    /*if(t==NULL){
        Node *temp = new Node;
        temp->data=key;
        temp->leftchild=NULL;
        temp->rightchild=NULL;
        t=temp;
        return t;
    }
    else if(key < t->data)
        t->leftchild=insert(t->leftchild,key);
    else if(key > t->data)
        t->rightchild=insert(t->rightchild,key);
    else
        return t;
    return t;
    */
}

void inorder(Node *t){
    if(t!=NULL){
        if(t->leftchild)
            inorder(t->leftchild);
        cout <<t->data << " ";
        if(t->rightchild)
            inorder(t->rightchild);
    }
    else return;
    
}

int main(int argc, char** argv) {

    srand(time(0));
    Node*root = new Node;


    for(int x=0;x<10;x++)
        root=insert(root,rand()%100);
    inorder(root);

    return 0;
}

