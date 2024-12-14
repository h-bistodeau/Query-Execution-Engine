#ifndef SELECT_H
#define SELECT_H
#include <variant>
#include "Operator.h"

class Select : public Operator {
  public:
    string filename;
    Operator* input;
    FileReader fr;

    string rec_attr;
    string operator_;
    // the variant values make it possible to compare int and double val (without it it wouldn't)
    variant<int,double, string> compare_val;
    variant<int, double, string> record_val;

    vector<Record> inPage;
    int r;

    // Select constructors
    Select(string fileName, string p_attr, string p_op, string p_val) {
      // same as the project function
      fr.setFileName(fileName);
      input = &fr;

      // instead of setting the vector like we did in project i am creating the member variables for the predicate
      rec_attr = p_attr;
      operator_ = p_op;
      compare_val = p_val;
    }

    Select(Operator *op, string p_attr, string p_op, string p_val) {
      // Implement this
      input = op;
      rec_attr = p_attr;
      operator_ = p_op;
      compare_val = p_val;
    }

    void open() {
      // Implement this
        input -> open();
        r = 0;
    }

    vector<Record> next() {
        vector<Record> outPage;

        while (outPage.size() < pageSize) {
            if (r==0 || r==inPage.size()) {
                inPage = input->next();
                r = 0;
            }

            if (inPage.empty()){
                break;            
            } 

            // For each rec
            while (r < inPage.size()) {
                //cout << " - evaluating record: " << r << endl;
                Record record = inPage[r];
                r++;

                // For each rec attr
                for (int a = 0; a < record.Attributes.size(); a++) {
                    // Now the comparison between int and double values should work

                    if (record.Attributes[a].name == rec_attr) {
                        // moved down the type checker for only the correct attr name

                        if (record.Attributes[a].type == "int") {
                            //use the variant types to set both values to an int (record attr are always str at initalization)
                            // but since record_val has already been assigned type str just using stoi is enough to change types
                            compare_val = std::get<int>(compare_val);
                            record_val = stoi(record.Attributes[a].value);
                        } 
                        else if (record.Attributes[a].type == "double") {
                            // same as the int check but using a double instead
                            compare_val = std::get<double>(compare_val);
                            record_val = stod(record.Attributes[a].value);
                        } 
                        else {
                            compare_val = std::get<string>(compare_val);
                            record_val = record.Attributes[a].value;
                        }

                        // Actually do the comparison
                        if (operator_ == ">") {
                            if (record_val > compare_val) {
                                outPage.push_back(record);
                                if (outPage.size() == pageSize)
                                    return outPage;
                            }
                        } 
                        else if (operator_ == "<") {
                            if (record_val < compare_val) {
                                outPage.push_back(record);
                                if (outPage.size() == pageSize)
                                    return outPage;
                            }
                        } 
                        else if (operator_ == "=") {
                            if (record_val == compare_val) {
                                outPage.push_back(record);
                                if (outPage.size() == pageSize)
                                    return outPage;
                            }
                        } 
                        else if (operator_ == "!=") {
                            if (record_val != compare_val) {
                                outPage.push_back(record);
                                if (outPage.size() == pageSize)
                                    return outPage;
                            }
                        }
                    }
                } // End attr loop
            } // End of r loop
        }

        return outPage;
    }


    void close() {
      // Implement this
      input -> close();
    }
};

#endif
