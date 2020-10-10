#include <iostream>
#include <cassert> // Provides assert function
#include "sequence1.h"

using namespace std;

namespace main_savitch_3 {
  
  //const sequence::size_type sequence::CAPACITY;

//Postcondition: The sequence has been initialized as an empty sequence.
  sequence::sequence() {

		used = 0; //no inputs
		current_index = 0;
  
  	}

//Postcondition: The first item on the sequence becomes the current item (but if the sequence is empty, then there is no current item).
  void sequence::start() {
    
    current_index = 0; 

	}
  
//Precondition: is_item returns true.
//Postcondition: If the current item was already the last item in the sequence, then there is no longer any current item. Otherwise, the new current item is the item immediately after the original current item.
  void sequence::advance() {
    
    if (current_index == used) // If item last item, then no current item
		current_index = 0;
    else current_index++; //Else new item comes after

	}
  
//Precondition: size( ) < CAPACITY.
//Postcondition: A new copy of entry has been inserted in the sequence before the current item. If there was no current item, then the new entry has been inserted at the front of the sequence. In either case, the newly inserted item is now the current item of the sequence.
  void sequence::insert(const value_type& entry) {
    
    assert(size() < CAPACITY);
    if (!is_item()) //if no item, then insert in front (position 0)
    current_index = 0;
    for (int i = used; i > current_index; i--) //shift items right by 1
    data[i] = data[i-1]; 
    data[current_index] = entry; //insert entry to new empty current_index
    used++;

   	 }

//Precondition: size( ) < CAPACITY.
//Postcondition: A new copy of entry has been inserted in the sequence after the current item. If there was no current item, then the new entry has been attached to the end of the sequence. In either case, the newly inserted item is now the current item of the sequence.
    void sequence::attach(const value_type& entry) {
      
      assert(size() < CAPACITY);
      if (!is_item()) //if not current item
      current_index = used - 1; //Entry after the current used
      current_index++; 
      for (int i = used; i > current_index; i--) //shift items
      data[i] = data[i-1];
      data[current_index] = entry; //insert entry to new empty current_index
      used++;

   	 }
    
//Precondition: is_item returns true.
//Postcondition: The current item has been removed from the sequence, and the item after this (if there is one) is now the new current item.
    void sequence::remove_current() {
      
      assert(is_item() == true); //is_item returns true
      for(int i = current_index; i < used - 1; i++)//shift items
      data[i] = data[i+1]; 
      used--; //one less item
		
    }
    
//Postcondition: The return value is the number of items in the sequence.
    sequence::size_type sequence::size() const {
      
      return used;

    }

//Postcondition: A true return value indicates that there is a valid "current" item that may be retrieved by activating the current member function (listed below). A false return value indicates that there is no valid current item.
    bool sequence::is_item() const {
      
      return (current_index < used) ? true : false; //if current_index < used then true, if not then false
      
    }

//Precondition: is_item( ) returns true.
//Postcondition: The item returned is the current item in the sequence.
    sequence::value_type sequence::current() const {
      
      assert(is_item() == true); //is_item( ) returns true
      return data[current_index]; //inserted item is current item

    }
}
