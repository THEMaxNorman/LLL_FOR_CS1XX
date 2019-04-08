
#include "node.h"
#include "lstring.h"
#include <iostream>
#include <cstddef>

using namespace std;

//////////////////////////////////////////////////
//
// Constructor/Destructor
//
//////////////////////////////////////////////////

String::String()
{
    // remember, always set head to NULL.
    // otherwise it looks like our list has something in it.
    _head = NULL;
}

String::~String()
{
    Node* current;

    while(_head)
    {
        // don't just delete _head,
        // otherwise we can't get to the next node.
        current = _head->next;

        // NOTE: if our nodes contained pointers,
        //       then we'd delete those here.
        delete _head;

        _head = current;
    }
}


//////////////////////////////////////////////////
//
// Insert methods
//
//////////////////////////////////////////////////
void String::prepend(char value)
{
    // if _head is null then we put the element
    // at the front of the list and we're done
    //
    //             |         -----
    // H -> 0      |    H -> | V | -> 0
    //             |         -----
    if(!_head)
    {
        _head = new Node;
        _head->value = value;
        _head->next = NULL;
        return;
    }

    //      -----    -----    -----       
    // H -> | 2 | -> | 3 | -> | 4 | -> 0
    //      -----    -----    -----       
    //                   -----
    //                   | 1 |
    //                   -----
    // becomes
    //
    //        T        H
    //        |        |
    //        v        v
    //      -----    -----    -----    -----       
    //      | 1 | -> | 2 | -> | 3 | -> | 4 | -> 0
    //      -----    -----    -----    -----       

    // Make a new node pointing to first element.
    Node* temp = new Node;
    temp->value = value;
    temp->next = _head;

    //
    //        H
    //        |
    //        v
    //      -----    -----    -----    -----       
    //      | 1 | -> | 2 | -> | 3 | -> | 4 | -> 0
    //      -----    -----    -----    -----       

    //this is now our first element of the list.
    _head = temp;
}

void String::append(char  value)
{
    // if _head is null then we put the element
    // at the front of the list and we're done
    //
    //             |         -----
    // H -> 0      |    H -> | V | -> 0
    //             |         -----
    if(!_head)
    {
        _head = new Node;
        _head->value = value;
        _head->next = NULL;
        return;
    }

    //      -----    -----    -----       
    // H -> | 1 | -> | 2 | -> | 3 | -> 0
    //      -----    -----    -----       
    //                   -----
    //                   | 4 |
    //                   -----
    // becomes
    //
    //                          P
    //                          |
    //                          v
    //      -----    -----    -----
    // H -> | 1 | -> | 2 | -> | 3 |           C
    //      -----    -----    -----           |
    //                             \ -----    V
    //                              -| 4 | -> 0
    //                               -----
    Node* previous = _head;
    Node* current = _head->next;

    // find the end of the list
    while(current != NULL)
    {
        previous = current;
        current = current->next;
    }

    // since current is NULL, we can reuse it to make our new node
    current = new Node;
    current->value = value;
    current->next = NULL;
   
    //connect previous to our new node
    previous->next = current;
}


void String::remove(char value)
{
    // don't remove anything from an empty list
    if(!_head)
    {
        return;
    }

    // remove 3
    //
    //                 P        C
    //                 |        |
    //                 V        V
    //      -----    -----    -----    -----       
    // H -> | 1 | -> | 2 | -> | 3 | -> | 4 | -> 0
    //      -----    -----    -----    -----       
    //
    // set current to be the node with the value we want
    // to remove.
    //
    // we need to remove the node, and set previous
    // to the next node.
    Node* previous = _head;
    Node* current = _head->next;

    // find the node with the value we want to remove
    while(current && current->value != value)
    {
        previous = current;
        current = current->next;
    }

    // if we found the node, remove it
    // if we didn't, then current is NULL, and we don't need to do anything
    if(current)
    {
        previous->next = current->next;
        delete current;
    }
}

void String::remove_front()
{
    // don't remove anything from an empty list
    if(!_head)
    {
        return;
    }

    //                 C
    //                 |
    //                 V
    //      -----    -----    -----    -----
    // H -> | 1 | -> | 2 | -> | 3 | -> | 4 | -> 0
    //      -----    -----    -----    -----
    //
    // set current to the second element
    // then delete the head of the list, and set head to point at current
    Node* current = _head->next;
    delete _head;
    _head = current;
}

void String::remove_back()
{
    // don't remove anything from an empty list
    if(!_head)
    {
        return;
    }

    //                          P        C
    //                          |        |
    //                          V        V
    //      -----    -----    -----    -----       
    // H -> | 1 | -> | 2 | -> | 3 | -> | 4 | -> 0
    //      -----    -----    -----    -----       
    //
    // set current to be the last node in the list
    // and previous to be the second to last node in the list.
    Node* current = _head;
    Node* previous = NULL;

    // find the last node in the list
    while(current->next)
    {
        previous = current;
        current = previous->next;
    }

    // NOTE: if our nodes contained pointers,
    //       then we'd delete those here.
    delete current;


    // if previous is NULL at this point,
    // then there was only one node in the list
    if(!previous)
    {
        _head = NULL;
    }
    else
    {
        previous->next = NULL;
    }

}


void String::display()
{
    

    // Well, we can write this loop from class as a for loop
    // You should check to make sure that this matches 
    // the while loop from the slides;
    for(Node* current = _head; current; current = current->next)
    {
        cout << current->value;
    }

    cout << endl;
}

int String::length()
{
    int counter = 0;
   for (Node* current = _head; current; current = current -> next)
    {
        ++ counter;
    }

    return counter;

}
String* String::reverse()
{
    String*  intList = new String();
    
    for (Node* current = _head; current; current = current -> next)
    {
        intList -> prepend(current -> value);
    }

    

    return intList;

}

bool String::equals(String* other)
{
    bool returnval = true;
    int l1;
    int l2;

    l1 = this -> length();

    l2 = other -> length();
    
    char list1[l1];
    char list2[l2];
    if (l1 != l2)
    {
        returnval = false;
    }
    int counter1 = 0;
    for (Node* current = _head; current; current = current -> next)
    {
        list1[counter1] = current -> value;
        counter1 ++;    
    }
    int counter2 = 0;
    for (Node* current = other -> _head; current; current = current -> next)
    {
        list2[counter2] = current -> value;
        counter2 ++;    
    }
    for (int i = 0; i < l1; i++)
    {
        if(list2[i] != list1[i])
        {
            returnval = false;
        }

    }
    return returnval;




}
void String::append(String& other)
{
    
    for (Node* current = other._head; current; current = current -> next)
    {
        cout << "The letter is: " << current -> value << endl;
        this -> append( current -> value);
        this -> display();
        
    }
} 

bool String::palindrome()
{
    bool returnval = false;
    String * revList = new String();
    
    revList = this -> reverse();

    returnval = this -> equals(revList);

    return returnval;

}



bool String::empty()
{
    bool returnval = false;
    if(_head != NULL)
    {
        returnval = true;
    }
    return !returnval;
}

String::String(const char* from)
{
    int leng = sizeof(from);
    for (int i = 0; i < leng; i ++ )
    {
        this -> append(from[i]);

    }
}



