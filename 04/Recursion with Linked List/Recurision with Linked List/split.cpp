/*
A recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. 
*/

#include "split.h"
#include <cstddef>

/* Add a prototype for a helper function */
void add_to_sorted_list(Node*& head, Node*& in);
void add_to_sorted_list_recursion(Node*& curr, Node*& in);

void split(Node*& in, Node*& odds, Node*& evens)
{
  if(in == NULL){
    return;
  }
  else{
    Node* headNode = in;
    Node* nextNode = in;
    nextNode = nextNode->next;
    if(headNode->value%2 == 0){ //even
        add_to_sorted_list(evens, headNode);
    }
    else{ //odd
        add_to_sorted_list(odds, headNode);
    }
    // in = in->next
    split(nextNode, odds, evens);
  }

  in = NULL;
}

void add_to_sorted_list(Node*& head, Node*& in)
{
  if (in == NULL)
  {
    return;
  }
  if (head == NULL)
  {
    head = in;
    head->next = NULL;//need to set the next element to NULL
  }
  else 
  {
    add_to_sorted_list_recursion(head, in);
    //add_to_sorted_list(head,in);
  }
  return;
}

//This function is not necessarily Needed as the input Node is already sorted
void add_to_sorted_list_recursion(Node*& curr, Node*& in)
{
  if (curr->next == NULL){
    curr->next = in;
    curr->next->next = NULL;
    return;
  }
  else{
    if(curr->value > in->value){
      in->next = curr;
      curr = NULL;
      return; 
    }
    else{
      add_to_sorted_list_recursion(curr->next, in);
    }
  }
}

