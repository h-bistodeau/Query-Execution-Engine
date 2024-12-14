#ifndef RECORD_H
#define RECORD_H
#include "Attribute.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Record {
  public:
    vector<Attribute> Attributes; // all this class is is just a vector of attribute objects

    // Adds attributes to the vector
    void Add_Attribute(string name, string value, string type) {
      Attribute temp;
      temp.Create_Attribute(name, value, type);
      Attributes.push_back(temp);
    }

    Attribute get_Attribute(string name) {
      int i;
      for (i = 0; i < Attributes.size(); i++) {
        if (Attributes[i].name == name) {
          break;
        }
      }

      return Attributes[i];
    }
    friend ostream& operator<< (ostream& os, const Record& r) {
      // Implement this to write a string to os displaying all attribute values
        for (int i = 0; i < r.Attributes.size(); i++) { // for every object in the attributes vector
          os << r.Attributes[i].value << " "; // print it off
        }
      // Finally, return os
      return os;
    }

    friend Record operator+ (const Record& r1, const Record& r2) {
      Record r;

      for (int i = 0; i < r1.Attributes.size(); i++) {
        r.Attributes.push_back(r1.Attributes[i]);
      }

      for (int i = 0; i < r2.Attributes.size(); i++) {
        r.Attributes.push_back(r2.Attributes[i]);
      }

      return r;
      }

};

#endif
