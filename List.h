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

#include <iostream>
using namespace std;

template <class T> 
class List
{
    private:
        struct ListNode
        {
            T *value;
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
    nodePtr = head; //Sets nodePtr to the head of the list

    //While nodePtr points to a node, traverse the list
    while(nodePtr)
    {
        cout << nodePtr->value << endl; //Displays the value of a node
        nodePtr = nodePtr->next; //Sets the nodePtr to the next node of the list
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
    newNode->value=&newValue;
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
    //Calls mergesort function to perform the mergesort
    head = mergesort(head, tail);
    
    //Finds the new tail by traversing the list
    tail = head;
    while(tail != NULL && tail->next != NULL)
    {
        tail = tail->next;
    }
}

template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* first, ListNode* last)
{
    ListNode* mid;
    ListNode* left;
    ListNode* right;

    //Base case for when list partition is zero or one node, function returns first parameter
    if(first == NULL || first == last)
    {
        cout<<"\n\nreturn mergesort\n\n";
        return first;
    }

    //Splits the list into two partitions and sort each partition recursively
    mid = split(first, last);
    left = mergesort(first, mid);
    right = mergesort(mid->next, last);

    //Merges the sorted partitions and returns the merged list
    cout<<"\n\nmerge partitions\n\n";
    return merge(left, right);
}

template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* first, ListNode* last)
{
    cout<<"\nenter split\n";
    int n=0;
    ListNode* slow;
    ListNode* fast;
    ListNode* mid;

    if(first == NULL || last == NULL || first == last)
    {
        cout<<"\nempty or one node split\n";
        return NULL; //Returns NULL if the partition is empty or has only one node
    }

    slow = first;
    fast = first->next;

    //Traverses the list with two pointers, one moving one step at a time, the other moving two steps at a time
    while(fast != last && fast->next != last)
    {
        slow = slow->next;
        fast = fast->next->next;
        cout<<"\nsplit n: "<<n<<"\n";
        n++;
    }

    mid = slow->next;
    slow->next = NULL; //Sets the next pointer of node before mid to NULL to split the list

    if(mid != NULL)
    {
        mid->prev = NULL; //Sets the previous pointer of mid to NULL
    }

    return mid; //Returns the middle node
}

template <typename T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* last)
{
    ListNode* merged = NULL;

    //Base case if either node is NULL, then return the other nodes
    if(first == NULL)
    {
        return last;
    }
    else if(last == NULL)
    {
        return first;
    }

    //Compares the value of the nodes
    if(first->value > last->value)
    {
        merged = first;
        merged->next = merge(first->next, last);
        merged->next->prev = merged;
    }
    else
    {
        merged = last;
        merged->next = merge(first, last->next);
        merged->next->prev = merged;
    }

    //Sets the previous pointer of merged node to NULL
    merged->prev = NULL;

    return merged;
}

#endif