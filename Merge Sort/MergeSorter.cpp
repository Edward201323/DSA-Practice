#include "MergeSorter.hpp"

MergeSorter::MergeSorter() {
    numComparisons = 0;
}

bool MergeSorter::lessThan(int left, int right) {
    numComparisons++;
    return left < right;
}

// Splits the given linked list into two equal sublists (or nearly equal when the length is odd).
// The passed `head` argument remains the head of a now-shorter list
// (NOTE: Make sure it ends with a nullptr link!);
// the return value is the head of the other sublist.
Node* MergeSorter::split(Node *head) {
    if(head == nullptr || head->next == nullptr){
        return nullptr;
    }
    
    Node *slow = head;
    Node *fast = head->next;

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *second_half = slow->next;
    slow->next = nullptr;

    return second_half;
}


// Combines two sorted lists and returns a pointer to the head of the now-sorted combined list
// (NOTE: use a `last` pointer on the list you're building so that appending is always O(1) )
Node* MergeSorter::merge(Node *head1, Node *head2) {
    Node dummy;
    Node *curr = &dummy;
    
    while(head1 && head2){
        if(lessThan(head1->data, head2->data)){
            curr->next = head1;
            head1 = head1->next;
        } else {
            curr->next = head2;
            head2 = head2->next;
        }
        curr = curr->next;
    }

    if(head1){
        curr->next = head1;
    }
    else if(head2){
        curr->next = head2;
    }

    return dummy.next;

}

// Performs merge sort on the given linked list:
// - base case: when the list has <= 1 nodes, return that list
// - otherwise:
//   - split the list
//   - recursively sort each half
//   - merge the two halves and return the result
Node* MergeSorter::mergeSort(Node *head) {
    if(head == nullptr || head->next == nullptr){
        return head;
    }

    Node *secondHalf = split(head);
    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);

    return merge(head, secondHalf);
}