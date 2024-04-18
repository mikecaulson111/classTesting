#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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

void saver(classroom *classroom, string s) {
    fstream fout;

    fout.open(s, ios::out | ios::app);

    for (int i = 0; i < classroom->get_num_students(); i++) {
        // cout << classroom->get_person(i)->fname << endl;
        person *p = classroom->get_person(i);
        fout << p->lname << "," << p->fname << "," << p->age << "," << p->is_male << "," << p->avg << ",";
        fout << p->subjects.size() << ",";
        for (subject sub : p->subjects) {
            fout << sub.name << ",";
            fout << sub.grades.size() << ",";
            for (assignment_grade ass : sub.grades) {
                fout << ass.assignment_name << "," << ass.grade << ",";
            }
        }
        fout << '\n';
    }

    fout.close();
}

void loader(classroom *classroom, string s) {
    fstream fin;
    fin.open(s, ios::in);

    vector<string> row;
    string temp, line, word;
    while (getline(fin, temp)) {
        row.clear();
        stringstream s(temp);
        while(getline(s,word,',')) {
            row.push_back(word);
        }

        person p;
        p.fname = row.at(1);
        p.lname = row.at(0);
        cout << row.at(2) << endl;
        p.age = stoi(row.at(2));
        p.is_male = bool(stoi(row.at(3)));
        p.avg = stof(row.at(4));
        int sub_size = stoi(row.at(5));
        int overall = 6;
        for (int i = 0; i < sub_size; i++) {
            subject s;
            s.name = row.at(overall);
            overall++;
            int ass_size = stoi(row.at(overall));
            overall++;
            for (int j = 0; j < ass_size; j++) {
                assignment_grade ass;
                ass.assignment_name = row.at(overall);
                overall++;
                ass.grade = stof(row.at(overall));
                overall++;
                s.grades.push_back(ass);
            }
            p.subjects.push_back(s);
        }

        classroom->add_student(&p);
    }

    fin.close();
}


int main(int argc, char* argv[]) {
    cout << "Hello world" << endl;
    classroom classroom1;
    
    // person *p1 = NULL;

    bool cont = true;
    string answer;

    while(cont) {
        cout << "Please Enter the number of what you would like to do:" << endl;
        cout << "[1] Add new student \n[2] Print list of students\n[3] Get number of students\n[4] Edit student\n[0] Quit\n" << endl;
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
            } else if (temp == 9) {
                string temp_str;
                cout << "Enter the name of the the file to write save to:" << endl;
                getline(cin, temp_str, '\n');
                saver(&classroom1, temp_str);
            } else if (temp == 8) {
                string temp_str;
                cout << "Enter the name of the file to read from:" << endl;
                getline(cin, temp_str, '\n');
                loader(&classroom1, temp_str);
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
