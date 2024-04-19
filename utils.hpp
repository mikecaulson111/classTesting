#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

using namespace std;

typedef struct assignment_grade_t {
    string assignment_name;
    float grade;
    float weight;
} assignment_grade;

typedef struct subject_t {
    string name;
    float grade;
    vector<assignment_grade> grades;
} subject;

bool is_numb(std::string &s, bool is_float=false); 



#endif
