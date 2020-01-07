/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
// edited
#include "List.h"

template <class T>
List<T>::List() {
  // @ graded in MP3.1  DONE
    head_ = NULL;
    tail_ = NULL;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @ graded in MP3.1   DONE
  return List<T>::ListIterator(head_);    //Changed NULL to head_
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @ graded in MP3.1    DONE no change
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @ Graded in MP3.1 DONE
  ListNode* curr;
  ListNode* temp;
  curr = head_;
  while(curr != NULL){
    temp = curr;
    curr = curr->next;
    delete temp;
  }
  head_ = NULL;
  tail_ = NULL;
  temp = NULL;
  length_= 0;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @ Graded in MP3.1          DONE
  if (head_ == NULL) {
      head_ = new ListNode(ndata);   //set nect and prev as null and node as tail }
      head_ -> next = NULL;
      head_ -> prev = NULL;
      tail_ = head_;
    length_++;}
  else {
      ListNode* front = new ListNode( ndata);
      front->next = head_;
      head_ -> prev = front;
      head_ = front;
      front -> prev = NULL;
      length_++;
  }
}
/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  if (tail_ == NULL) {
      tail_ = new ListNode(ndata);   //set nect and prev as null and node as tail }
      tail_ -> next = NULL;
      tail_ -> prev = NULL;
      head_ = tail_;
    length_++;}
  /// @ Graded in MP3.1    DONE
  /*ListNode* temp = new ListNode(ndata);
  if(length_ == 0){
    head_ = temp;
    tail_ = temp;
    length_++; */

  else{
    ListNode* back = new ListNode(ndata);
    tail_->next = back;
    back->prev = tail_;
    tail_ = back;
    tail_ -> next = NULL;
    length_++;
}
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @ Graded in MP3.1                  DONE
  if(splitPoint == 0  || head_ == NULL ){
      return start;
    }
    ListNode* temp;
    ListNode* temp2 = start;
    ListNode* temp3;
    for(int i = 1; i <= splitPoint; i++) {
      temp = temp2;
      temp2 = temp2->next;
    }
    temp3 = temp -> next;
    temp->next = NULL;
    temp3 -> prev = NULL;
    return temp3;
  }

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @ Graded in MP3.1   DONE
  if(head_ == NULL){return;}
ListNode* curr, *temp;
int count = 1;
curr = head_;
while(curr != tail_ && curr != NULL){
  if(count % 2 == 0){
    curr->prev->next = curr->next;
    temp = curr;
    curr = curr->next;
    temp->next = NULL;
    //length_--;
    //insertBack(temp);
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = tail_->next;
  }
  else{
    curr = curr->next;    //No change
  }
  count++;
}
return;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2     DONE
  ListNode *curr_start_org = startPoint;
    ListNode *curr_end_org  = endPoint;
    ListNode *curr_end_org_next;
    ListNode *curr_start_org_next;


    ListNode *curr_start_next;
    ListNode *curr_start_prev;
    ListNode *curr_end_next;
    ListNode *curr_end_prev;
    while(1){
        if (curr_start_org->next == curr_end_org){
          curr_start_org->next = curr_end_org->next;
          curr_end_org ->prev = curr_start_org->prev;

          curr_end_org ->next = curr_start_org;
          curr_start_org->prev = curr_end_org;
          if (curr_start_org->next == NULL){
            tail_ = curr_start_org;
          }
          else{
            curr_start_org->next->prev = curr_start_org;
          }
          if (curr_end_org->prev == NULL){
            head_ = curr_end_org;
          }
          else{
            curr_end_org->prev->next = curr_end_org;
          }
          break;
        }
        else{
          if (curr_end_org == curr_start_org){
            break;
          }
          curr_start_next = curr_start_org -> next;
          curr_start_prev = curr_start_org ->prev;
          curr_end_next = curr_end_org -> next;
          curr_end_prev = curr_end_org ->prev;
          curr_end_org_next = curr_end_prev;
          curr_start_org_next = curr_start_next;


          curr_start_org->next = curr_end_next;
          curr_start_org->prev = curr_end_prev;
          curr_end_org->next = curr_start_next;
          curr_end_org->prev = curr_start_prev;
          if (curr_start_org->next == NULL){
            tail_ = curr_start_org;
          }
          else{
            curr_start_org->next->prev = curr_start_org;
          }
          if (curr_end_org->prev == NULL){
            head_ = curr_end_org;
          }
          else{
            curr_end_org->prev->next = curr_end_org;
          }
          curr_end_org_next->next = curr_start_org;
          curr_start_org_next->prev = curr_end_org;
          curr_start_org = curr_start_org_next;
          curr_end_org = curr_end_org_next;

        }

    }}
