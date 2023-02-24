#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
    // if linked list is empty
    if (head == nullptr)
    {
        smaller = nullptr;
        larger = nullptr;
        return;
    }

    // if the linked list is not empty small val is smaller than pivot
    else if( head -> val <= pivot)
    {
        smaller = head;
        head = head->next;
        llpivot (head, smaller->next, larger, pivot);
    }
    // if the linked list is not empty small val is greater than pivot
    else 
    {
        larger = head;
        head= head->next;
        llpivot (head, smaller, larger->next, pivot);
    }
    // at the last element, make head null
    head = nullptr;

  
}




