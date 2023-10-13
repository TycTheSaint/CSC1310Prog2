/*
	Title:  List.h
	Author:  Tyce Webster & Isaac Essex
    Course: CSC 1310-001
	Date:  10/12/2023
    Due: 10/12/2023
	Purpose: This header file serves as the framework for our doubly-linked list.
*/
#ifndef LIST_H
#define LIST_H

//Libraries used
#include <iostream>
#include <cstddef>
using namespace std;

template <class T> //Template for the List class
class List
{
    private:
        struct ListNode
        {
            T value;
            ListNode* next;
            ListNode* prev;
        };
        ListNode* head;
        ListNode* tail;

        void print(ListNode*); //Parameter moves through the list
        ListNode* mergesort(ListNode*, ListNode*);
        ListNode* merge(ListNode*, ListNode*);
        ListNode* split(ListNode*, ListNode*);
    public:
        List() //Constructor
        {
            head = NULL;
            tail = NULL;
        }
        ~List(); //Deconstructor
        void print();
        void append(T);
        void mergesort();
};

template <typename T>
void List<T>::print(ListNode* nodePtr) //Parameter moves through the list
{
    ListNode *temp = nodePtr; //Sets iterator to the head of the list

    //While nodePtr points to a node, traverse the list
    while(temp)
    {
        cout << *(temp->value) << endl; //Displays the value of a node
        temp = temp->next; //Sets the nodePtr to the next node of the list
    }
}

template <typename T>
List<T>::~List() //Deconstructor
{
    ListNode* nodePtr;
    ListNode* nextNode;

    nodePtr = head;

    while(nodePtr != NULL)
    {
        nextNode = nodePtr->next;

        delete nodePtr;

        nodePtr = nextNode;
    }
}

template <typename T>
void List<T>::print()
{
    print(head); //Calls private print() function and sets head as the current node to print
}

template <typename T>
void List<T>::append(T newValue)
{
    ListNode *newNode; //Points to a new node

    //Allocates newNode and stores newValue there
    newNode = new ListNode;
    newNode->value= newValue;
    newNode->next = NULL;
    newNode->prev = NULL;

    //If there are no nodes in the list, then make newNode the first node
    if(!head)
    {
        head = newNode;
        tail = newNode;
    }
    else //Inserts newNode at the end of the list
    {
        //Sets the current last node's next pointer to newNode
        tail->next = newNode;
        newNode->prev = tail;
        //Tail is set to the newNode
        tail = newNode;
    }
}

template<typename T>
void List<T>::mergesort()
{
    ListNode* ptr = NULL;
    //Calls mergesort function to perform the mergesort
    head = mergesort(head, tail);
    ptr = head;
    
    //Finds the new tail by traversing the list
    while(ptr != NULL && ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    tail = ptr;
}

template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* first, ListNode* last)
{
    ListNode* left;
    ListNode* right;

    //Base case for when list partition is zero or one node, function returns first parameter
    if(first == NULL || first->next == NULL)
    {
        return first;
    }
    
    left = first;
    //Splits the list into two partitions and sort each partition recursively
    right = split(first, last); //Beginning of second partition
    left = mergesort(left, right->prev); //Partition one
    right = mergesort(right, last); //Partition two

    //Merges the sorted partitions and returns the merged list
    return merge(left, right); //Returns the merge call with the left and right partitions as parameters
}

template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* first, ListNode* last)
{
    ListNode* mid;

    if(first == NULL || last == NULL || first == last)
    {
        return first; //Returns NULL if the partition is empty or has only one node
    }

    //While first and last node are not the same and the next first node is not the same as last node, loop executes
    while(first!=last && first->next!=last)
    {
        first=first->next;
        last=last->prev;
    }

    mid = first->next; //Defines the mid pointer for second half of partition

    first->next = NULL; //Split sets value to NULL

    return mid; //Returns the middle node
}

template <typename T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* last)
{
    //Base case if either node is NULL, then return the other nodes
    if(first == NULL)
    {
        return last;
    }
    else if(last == NULL)
    {
        return first;
    }

    //Recursively calls the merge function to compare the dereferenced values between partition one and two
    if(*(first->value) > *(last->value))
    {
        first->next = merge(first->next, last);
        first->next->prev = first;
        //Sets prev to NULL and returns the value of first
        first->prev = NULL;
        return first;
    }
    else
    {
        last->next = merge(first, last->next);
        last->next->prev = last;
        //Sets prev to NULL and returns the value of last
        last->prev = NULL;
        return last;
    }
}

#endif