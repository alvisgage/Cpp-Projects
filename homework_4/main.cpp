/* 
 * File:   main.cpp
 * Author: Rage Gage
 *
 * Created on November 13, 2012, 6:40 PM
 */

#include <cstdlib>
using namespace std;
typedef int element_type;
struct linkedlist{
    typedef element_type& reference;
    typedef const element_type& const_reference;
    linkedlist();
    ~linkedlist();
    bool empty() const;
    void clear();
    reference back();
    const_reference back() const;
    reference front();
    const_reference front() const;
    linkedlist& operator=(const linkedlist& i);
    void pop_back ();
    void pop_front();
    void push_back(const element_type& x);
    void push_front(const element_type& x);
    void sort();
    explicit linkedlist(unsigned int n);
    void check() const;
    void rcheck() const;
    struct Node{
        Node *next;
        Node *prev;
        element_type element;

    };
    struct iterator{
        iterator begin();
        end();
        rbegin();
        rend();
        insert(iterator pos, const element_type& x);
        erase(iterator pos);
        //overload * de-reference, ++, --
    };
    linkedlist::linkedlist(){
        
    }

};
int main(int argc, char** argv) {

    return 0;
}