/*  if(startPoint == endPoint) { return; }    //Empty case

     ListNode* temp = startPoint;
     ListNode * temp2 = startPoint;
     ListNode * temp3 = endPoint->next;

     while (temp != temp3)
     {
         temp2 = temp->prev;
         temp->prev = temp->next;
         temp->next = temp2;
         temp = temp->prev;
     }

     temp2 = endPoint->prev;

     if (startPoint->next != NULL)
     {
         endPoint ->prev = startPoint->next;
         startPoint->next->next = endPoint;
     } else
         endPoint ->prev = NULL;

     if (temp2 != NULL)
     {
         startPoint->next = temp2;
         temp2->prev = startPoint;
     } else
         startPoint ->next = NULL;

     temp = startPoint;
     startPoint = endPoint;
     endPoint = temp;
     temp = NULL;
     temp2 = NULL;
} */

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2  TODO
    int k;
    ListNode* curr_start = head_;
    ListNode* curr_end = head_;
    ListNode* curr_start_next = NULL ;
    ListNode* curr_end_next = NULL;
    ListNode* tail = tail_;

    while(curr_start!= NULL){
      k =  n-1;
      while(k!=0 && curr_end != tail){
        curr_end = curr_end->next;
          k = k-1;
      }
      curr_start_next = curr_end->next;
      curr_end_next = curr_end->next;
      reverse(curr_start, curr_end);
      curr_start = curr_start_next;
      curr_end = curr_end_next;
    }
    }


/*
  ListNode * curstart = head_;
  ListNode * curend = curstart;

  while (curstart != NULL) {
    int count = 1;
    while (count < n) {
      if (curend != tail_) {
        curend = curend->next;
      }
      count++;
    }
    reverse(curstart, curend);
    curstart = curstart->next;
    curend = curstart;
}

  if(n <= 1 || head_ == NULL)  {return; }

  ListNode *blockstart, *blockend;
  blockstart = head_;
  blockend = tail_;

//  while(blockstart != NULL){

    blockend = blockstart;
    for(int i = 0; i < n - 1; i++){
      if(blockend->next != NULL){
        blockend = blockend->next;    */
    //  }
    //}

    /*reverse(blockstart, blockend);
    blockstart -> prev = NULL;
    blockend -> next = NULL; */
  //  blockstart = blockend->next;




/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if (first == NULL) {return second; }
  if (second == NULL) {return first; }
  ListNode *first_node;
  ListNode *second_node;
  ListNode *head;
  ListNode* curr;
  if (first->data <second->data){
      first_node = first;
      second_node = second;
      head = first;
  }
  else{
      first_node = second;
      second_node = first;
      head = second;
  }
  while(second_node != NULL){
    curr = second_node;

    if(first_node->next == NULL){
      first_node->next = curr;
      curr->prev = first_node;
      second_node = NULL;
      break;
    }
    ListNode* next_node = first_node->next;

    if (first_node->data < curr->data){
    if (!(next_node->data < curr->data)){
      second_node = second_node->next;
      curr->prev = first_node;
      curr->next = first_node->next;
      first_node->next->prev = curr;
      first_node->next = curr;
    }    }

    else if (first_node->data == curr->data){
    if (!(next_node->data < curr->data)){
      second_node = second_node->next;
      curr->prev = first_node;
      curr->next = first_node->next;
      first_node->next->prev = curr;
      first_node->next = curr;
    }    }

    first_node = first_node->next;
  }

  return head;
}
  /// @todo Graded in MP3.2
/*return NULL; //REMOVE
if(first == NULL){return second;}
if(second == NULL){return first;}
if(first == NULL && second == NULL){return NULL;}
ListNode* temp, *curr_first, *curr_second, *first_next, *second_next;

//choose head to be first
if(second->data < first->data){
  temp = second;
  second = first;
  first = temp;
  if(first != NULL) { first->prev = NULL; }
}
} */
/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  /*  if (start == NULL){ return NULL; }
    if (chainLength == 1) {return start; }

    int len = chainLength/2;    //Halfing
    int len1 = chainLength-len;
    int len2 = chainLength-len1;
    ListNode* current = start;

    while(len>0) {
        start = start->next;
        len = len - 1;
    }
    start->prev->next = NULL;
    start->prev = NULL;
    ListNode* first = mergesort(current, len2);
    ListNode* second = mergesort(start, len1);


    return merge(first, second); }   //Merge is a void fn too */

  if (chainLength == 1 || start == NULL) {
		return start;
	} else {
		ListNode* headB = split(start, chainLength/2);
		headB = mergesort(headB, chainLength/2 + chainLength%2);
		start = mergesort(start, chainLength/2);
		return merge(start, headB);
}
    start->prev = NULL;
    start->next = NULL;
    return start;
  } /*
  ListNode * second = split(start, chainLength / 2);
  return merge(mergesort(start, chainLength / 2), mergesort(second, (chainLength % 2) + (chainLength / 2)));
  else{
    int breakpoint;
    breakpoint = int(chainLength / 2);
    ListNode* temp = start;
    for(int i = 1; i <= breakpoint; i++){
      temp = temp->next;
    }
    if (temp != NULL){  //separate the lists
      temp->prev->next = NULL;
      temp->prev = NULL;
    }
    start = mergesort(start, breakpoint);
    temp = mergesort(temp, chainLength - breakpoint);
    start = merge(start, temp);
    return start;
  }   */
