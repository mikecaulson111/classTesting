#include <iostream>
#include <vector>

#include "classroom.hpp"
#include "person.hpp"
#include "utils.hpp"

using namespace std;


// bool is_number(string &s) {
//     // return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
//     for(int i = 0; i < s.length(); i++) {
//         if (s[i] > 57 || s[i] < 48) {
//             return false;
//         }
//     }
//     return true;
// }

int main(int argc, char* argv[]) {
    cout << "Hello world" << endl;
    classroom classroom1;
    
    // person *p1 = NULL;

    bool cont = true;
    string answer;

    while(cont) {
        cout << "Please Enter the number of what you would like to do:" << endl;
        cout << "[1] Add new student \n[2] Print list of students\n[3] Get number of students\n[4] Edit student" << endl;
        getline(cin, answer, '\n');
        // cout << answer << endl;
        int temp;
        if (is_numb(answer)) {
            temp = stoi(answer);

            if (temp == 1) {
                classroom1.make_person();
            } else if (temp == 2) {
                classroom1.print_students(false);
            } else if (temp == 3) {
                cout << "There are currently: " << classroom1.get_num_students() << " students in this class." << endl;
            } else if (temp == 4) {
                classroom1.edit_student();
            } else if (temp == 0) {
                cont = false;
            }
        } else {
            cout << "Please only enter a number" << endl;
        }

    }

    // p1 = new person;
    // p1->fname = "Michael";
    // p1->lname = "Caulson";
    // p1->age = 14;
    // p1->is_male = true;
    // p1->avg = 0.5;

    // cout << p1->fname << endl;

    // classroom1.add_student(p1);

    // free(p1);
    // p1 = NULL;

    // p1 = new person;
    // p1->fname = "Mia";
    // p1->lname = "Kilkenny";
    // p1->age = 16;
    // p1->is_male = false;
    // p1->avg = 0.99;


    // classroom1.add_student(p1);

    // classroom1.print_students();

    // free(p1);
    // p1 = NULL;

    // p1 = make_person();

    // free(p1);
    // p1 = NULL;

}
