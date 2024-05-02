#include "classroom.hpp"
#include "person.hpp"
#include "utils.hpp"


#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

#define RED "\033[0;31m"
#define NORMAL "\033[0m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"

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

float calculate_student_average(person *p) {
    float total = 0.0;
    float count = 0;
    float class_count = 0;
    if (p->subjects.size() > 0) {
        for (subject sub : p->subjects) {
            float temp_tot = 0;
            for(assignment_grade ass : sub.grades) {
                temp_tot += (ass.grade * (ass.weight / 100.));
            }
            p->subjects.at(class_count).grade = temp_tot;
            total += temp_tot;
            class_count++;
        }
        total /= class_count;
    }

    if (p->subjects.size() > 0 && total == 0.0) {
        for (subject sub : p->subjects) {
            for (assignment_grade ass : sub.grades) {
                total += ass.grade;
                count++;
            }
        }
        total /= count;
    }

    return total;
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
    p->avg = calculate_student_average(p);

    this->students.push_back(*p);
    this->num_students += 1;
}

void print_assignments(person p, int show_nums=0, int sub_num=-1, int just_subjects=-1) {
    cout << "\033[0;32m";
    cout << "\tSubjects:" << "\033[0m" << endl;
    int counter = 0;
    for (subject sub : p.subjects) {
        cout << "\t\t";
        if (show_nums == 1) {
            //cout << "[" << "\033[0;31m" << counter << "\033[0m] ";
            cout << "[" << RED << counter << "\033[0m] ";
        }
        cout << sub.name << " (" << (sub.grade >= 80 ? GREEN : (sub.grade >= 60 ? YELLOW : RED)) << sub.grade << NORMAL << ")" << ":" << endl;
        int counter1 = 0;
        for (assignment_grade ass : sub.grades) {
            cout << "\t\t\t";
            if (show_nums == 2 && sub_num != -1) {
                if (counter == sub_num) {
                    cout << "[\033[0;31m" << counter1 << "\033[0m] ";
                }
            }
            cout << ass.assignment_name << " : " << (ass.grade >= 80 ? GREEN : (ass.grade >= 60 ? YELLOW : RED)) << ass.grade << NORMAL << "(" << ass.weight << "%)" << endl;
            counter1++;
        }
        counter++;
    }
    // cout << "\033[0;32m";
    // cout << "\tSubjects:" << "\033[0m" << endl;
    // int counter = 0;
    // for (int i = 0; i < p.subjects.size(); i++) {
    //     subject sub = p.subjects.at(i);
    //     cout << "\t\t";
    //     if (show_nums == 1) {
    //         //cout << "[" << "\033[0;31m" << counter << "\033[0m] ";
    //         cout << "[" << RED << counter << "\033[0m] ";
    //     }
    //     cout << sub.name << " (" << (sub.grade >= 80 ? GREEN : (sub.grade >= 60 ? YELLOW : RED)) << sub.grade << NORMAL << ")" << ":" << endl;
    //     int counter1 = 0;
    //     if (-2 == just_subjects || i == just_subjects) {
    //         for (int j = 0; j < sub.grades.size(); j++) {
    //             assignment_grade ass = sub.grades.at(j);
    //             cout << "\t\t\t";
    //             if (show_nums == 2 && sub_num != -1) {
    //                 if (counter == sub_num) {
    //                     cout << "[\033[0;31m" << counter1 << "\033[0m] ";
    //                 }
    //             }
    //             cout << ass.assignment_name << " : " << (ass.grade >= 80 ? GREEN : (ass.grade >= 60 ? YELLOW : RED)) << ass.grade << NORMAL << "(" << ass.weight << "%)" << endl;
    //             counter1++;
    //         }
    //     }
    //     counter++;
    // }
}

void classroom::print_students(bool show_nums, bool show_assignments) {
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

        if (show_assignments && p.subjects.size() > 0) {
            print_assignments(p);
        }
    }
    cout << endl;
}

void add_assignments(subject *s, int num_assignments) {
    string temp;
    for (int j = 0; j < num_assignments; j++) {
        assignment_grade assignment;
        cout << "Please enter the name of the assignment:" << endl;
        getline(cin, temp, '\n');
        assignment.assignment_name = temp;
        cout << "Please enter the grade received for " << assignment.assignment_name << " as a decimal:" << endl;
        getline(cin, temp, '\n');
        if (is_numb(temp, true)) {
            assignment.grade = stof(temp);
            cout << "Please enter the weight for the assignment(as a percentage):" << endl;
            getline(cin, temp, '\n');
            if ( is_numb(temp,true)) {
                assignment.weight = stof(temp);
            } else {
                cout << "Weight was not entered correctly, entering 0" << endl;
                assignment.weight = 0;
            }
            s->grades.push_back(assignment);
        } else {
            cout << "That was not a recognized number, not adding assignment, try again" << endl;
        }
        
    }
}

