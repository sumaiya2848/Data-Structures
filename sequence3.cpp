#include <cassert> // Provides assert
#include <cstdlib> // Provides NULL, rand, size_t
#include "node1.h" // Provides node and the linked-list functions
#include "sequence3.h"

using namespace std;

namespace main_savitch_5 {
  
//Postcondition: The sequence has been initialized as an empty sequence.
sequence::sequence( ) {
//Run time analysis: O(1) (constant)
//initializes private member variables
  m_head_ptr = NULL;
  m_tail_ptr = NULL;
  m_cursor = NULL;
  m_precursor = NULL;
  m_many_nodes = 0;  

}

//Copy constructor
sequence::sequence(const sequence& source) {
//Run time analysis: O(n) (linear)
  node *tail_ptr; // Needed for argument of list_copy
  list_copy(source.m_head_ptr, m_head_ptr, m_tail_ptr); // Copies everything from source
  list_copy(source.m_cursor, m_cursor, m_precursor);
  m_many_nodes = source.m_many_nodes;

}

//Destructor
sequence::~sequence( ) {
//Run time analysis: O(n) (linear)
  list_clear(m_head_ptr); // list_clear function from node1.cpp
  m_many_nodes = 0;

}

// Postcondition: The first item on the sequence becomes the current item (but if the sequence is empty, then there is no current item).
void sequence::start( ) {
//Run time analysis: O(1) (constant)
  m_cursor = m_head_ptr; // first item becomes current item
  m_precursor = NULL; // if empty, no current item

}

// Precondition: is_item returns true.
// Postcondition: If the current item was already the last item on the sequence, then there is no longer any current item. Otherwise, the new current item is the item immediately after the original current item.
void sequence::advance( ) {
//Run time analysis: O(1) (constant)  
  assert(is_item()); // Precondition
  m_precursor = m_cursor; 
  m_cursor = m_cursor->link(); //new current is after original current

}

// Postcondition: A new copy of entry has been inserted in the sequence before the current item. If there was no current item, then the new entry has been inserted at the front of the sequence. In either case, the newly inserted item is now the current item of the sequence.
void sequence::insert(const value_type& entry) {
//Run time analysis: O(1) (constant) 
  if(!is_item()) { //if no current item

  list_head_insert(m_head_ptr, entry); //inserted at front
  m_cursor = m_head_ptr; //head_ptr becomes current
  m_precursor = NULL;
  
  } else {
    
    if(m_cursor == m_head_ptr) { //if current is at the head_ptr
      
      list_head_insert(m_head_ptr,entry);
      m_cursor = m_head_ptr;
      m_precursor = NULL;
      
      } else { //if current located anywhere else
        
        list_insert(m_precursor, entry);
        m_cursor = m_precursor->link(); //current will be what the precursor points to
      
      }
    }
    m_many_nodes++; //increase
}

// Postcondition: A new copy of entry has been inserted in the sequence after the current item. If there was no current item, then the new entry has been attached to the end of the sequence. In either case, the newly inserted item is now the current item of the sequence.
void sequence::attach(const value_type& entry) {
//Run time analysis: O(1) (constant)  
  if(is_item()) { //if there is a current item
    
    list_insert(m_cursor, entry);
    m_precursor = m_cursor;
    m_cursor = m_cursor->link();
    
  } else { // if no current item
    
    if(m_precursor == NULL) { // If nothing before the current
      
      list_head_insert(m_head_ptr,entry);
      m_cursor = m_head_ptr;
      m_precursor = NULL;
      
      } else {
        
        m_cursor = list_locate(m_head_ptr, list_length(m_head_ptr));
        list_insert(m_cursor, entry);
        m_cursor = m_precursor->link();
        
        }
    }
   m_many_nodes++; //increase total
}

// Precondition: is_item returns true.
// Postcondition: The current item has been removed from the sequence, and the item after this (if there is one) is now the new current item.
void sequence::remove_current( ) {
//Run time analysis: O(1) (constant)
  assert(is_item() == true); // if is_item returns true
  
  if(m_cursor == m_head_ptr) {
    
    list_head_remove(m_head_ptr);
    m_cursor = m_head_ptr;
    m_precursor = NULL;
    
    } else {
      
      m_cursor = m_cursor ->link();
      list_remove(m_precursor);
      
      }
      m_many_nodes--; //decrease total
}

//copy
void sequence::operator =(const sequence& source) {
//Run time analysis: O(n) (linear)  
  node *tail_ptr; // Needed for list_copy
  // Check for possible self-assignment
  if (this == &source)
  return;

  list_clear(m_head_ptr);
  m_many_nodes = 0;
  list_copy(source.m_head_ptr, m_head_ptr, m_tail_ptr); //copies everything from source
  m_many_nodes = source.m_many_nodes;
  
  m_cursor = m_head_ptr; //Assume the cursor is the head pointer
  m_precursor = NULL; //Since cursor is head pointer, there is nothing before cursor
  
  node* travel = source.m_head_ptr;
  while(travel != NULL && travel != source.m_cursor) { // Pointer will travel until finds current item
    
    travel = travel ->link();
    m_precursor = m_cursor; //precursor and cursor will also move until current item is found.
    m_cursor = m_cursor ->link();
    
    }
}

// Postcondition: The return value is the number of items on the sequence.
size_t sequence::size( ) const {
//Run time analysis: O(1) (constant)
  return m_many_nodes; //number of items in sequence

}

// Postcondition: A true return value indicates that there is a valid "current" item that may be retrieved by activating the current member function (listed below). A false return value indicates that there is no valid current item.
bool sequence::is_item( ) const {
//Run time analysis: O(1) (constant)
  return m_cursor != NULL && size() > 0; //when there is a value in the sequence, then there is a current

}

// Precondition: is_item( ) returns true.
// Postcondition: The item returned is the current item on the sequence.
sequence::value_type sequence::current( ) const {
//Run time analysis: O(1) (constant)
  assert(is_item()); //precondition
  return m_cursor->data();
  
  }
}