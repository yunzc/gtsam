/**
 * @file    VariableSlots.cpp
 * @brief   
 * @author  Richard Roberts
 * @created Oct 5, 2010
 */

#include <gtsam/inference/VariableSlots.h>

#include <iostream>
#include <boost/foreach.hpp>

using namespace std;

namespace gtsam {

/** print */
void VariableSlots::print(const std::string& str) const {
  if(this->empty())
    cout << "empty" << endl;
  else {
    cout << str << "\n";
    cout << "Var:\t";
    BOOST_FOREACH(const value_type& slot, *this) { cout << slot.first << "\t"; }
    cout << "\n";

    for(size_t i=0; i<this->begin()->second.size(); ++i) {
      cout << "    \t";
      BOOST_FOREACH(const value_type& slot, *this) {
        if(slot.second[i] == numeric_limits<Index>::max())
          cout << "x" << "\t";
        else
          cout << slot.second[i] << "\t";
      }
      cout << "\n";
    }
  }
}

/** equals */
bool VariableSlots::equals(const VariableSlots& rhs, double tol) const {
  return *this == rhs;
}

}
