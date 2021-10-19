#include "Stack.h"

//----------------------------------------------------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------------------------------------------------
Stack::Stack()
{
  top = nullptr;
  stackSize = 0;
}

//----------------------------------------------------------------------------------------------------------------------
// IsEmpty - Tests to see if the stack is empty
//----------------------------------------------------------------------------------------------------------------------
bool Stack::IsEmpty()
{
  return (top == nullptr);
}

//----------------------------------------------------------------------------------------------------------------------
// GetANode - Will allocate memory for the node and fill it.
//----------------------------------------------------------------------------------------------------------------------
nodePtr Stack::GetANode(Card current)
{
  nodePtr ptr = new nodeStructType;

  ptr->data = current;

  ptr->next = nullptr;

  return ptr;
}

//----------------------------------------------------------------------------------------------------------------------
// GetTop - Will return the top card
//----------------------------------------------------------------------------------------------------------------------
nodePtr Stack::GetTop()
{
  return top;
}

//----------------------------------------------------------------------------------------------------------------------
// Pop - Get the value of the first card, assign it and take if off the stack.
//----------------------------------------------------------------------------------------------------------------------
Card Stack::Pop()
{
  nodePtr temp;
  Card tempCard;

  if (IsEmpty())
  {
    cout << "The Deck Is Empty" << endl;
    return tempCard;
  }
  else
  {
    // assign top to temp
    temp = top;

    // assign second node to the top
    top = top->next;

    // assigning data to a temp card
    tempCard = temp->data;

    // destroy's the connection
    temp->next = nullptr;

    // releases memory of top node
    free(temp);

    stackSize--;

    return tempCard;
  }

}

//----------------------------------------------------------------------------------------------------------------------
// Push - Put the card on to the top of the stack. 
//----------------------------------------------------------------------------------------------------------------------
void Stack::Push(Card current)
{
  // creating new node
  struct nodeStructType* temp;
  temp = new nodeStructType();

  if (!temp)
  {
    cout << "The Deck Is Full" << endl;
  }
  else
  {
    // initialize data into a temp data field
    temp->data = current;

    // Link the temp to the top 
    temp->next = top;

    // Make the temp the top of the stack
    top = temp;

    stackSize++;
  }

}

//----------------------------------------------------------------------------------------------------------------------
// CreateAStack - Sets the top to null
//----------------------------------------------------------------------------------------------------------------------
void Stack::CreateAStack()
{
  top = nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
// DestroyStack - Removes all the items from the stack when this method is called
//----------------------------------------------------------------------------------------------------------------------
void Stack::DestroyStack()
{
  while (!IsEmpty())
  {
    Pop();
  }
}

//----------------------------------------------------------------------------------------------------------------------
// selectionSort - recursive selection sort
//----------------------------------------------------------------------------------------------------------------------
nodePtr Stack::selectionSort(nodePtr head)
{
  // if the next node is null
  if (head->next == nullptr)
  {
    return head;
  }

  nodePtr temp = head;
  nodePtr previousTemp = nullptr;
  nodePtr ptr;

  // traverse the linked list
  for (ptr = head; ptr->next != nullptr; ptr = ptr->next)
  {
    temp = ptr->next;
    previousTemp = ptr;
  }

  // if temp isn't the head node
  if (temp != head)
  {
    Swap(&head, head, temp, previousTemp);
  }

  // call the function recursively
  head->next = selectionSort(head->next);

  // return the head
  return head;
}

//----------------------------------------------------------------------------------------------------------------------
// ShuffleStack - Shuffles the stack
//----------------------------------------------------------------------------------------------------------------------
void Stack::ShuffleStack()
{
  if ((top) == nullptr)
  {
    return;
  }

  top = selectionSort(top);
}

//----------------------------------------------------------------------------------------------------------------------
// Swap - Swaps the nodes
//----------------------------------------------------------------------------------------------------------------------
void Stack::Swap(nodePtr* firstPtr, nodePtr secondPtr, nodePtr thirdPtr, nodePtr fourthPtr)
{

  *firstPtr = thirdPtr;

  fourthPtr->next = secondPtr;

  nodePtr temp = secondPtr->next;
  secondPtr->next = thirdPtr->next;
  thirdPtr->next = temp;
}

//----------------------------------------------------------------------------------------------------------------------
// GetStackSize - Returns the stack size
//----------------------------------------------------------------------------------------------------------------------
int Stack::GetStackSize()
{
  return stackSize;
}

//----------------------------------------------------------------------------------------------------------------------
// FreeTheList - Frees all the memory in all the nodes of the list, Re-sets the count of the numbers in the list to 0 
//----------------------------------------------------------------------------------------------------------------------
void Stack::FreeTheList()
{
  nodePtr current = top;
  nodePtr next = nullptr;

  while (current != nullptr)
  {
    next = current->next;
    delete current;
    current = next;
  }
  top = nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------------------------------------------------
Stack::~Stack()
{

}