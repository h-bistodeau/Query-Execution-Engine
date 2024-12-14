#ifndef FILEREADER_H
#define FILEREADER_H
#include <vector>
#include <sstream>
#include <fstream>
#include "Record.h"
#include "Operator.h"
using namespace std;

// line 1 of the file is always the attribute names
// line 2 is always the types to match
// junk characters separate the corresponding record values

class FileReader : public Operator {
  public:
    string filename;
    fstream file;
    int page_count;
    vector<string> attr_names;
    vector<string> attr_types;

  void setFileName(string givenName) {
    filename = givenName;
  }

  vector<string> split(string line){
    vector<string> v; // stores the broken up string parts
    string s; // big string that you initially start with
    istringstream is(line);
    while (getline(is, s, ',')) // looks for the commas while the string is not nothing
      v.push_back(s); // adds that chunk to the vector
    return v;
  }

    void open() {
      // Implement this
      file.open(filename, ios :: in);

      if (file.is_open()) {
        string line;
        getline(file, line);
        attr_names = split(line); // get the first line and set that as the attribute name

        getline(file, line);
        attr_types = split(line); // pull the second line and set it to the attribute types

        getline(file, line); // junk characters
      }
      else
        cout << "Error opening file " << filename << endl;

    // handle the first two lines in here then use seekg to jump down three lines in the next() function
    // that way in case he calls next multiple times the attribute variables and junk dont get in the way
    }

    vector<Record> next() {
      vector<Record> Outpage;
      string line;
      int i = 0;
      if (file.is_open()) {
        // should be able to start with the records now
        for (i = 0; i < pageSize && getline(file, line); i++) {
          Record r_1;
          vector<string> record_vals = split(line);

          for (int j = 0; j < record_vals.size(); j++) {
            r_1.Add_Attribute(attr_names[j], record_vals[j], attr_types[j]);
          }
          Outpage.push_back(r_1);
        }
        // Return an empty vector if no more pages exist
      }
      return Outpage;
      //return outPage;
    }

    void close() {
      // Implement this
      if (file.is_open()){
        file.close();
      }
    }
};

#endif
