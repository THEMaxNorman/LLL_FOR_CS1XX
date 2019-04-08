#ifndef LIST_H
#define LIST_H

#include "node.h"

// A List is a linked list of integers.
class String
{
public:
    String();

    // deletes every element of the list.
    ~String();

    // Inserts a value into a list
    // such that everything before value
    // is less than value.
    // If the list is sorted, then this
    // method will insert value into the correct position.
    


    // inserts value into the first position in the list.
    void prepend(char value);

    // inserts value into the last position in the list.
    void append(char value);

    // remove a node from the list that contains value.
    void remove(char value);
    
    // removes the first value from the list.
    void remove_front();

    // removes the last value from the list.
    void remove_back();

    // print out every element in the list.
    void display();

    //Returns the length of the list
    int length();

    String * reverse();

    bool equals(String * other);
    bool palindrome();

    bool empty();
    void append(String& other);
    String(const char* from);

private:
    // points to the first element in the list.
    Node* _head;
};

#endif // LIST_H
