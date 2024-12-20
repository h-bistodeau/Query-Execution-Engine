# Query-Execution-Engine

This repository holds all files required to run a simple query execution engine capable of running Select, Project, and Join operations. It is programmed entirely in C++.

Files include are:
- Attribute.h
    - defines and creates a attribute object with 3 variables being Name, Type & Value.

- Record.h
   - Defines a Record object as a vector that can hold a arbitrary amount of attribute objects
   - Includes two member functions that add an attribute to the record, and the second iterates through the Record to find a specific attribute index. (used within the Join)
 
- FileReader.h
    - Opens/closes a file and reads in the data as pages of a designated size (Defined in the Operator class).
 
- Operator.h
    - Contains the protected page size variable

- Project.h
  - Prints (or projects) defined attributes to the screen, by reading in pages from a file or pulling them in from other operators.
  - EX.
        - Project op1("student.data", {"FirstName", "LastName"});
        - SQL; Select FirstName, Lastname From 'student.data'
 
- Select.h
  - Equivalent to SQL's 'Where', it takes in the file or another operators output as well as the attribute name and value, it uses this information to remove data that does not meet the given constraints.
  - EX.
        - Select op1("smallData/faculty.data", "dept_name","=","Comp. Sci.");
        - SQL: Select * From "smallData/faculty.data" Where dept_name = "Comp. Sci"

- Join.h
  - Able to perform Join functionality from 2 files, a file and previous operator, and two operators. This class has 3 different constructors based on the different data inputs stated previously. This class runs a simple equi-join where it checks for equality within the chosen attributes.
        - Join op1("smallData/instructor.data", "smallData/department.data", "I_dept_name","D_dept_name");
        - SQL: SELECT * FROM instructor JOIN department ON instructor.dept_name=department.dept_name
 


