
#ifndef JOIN_H
#define JOIN_H
#include <variant>
#include "Operator.h"
#include "FileReader.h"
#include <vector>

class Join : public Operator {
  public:
    Operator* r_input;
    Operator* l_input;
    FileReader l_fr;
    FileReader r_fr;

    string r_attr;
    string l_attr;

    int r_index;
    int l_index;
    vector<Record> r_page;
    vector<Record> l_page;

    bool first_pass = true;

    Join(Operator *op1, Operator *op2, string pAttr1, string pAttr2) {
      // Implement this (no need for the fileReader since both are operators)
      l_input = op1;
      r_input = op2;

      l_attr = pAttr1;
      r_attr = pAttr2;
    }
    Join(Operator *op, string fileName, string pAttr1, string pAttr2) {
      // Implement this
      l_input = op; // set the operator

      r_fr.setFileName(fileName); // set the fileReader and the second right input
      r_input = &r_fr;

      //set the two attr to member variables
      l_attr = pAttr1;
      r_attr = pAttr2;
    }
    Join(string fileName1, string fileName2, string pAttr1, string pAttr2) {
      // Implement this
      //set the two fileReaders to open
      l_fr.setFileName(fileName1);
      r_fr.setFileName(fileName2);

      // have both inputs ready
      l_input = &l_fr;
      r_input = &r_fr;

      //set the two variant types (you might not need this but it wouldn't hurt just in case)
      l_attr = pAttr1;
      r_attr = pAttr2;
    }

    bool AdvanceToNextRecord() {
      r_index++;
      if (r_index == r_page.size()) {
          r_index = 0;
          l_index++;
      }
      if (l_index == l_page.size()) {
        l_index = 0;
        r_page = r_input -> next();
      
            if (r_page.empty()) {
              l_page = l_input -> next();
              if (l_page.empty()) {
                return true;
              }
            
              r_input -> close();
              r_input -> open();
              r_page = r_input -> next();
            }
    }
      return false;
    }

    void open() {
      // Implement this
      l_input -> open();
      r_input -> open();


    }

vector<Record> next() {
    vector<Record> outPage;
    if (first_pass == true){
        l_page = l_input -> next();
        r_page = r_input -> next();

        l_index = 0;
        r_index = -1;

        first_pass = false;
    }


    // while the outPage isn't full
    while (outPage.size() < pageSize) {

        //cout << "dumby dumb" << endl;

        // Call to AdvanceToNextRecords
        if (AdvanceToNextRecord() == true) {
            // Return if there is no more data (AdvanceToNextRecord returns true)
            return outPage;
        }

        Record left_r = l_page[l_index];
        Record right_r = r_page[r_index];

        if (left_r.get_Attribute(l_attr).value == right_r.get_Attribute(r_attr).value){
            Record newRecord = left_r + right_r;
            outPage.push_back(newRecord);
        }

    }

    return outPage;
}


    void close() {
      // Implement this
      l_input -> close();
      r_input -> close();
    }
};


#endif
