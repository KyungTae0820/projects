#include "llrec.h"

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
  if(head == nullptr){
		//head = nullptr; //the linked list head no longer exists (head should be set to NULL).
		smaller = nullptr;
		larger = nullptr;
		return; //handle the cases when an input linked list is empty
	} 
  if(head->val > pivot){
    larger = head;
		head = head->next;	
		larger->next = nullptr;
    llpivot(head, smaller, larger->next, pivot);
  }
  else{
    smaller = head;	
		head = head->next;
		smaller->next = nullptr;
    llpivot(head, smaller->next, larger, pivot);
  }
}

