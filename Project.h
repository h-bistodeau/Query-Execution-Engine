#ifndef PROJECT_H
#define PROJECT_H
#include "Record.h"
#include "Operator.h"
#include "FileReader.h"
#include <fstream>
#include <vector>
using namespace std;

class Project : public Operator {
  public:
    vector<string> kept_values; // attributes we want to keep
    Operator* input;
    FileReader fr;

    // Project constructors
    Project(string fileName, vector<string> fieldNames){
      kept_values = fieldNames;
      fr.setFileName(fileName);
      input = &fr;
    }

    Project(Operator *op, vector<string> fieldNames) {
      // Implement this
      kept_values = fieldNames;
      input = op;
    }

    void open() {
      // Implement this
      input -> open();
    }

    vector<Record> next() {
      vector<Record> outPage;
      vector<Record> inPage = input -> next();

      // for the length of inPage (for each record)
      for (int i = 0; i < inPage.size(); i++) {
        // for every attribute in that record
        Record record = inPage [i];
        Record outRecord;// create another record instance

        //for the fieldnames that we are keeping
        for (int k = 0; k < kept_values.size(); k++) {

          // for the attributes in record
          for (int j = 0; j < record.Attributes.size(); j++) {
            if (record.Attributes[j].name == kept_values[k]) //if that record attribute name equals a name we want to keep
              outRecord.Add_Attribute(record.Attributes[j].name, record.Attributes[j].value, record.Attributes[j].type);
          }
        }
        outPage.push_back(outRecord);
        // Return an empty vector if no more pages exist
      }
      return outPage;
    }

    void close() {
      // Implement this
      input -> close();
    }
};

#endif
