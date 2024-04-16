#include "classroom.hpp"
#include "person.hpp"
#include "utils.hpp"


#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


float classroom::calculate_average() {
    float tot = 0;
    for(person p : this->students) {
        tot += p.avg;
    }

    tot = tot / this->num_students;

    this->class_avg = tot;
    return tot;
}

void classroom::change_dimensions(int l, int w, int h) {
    this->width = w;
    this->length = l;
    this->height = h;

    cout << "Successfully updated the dimensions of the classroom" << endl;
}

int classroom::get_num_students() {
    return this->num_students;
}

void classroom::add_student(person *p) {
    // cout << "why here" << endl;

    this->students.push_back(*p);
    this->num_students += 1;
    // cout << "size: " << students.size() << endl;
}

void print_assignments(person p, int show_nums=0) {
    cout << "\033[0;32m";
    cout << "\tSubjects:" << "\033[0m" << endl;
    int counter = 0;
    for (subject sub : p.subjects) {
        cout << "\t\t";
        if (show_nums == 1) {
            cout << "[" << "\033[0;31m" << counter << "\033[0m] ";
        }
        cout << sub.name << ":" << endl;
        int counter1 = 0;
        for (assignment_grade ass : sub.grades) {
            cout << "\t\t\t";
            if (show_nums == 2) {
                cout << "[\033[0;31m" << counter1 << "\033[0m] ";
            }
            cout << ass.assignment_name << " : " << ass.grade << endl;
            counter1++;
        }
        counter++;
    }
}

void classroom::print_students(bool show_nums) {
    cout << endl;
    if (show_nums) {
        cout << " [num] ";
    }
    cout << "   last name |     first name | age | sex | avg" << endl;
    if (show_nums) {
        cout << "-------";
    }
    cout << "-----------------------------------------------" << endl;
    int counter = 0;
    for(person p : this->students) {
        if (show_nums) {
            cout << "[";
            cout << std::setw(4) << "\033[0;31m" << counter << "\033[0m"; // look up ansi color codes
            cout << "] ";
            counter++;
        }
        cout << std::setw(12) << p.lname;
        cout << " | ";
        cout << std::setw(14) << p.fname;
        cout << " | ";
        cout << std::setw(3) << p.age;
        cout << " | ";
        cout << std::setw(3) << (p.is_male == true ? "M" : "F");
        cout << " | ";
        cout << std::setw(3) << p.avg << endl;

        if (p.subjects.size() > 0) {
            print_assignments(p);
        }
    }
    cout << endl;
}


void classroom::make_person() {
    person *p = NULL;

    p = new person;
    string temp;
    
    if (NULL != p) {
        cout << "Enter the first name of new student:" << endl;
        getline(cin, p->fname, '\n');
        cout << "Enter the last name of new student:" << endl;
        getline(cin,p->lname,'\n');
        cout << "Enter the age of new student:" << endl;
        getline(cin,temp,'\n');
        // Now I need to make the check is number here and if so then add it if not, skip I guess...?
        if (is_numb(temp)) {
            int age_ = stoi(temp);
            p->age = age_;
        } else {
            cout << "That was not a number, entering 0, if you would like to change go and edit person from menu" << endl;
        }
        temp = "";
        cout << "Is " << p->fname << " female (type f) or male (type m):" << endl;
        getline(cin,temp,'\n');
        if (temp[0] == 'm' || temp[0] == 'M') {
            p->is_male = 1;
        } else if (temp[0] == 'f' || temp[0] == 'F') {
            p->is_male = 0;
        } else {
            cout << "That was not one of the options, putting in as female for now, to change edit person from menu" << endl;
        }

        cout << "How many subjects would you like to add for this student?" << endl;
        getline(cin, temp, '\n');
        if (is_numb(temp)) {
            int num_subject = stoi(temp);
            for (int i = 0; i < num_subject; i++) {
                subject sub;
                cout << "Enter the name for subject " << i+1 << endl;
                getline(cin, temp, '\n');
                sub.name = temp;
                cout << "How many assignments are you going to input for " << sub.name << "?" << endl;
                getline(cin, temp, '\n');
                if (is_numb(temp)) {
                    int num_assignments = stoi(temp);
                    for (int j = 0; j < num_assignments; j++) {
                        assignment_grade assignment;
                        cout << "Please enter the name of the assignment:" << endl;
                        getline(cin, temp, '\n');
                        assignment.assignment_name = temp;
                        cout << "Please enter the grade received for " << assignment.assignment_name << " as a decimal:" << endl;
                        getline(cin, temp, '\n');
                        if (is_numb(temp, true)) {
                            assignment.grade = stof(temp);
                            sub.grades.push_back(assignment);
                        } else {
                            cout << "That was not a recognized number, not adding assignment, try again" << endl;
                        }
                    }
                    p->subjects.push_back(sub);
                } else {
                    cout << "That was not a correct number, not adding subject, you can add this from edit student in menu" << endl;
                }
            }
        } else {
            cout << "Please only enter a number, entering no subjects for now, if you wish to change this edit student from the menu" << endl;
        }


        this->add_student(p);

    }

    free(p);
    p = NULL;
}

person *classroom::get_person(int place) {
    person *p = NULL;

    if (place < get_num_students()) {
        p = &this->students.at(place);
    }
    return p;
}

void edit_subject(person *p) {
    cout << "Editing Subject or Assignment" << endl;
    print_assignments(*p, 1);
}

void classroom::edit_student() {
    string temp;
    person *p = NULL;
    int person_num;
    int choice;

    print_students(true);
    cout << "Plese enter the number of the student you would like to edit:" << endl;
    getline(cin, temp,'\n');
    if(is_numb(temp)) {
        person_num = stoi(temp);
        if (person_num < get_num_students()) {
            p = get_person(person_num);
            cout << "Editing for " << p->fname << " " << p->lname << endl;
            cout << "Enter the number of what you would like to edit:\n[1] First Name\n[2] Last Name\n[3] Age\n[4] Sex\n[5] Subject/Assignment\n" << endl;
            getline(cin, temp, '\n');
            if (is_numb(temp)) {
                choice = stoi(temp);

                switch (choice) {
                    case 1:
                        cout << "Enter the new first name: ";
                        getline(cin, temp, '\n');
                        p->fname = temp;
                        break;
                    case 2:
                        cout << "Enter the new last name: ";
                        getline(cin, temp, '\n');
                        p->lname = temp;
                        break;
                    case 3:
                        cout << "Enter the new age: ";
                        getline(cin, temp, '\n');
                        if (is_numb(temp)) {
                            p->age = stoi(temp);
                        } else {
                            cout << "Please only enter a number next time." << endl;
                        }
                        break;
                    case 4:
                        cout << "Switching the sex ... completed" << endl;
                        p->is_male = !p->is_male;
                        break;
                    case 5:
                        edit_subject(p);
                        break;
                    default:
                        cout << "Please only enter a number between 1 and 4" << endl;
                }
                cout << "\n" << endl;
            } else {
                cout << "Please only enter a number for between 1 and 4" << endl;
            }

        } else {
            cout << "Please only enter the number of a student in the list\n" << endl;
        }
    } else {
        cout << "Please only enter a number, no letters\n" << endl;
    }

    // free(p);
    // p = NULL;
}
