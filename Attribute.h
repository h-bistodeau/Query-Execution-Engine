
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Attribute {
public:
  string name;
  string type;
  string value;

  // Modified Create_Attribute method
  void Create_Attribute(string attr_name, string attr_value, string attr_type) {
    name = attr_name;
    type = attr_type;
    value = attr_value;
  }
};

#endif