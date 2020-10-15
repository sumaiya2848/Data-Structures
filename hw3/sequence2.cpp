#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include "sequence2.h"

using namespace std;

namespace main_savitch_4 {

// sequence(size_type initial_capacity = DEAULT_CAPACITY)
// Postcondition: The sequence has been initialized as an empty sequence. The insert/attach functions will work efficiently (without allocating new memory) until this capacity is reached.

sequence::sequence(size_type initial_capacity) {

  //initialize data
  m_data = new value_type[initial_capacity]; 
  m_capacity = initial_capacity; //default is 30
  m_used = 0;
  m_current_index = 0;
  
  }
  
// sequence(const sequence& source)
// Postcondition: The bag that is being constructed has been initialized with the same items and capacity as source.

sequence::sequence(const sequence& source) {
  
  m_data = new value_type[source.m_capacity];
  m_capacity = source.m_capacity; //same capacity as source
  m_used = source.m_used; 
  m_current_index = source.m_current_index;
  copy(source.m_data, source.m_data + m_used, m_data); //copy items into new allocated array

}

// Postcondition: dynamically allocated memory for data member has been released
//destructor

sequence::~sequence() {
  
  delete [ ] m_data; // Deletes array when destructor is called 
  
  }

// void resize(size_type new_capacity)
// Postcondition: The sequence's current capacity is changed to the new_capacity (but not less that the number of items already on the sequence). The insert/attach functions will work efficiently (without allocating new memory) until this new capacity is reached.

void sequence::resize(size_type new_capacity) {
  
  value_type *new_data;
  
  if(new_capacity == m_capacity) 
  return; // The allocated memory is already the right size.
  
  if (new_capacity > m_used) {

    new_data = new value_type[new_capacity];
    copy(m_data, m_data + m_used, new_data); 
    delete [ ] m_data;
    m_data = new_data;
    m_capacity = new_capacity;

    } else if (new_capacity < m_used) {

     new_capacity = m_used; // Can’t allocate less than we are using.
    
  }
}

// void start( )
// Postcondition: The first item on the sequence becomes the current item (but if the sequence is empty, then there is no current item).

void sequence::start() {
  
  //sets index to the start
  if(size() > 0)
  m_current_index = 0;
  
  }

// void advance( )
// Precondition: is_item returns true.
// Postcondition: If the current item was already the last item on the sequence, then there is no longer any current item. Otherwise, the new current item is the item immediately after the original current item.

void sequence::advance() {
  
  if (m_current_index == m_used) // If item last item, then no current item
  m_current_index = 0;
  else m_current_index++; //Else new item comes after
    
  }

// void insert(const value_type& entry)
// Postcondition: A new copy of entry has been inserted in the sequence before the current item. If there was no current item, then the new entry has been inserted at the front of the sequence. In either case, the newly inserted item is now the current item of the sequence.

void sequence::insert(const value_type& entry) {
  
  if(m_used == m_capacity)
  resize(m_used + 1); // Increase
  
  if(!is_item()) //if not current item
  m_current_index = 0; //set in front of list
  
  for(int i = m_used; i > m_current_index; i--) //shift items
  m_data[i] = m_data[i-1];
  m_data[m_current_index] = entry; //insert entry to new empty current_index
  m_used++;
  
  }	

// void attach(const value_type& entry)
// Postcondition: A new copy of entry has been inserted in the sequence after the current item. If there was no current item, then the new entry has been attached to the end of the sequence. In either case, the newly inserted item is now the current item of the sequence.

void sequence::attach(const value_type& entry) {
  
  if (m_used == m_capacity)
  resize(m_used + 1);  // Increase
  
  if (!is_item()) //if not current item
  m_current_index = m_used - 1; //Entry after the current used
  m_current_index++;
  
  for (int i = m_used; i > m_current_index; i--) //shift items
  m_data[i] = m_data[i-1];
  m_data[m_current_index] = entry; //insert entry to new empty current_index
  m_used++;
  
  }

// void remove_current( )
// Precondition: is_item returns true.
// Postcondition: The current item has been removed from the sequence, and the item after this (if there is one) is now the new current item.

void sequence::remove_current() {
  
  assert(is_item() == true); // if is_item returns true
  for(int i = m_current_index; i < m_used - 1; i++)//shift items
  m_data[i] = m_data[i+1];
  m_used--; //one less item
  
  }

// size_type size( ) const
// Postcondition: The return value is the number of items on the sequence.

sequence::size_type sequence::size() const {
  
  return m_used; //return number of items
  
  }

// bool is_item( ) const
// Postcondition: A true return value indicates that there is a valid "current" item that may be retrieved by activating the current member function (listed below). A false return value indicates that there is no valid current item.

bool sequence::is_item() const {
  
  return (m_current_index < m_used) ? true : false; //if current_index < used then true, if not then false
  
  }

// value_type current( ) const
// Precondition: is_item( ) returns true.
// Postcondition: The item returned is the current item on the sequence.

sequence::value_type sequence::current() const {
  
  assert(is_item() == true); //is_item( ) returns true
  return m_data[m_current_index]; //inserted item is current item
  
  }
  
//void operator=(const sequence& source);
// Postcondition: The sequence that activated this function has the same items and capacity as source.

void sequence::operator =(const sequence& source) {
  value_type *new_data;
  // Check for possible self-assignment
  if(this == &source)
  return;
  
  //Allocate new array
  new_data = new value_type[source.m_capacity];
  copy(source.m_data, source.m_data+source.m_used, new_data); // copy data from the source
  delete [ ] m_data; // Release old array
  m_data = new_data;
  m_used = source.m_used;
  m_capacity = source.m_capacity; //same capacity as source
  
  if(source.is_item())
  m_current_index = source.m_current_index;
  
  else
  m_current_index = m_used;

}

// void operator+=(const sequence& source);
// Postcondition: Each item in source has been added to the bag.

void sequence::operator +=(const sequence& source) {
  
  if (m_used + source.m_used > m_capacity) //ensure that there is enough room for the new items.
  resize(m_used + source.m_used);
  copy(source.m_data, source.m_data + source.m_used, m_data + m_used); //copy data from the source
  m_used += source.m_used;
  
  }
  
// sequence operator +(const sequence& s1, const sequence& s2);
// Postcondition: Returned is the union of s1 and s2.

sequence operator +(const sequence& s1, const sequence& s2) {
  
  sequence answer(s1.size( ) + s2.size( ));
  answer += s1;
  answer += s2;
  return answer;
  
  }
  
// value_type operator[](size_type index) const;
// Precondition: index < m_capacity and m_used.
// Postcondition: Returned is the value at the specified position. 

sequence::value_type sequence::operator[] (sequence::size_type index) const {
  
  // Index cannot be greater than capacity or used.
  assert(index < m_capacity);
  assert(index < m_used);
  
  return m_data[index];
  
  }

}