void add_subjects(person *p, int num_subjects) {
    string temp;
    for (int i = 0; i < num_subjects; i++) {
        subject sub;
        cout << "Enter the name for subject " << i+1 << endl;
        getline(cin, temp, '\n');
        sub.name = temp;
        cout << "How many assignments are you going to input for " << sub.name << "?" << endl;
        getline(cin, temp, '\n');
        if (is_numb(temp)) {
            int num_assignments = stoi(temp);
            add_assignments(&sub, num_assignments);
            p->subjects.push_back(sub);
        } else {
            cout << "That was not a correct number, not adding subject, you can add this from edit student in menu" << endl;
        }
    }
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
            int num_subjects = stoi(temp);
            add_subjects(p, num_subjects);
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
    string temp;
    cout << "Editing Subject or Assignment" << endl;
    cout << "Please select one of the following:\n[0] Edit Subject/Assignment\n[1] Add/Remove Subject" << endl;
    getline(cin, temp, '\n');
    if (is_numb(temp)) {
        if (stoi(temp) == 0) {
            print_assignments(*p, 1);
            cout << "Choose the number of the subject shown above that you wish to edit:" << endl;
            getline(cin, temp, '\n');
            if (is_numb(temp)) {
                int place = stoi(temp);
                if (place < p->subjects.size()) {
                    subject *sub = &p->subjects.at(place);
                    cout << "Please enter\n[0] If you want to edit the name of the subject\n[1] If you wish to edit one of the assignments\n[2] To add/remove assignment" << endl;
                    getline(cin, temp, '\n');
                    if (is_numb(temp)) {
                        if (stoi(temp) == 0) {
                            cout << "Please enter the name for the subject:" << endl;
                            getline(cin, temp, '\n');
                            sub->name = temp;
                        } else if (stoi(temp) == 1) {
                            print_assignments(*p, 2, place);
                            cout << "Please enter the number of the assignment from above you wish to edit:" << endl;
                            getline(cin, temp, '\n');
                            if (is_numb(temp)) {
                                int place1 = stoi(temp);
                                if (place1 < sub->grades.size()) {
                                    cout << "Please enter [0] if you wish to change the name of the assignment, [1] if you wish to change the grade, or [2] if you wish to change the weight:" << endl;
                                    getline(cin, temp, '\n');
                                    if (is_numb(temp)) {
                                        if (stoi(temp) == 0) {
                                            cout << "Enter the name for the assignment:" << endl;
                                            getline(cin,temp,'\n');
                                            sub->grades.at(place1).assignment_name = temp;
                                        } else if (stoi(temp) == 1) {
                                            cout << "Enter the grade:" << endl;
                                            getline(cin,temp,'\n');
                                            if(is_numb(temp, true)) {
                                                sub->grades.at(place1).grade = stof(temp);
                                                p->avg = calculate_student_average(p);
                                            } else {
                                                cout << "Please only enter a number for the grade, try again" << endl;
                                            }
                                        } else if (stoi(temp) == 2) {
                                            cout << "Enter the weight:" << endl;
                                            getline(cin, temp, '\n');
                                            if (is_numb(temp,true)) {
                                                sub->grades.at(place1).weight = stof(temp);
                                                p->avg = calculate_student_average(p);
                                            } else {
                                                cout << "Please only enter a number for the weight" << endl;
                                            }
                                        } else {
                                            cout << "Please only enter a number between 0 and 1, try again" << endl;
                                        }
                                    } else {
                                        cout << "Please only enter a number for the assignment, try again" << endl;
                                    }
                                } else {
                                    cout << "Please only enter a number that is displayed on the screen, try again" << endl;
                                }
                            } else {
                                cout << "Please enter a number for the assignment, try again" << endl;
                            }
                        } else if (stoi(temp) == 2) {
                            cout << "Please choose one of the following:\n[0] Add Assignment\n[1] Remove Assignment\n" << endl;
                            getline(cin, temp, '\n');
                            if (is_numb(temp)) {
                                if (stoi(temp) == 0) {
                                    // do the addition here
                                    cout << "How many assignments would you like to add to " << sub->name << endl;
                                    getline(cin, temp, '\n');
                                    if (is_numb(temp)) {
                                        add_assignments(sub, stoi(temp));
                                    } else {
                                        cout << "Please only enter a number for this" << endl;
                                    }
                                } else if (stoi(temp) == 1) {
                                    // do the removal here
                                    print_assignments(*p, 2, place);
                                    cout << "Please enter the number of the assignment you would like to remove from above" << endl;
                                    getline(cin, temp, '\n');
                                    if (is_numb(temp)) {
                                        if (stoi(temp) < sub->grades.size()) {
                                            sub->grades.erase(sub->grades.begin() + stoi(temp));
                                        } else {
                                            cout << "Please only enter a number that is on the screen" << endl;
                                        }
                                    } else {
                                        cout << "Please only enter a number, try again" << endl;
                                    }
                                } else {
                                    cout << "Please only enter a number shown on screen (0, 1)" << endl;
                                }
                            } else {
                                cout << "Please only enter a number next time" << endl;
                            }
                        } else {
                            cout << "Please only enter a number between 0 and 1, try again" << endl;
                        }
                    } else {
                        cout << "Please only enter a number for the subject, try again" << endl;
                    }
                } else {
                    cout << "Please only enter a number that is displayed on the screen, try again" << endl;
                }
            } else {
                cout << "Please only enter a number for the subject, try again" << endl;
            }
        } else if (stoi(temp) == 1) {
            // Add/remove the subject
            cout << "Please choose one of the following:\n[0] Add Subject\n[1] Remove Subject\n" << endl;
            getline(cin, temp, '\n');
            if(is_numb(temp)) {
                if (stoi(temp) == 0) {
                    // add subject
                    cout << "How many subjects would you like to add at this time:" << endl;
                    getline(cin, temp, '\n');
                    if (is_numb(temp)) {
                        add_subjects(p, stoi(temp));
                        p->avg = calculate_student_average(p);
                    } else {
                        cout << "Please only enter a number for this amount" << endl;
                    }
                } else if (stoi(temp) == 1) {
                    // remove subject
                    print_assignments(*p, 1);
                    cout << "Please enter the number of the subject you would like to remove:" << endl;
                    getline(cin, temp, '\n');
                    if (is_numb(temp)) {
                        int place2 = stoi(temp);
                        if (place2 < p->subjects.size()) {
                            cout << "CONFIRM: Are you sure you wish to remove " << p->subjects.at(place2).name << " and all of the assignments under it permanently?" << endl;
                            cout << "[0] NO" << endl;
                            cout << "[1] YES" << endl;
                            getline(cin, temp, '\n');
                            if(is_numb(temp)) {
                                if (stoi(temp) == 1) {
                                    // remove
                                    p->subjects.at(place2).name = "";
                                    p->subjects.at(place2).grade = 0.0;
                                    p->subjects.at(place2).grades.clear();
                                    p->subjects.erase(p->subjects.begin() + place2);
                                    cout << "Removed subject" << endl;
                                    p->avg = calculate_student_average(p);
                                } else {
                                    cout << "Ok aborting removal" << endl;
                                }
                            } else {
                                cout << "Please only enter a number" << endl;
                            }
                        } else {
                            cout << "Please only enter a number shown on the screen for the subject" << endl;
                        }
                    } else {
                        cout << "Please only enter a number" << endl;
                    }
                } else {
                    cout << "Please only enter one of the numbers shown on the screen" << endl;
                }
            } else {
                cout << "Please only enter a number" << endl;
            }
        } else {
            cout << "Please only enter one of the numbers shown on the screen" << endl;
        }
    } else {
        cout << "Please only enter a number" << endl;
    }
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
            print_students(false, true);
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
                        cout << "Please only enter a number between 1 and 5" << endl;
                }
                cout << "\n" << endl;
            } else {
                cout << "Please only enter a number for between 1 and 5" << endl;
            }

        } else {
            cout << "Please only enter the number of a student in the list\n" << endl;
        }
    } else {
        cout << "Please only enter a number, no letters\n" << endl;
    }
}

void classroom::print_student_subjects() {
    string temp;
    person *p = NULL;
    print_students(true);
    cout << "Please enter the number of the student you would like to see the subjects and assignments for:" << endl;
    getline(cin, temp, '\n');
    if (is_numb(temp)) {
        p = get_person(stoi(temp));
        cout << "Subject Information for: " << p->fname << " " << p->lname << ":" << endl;
        print_assignments(*p);
    } else {
        cout << "Please only enter a number for the student" <<  endl;
    }
}
