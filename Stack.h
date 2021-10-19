//----------------------------------------------------------------------------------------------------------------------
//File Name:        Stack.h
//Associated file:  Stack.cpp
//
//----------------------------------------------------------------------------------------------------------------------

#ifndef Stack_h
#define Stack_h

#include "DeckClassType.h"

// Definition of a node with a pointer to set for the next node
struct nodeStructType
{
  Card data;
  nodeStructType* next;
};

typedef nodeStructType* nodePtr;

class Stack
{
public:

  Stack();

  bool IsEmpty();

  nodePtr GetANode(Card current);

  nodePtr GetTop();

  Card Pop();

  void Push(Card current);

  void CreateAStack();

  void DestroyStack();

  int GetStackSize();

  void Swap(nodePtr* firstPtr, nodePtr secondPtr, nodePtr thirdPtr, nodePtr fourthPtr);

  void ShuffleStack();


  // I wanted to try a different sorting algorithm, so I based this one partially off of this one, 
  // https://www.geeksforgeeks.org/recursive-selection-sort-singly-linked-list-swapping-node-links/
  // I wasn't sure if this would count as "plagiarism", so thats why I gave partial credit.
  // I can rewrite this if you want me to.
  nodePtr selectionSort(nodePtr head);

  void FreeTheList();

  ~Stack();

private:

    nodePtr top;
    int stackSize;
};
#endif