/* 
 * File:   node.h
 * Author: Rage Gage
 *
 * Created on September 30, 2012, 6:14 PM
 */

#ifndef NODE_H
#define	NODE_H
using namespace std;

struct node {
    //node funct
    node();
    virtual ~node();
    void addNode();
    void clear();
    void remove(int index);
    void list(int num);
    void print();
    
    //variables
    int x;
    char *p;
    node *next;
    int size;
};

#endif	/* NODE_H */

