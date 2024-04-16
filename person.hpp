#ifndef PERSON_HPP
#define PERSON_HPP

#include <vector>
#include <string>
#include "utils.hpp"

using namespace std;

typedef struct person_s {
    string fname;
    string lname;
    int age;
    int grade;
    bool is_male;
    float avg;
    // vector<float> grades;
    vector<subject> subjects;
} person;

#endif
