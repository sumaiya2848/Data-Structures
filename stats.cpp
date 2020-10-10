#include <iostream>
#include <cassert>
#include "stats.h"

namespace main_savitch_2C {

statistician::statistician() {
  
  reset(); //values are listed under: void statistician::reset()

}

void statistician::next(double r) {
  
  if (m_count < 1) {
    m_tinyest = r; 
    m_largest = r;

  } if (r > m_largest) {
    //anytime there is a input, "r" greater than the current largest, "r" becomes the largest.
    m_largest = r;

  } else if(r < m_tinyest) {
    //anytime there is a input, "r" less than the current smallest, "r" becomes the tinyest.
    m_tinyest = r;
    
  }
  
  m_count ++; //anytime there is another number "r" added, the count goes up by 1
  m_total += r; //anytime there is another number "r" added, the sum goes up by that number "r"
  
  }

void statistician::reset() {
//initialized
  m_count = 0;
  m_total = 0;
  m_tinyest = 0;
  m_largest = 0;

}

int statistician::length() const {

  return m_count;

}

double statistician::sum() const {

  return m_total;

}

double statistician::mean() const {
  
  assert(length() > 0);
  return m_total / m_count;

}

double statistician::minimum() const {
  
  assert(length() > 0);
  return m_tinyest;

}

double statistician::maximum() const {
  
  assert(length() > 0);
  return m_largest;

}

statistician operator+(const statistician& s1, const statistician& s2) {
  
  if (s1.length() == 0) //if empty
    return s2;
  if (s2.length() == 0) 
    return s1;

  statistician value;

  value.m_count = s1.m_count + s2.m_count;
  value.m_total = s1.m_total + s2.m_total;

  if (s1.m_tinyest <= s2.m_tinyest) { //if tinyest s1 is less than or equal to tinyest s2 then, make it s1
    value.m_tinyest = s1.m_tinyest;

  } else {
    
    value.m_tinyest = s2.m_tinyest;

  }
  
  if (s1.m_largest >= s2.m_largest) { //if largest s1 is greater than or equal to largest s2 then, make it s1
    value.m_largest = s1.m_largest;

  } else {
    
    value.m_largest = s2.m_largest;

  }
  return value;
}
  
  statistician operator*(double scale, const statistician& s) {

    statistician value;
    value.m_count = s.m_count;
    value.m_total = scale * s.m_total;

    if (scale >= 0) { //if we have a value greater than or equal to zero (positive number), then we can multiply and get the tinyest value by multiplying by tinyests and vice versa. But if we have a negative number, then we will have to switch them.
      value.m_tinyest = scale * s.m_tinyest;
      value.m_largest = scale * s.m_largest;

    } else {

      value.m_tinyest = scale * s.m_largest;
      value.m_largest = scale * s.m_tinyest;

    }

    return value;

  }

  bool operator == (const statistician& s1, const statistician& s2) {

    if (s1.length() == 0 && s2.length() == 0) {
      
      return true;

    } else if ((s1.length() == s2.length()) && (s1.sum() == s2.sum()) && (s1.minimum() == s2.minimum()) && (s1.maximum() == s2.maximum()) && (s1.mean() == s2.mean())) {
      
      return true;

    } else {
      
      return false; 

    }

  }

}