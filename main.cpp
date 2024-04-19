#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "classroom.hpp"
#include "person.hpp"
#include "utils.hpp"

using namespace std;


void saver(classroom *classroom, string s) {
    const char* path = "./saves";
    struct stat sb;
    if (stat(path, &sb) != 0) {
        mkdir("saves", 0777);
    }

    fstream fout;

    if (s.substr(s.length()-4, 4).compare(".csv") == 0) {
        fout.open("./saves/" + s, ios::out | ios::app);
    } else {
        fout.open("./saves/" + s + ".csv", ios::out | ios::app);
    }

    for (int i = 0; i < classroom->get_num_students(); i++) {
        person *p = classroom->get_person(i);
        fout << p->lname << "," << p->fname << "," << p->age << "," << p->is_male << "," << p->avg << ",";
        fout << p->subjects.size() << ",";
        for (subject sub : p->subjects) {
            fout << sub.name << ",";
            fout << sub.grades.size() << ",";
            for (assignment_grade ass : sub.grades) {
                fout << ass.assignment_name << "," << ass.grade << "," << ass.weight << ",";
            }
        }
        fout << '\n';
    }

    fout.close();
}

void loader(classroom *classroom, string s) {
    fstream fin;
    if (s.substr(s.length()-4, 4).compare(".csv") == 0) {
        fin.open("./saves/" + s, ios::in);
    } else {
        fin.open("./saves/" + s + ".csv", ios::in);
    }

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
                ass.weight = stof(row.at(overall));
                overall++;
                s.grades.push_back(ass);
            }
            p.subjects.push_back(s);
        }

        classroom->add_student(&p);
    }

    fin.close();
}

// void print_saves() {
//     string path = "./saves/";
// 
//     for(const auto & entry ; fs::directory_iterator(path)) {
//         cout << entry.path() << endl;
// }


int main(int argc, char* argv[]) {
    classroom classroom1;
    
    bool cont = true;
    string answer;

    while(cont) {
        cout << "Please Enter the number of what you would like to do:" << endl;
        cout << "[1] Add new student \n[2] Print list of students\n[3] Get number of students\n[4] Edit student\n";
        cout << "[8] Load file\n[9] Save current class to file\n";
        cout << "[0] Quit\n" << endl;
        getline(cin, answer, '\n');
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
                if (is_numb(temp_str) && 1 == stoi(temp_str)) {
                    // print_saves();
                    cout << "Listing saves is coming soon..." << endl;
                } else {
                    loader(&classroom1, temp_str);
                }
            } else if (temp == 0) {
                cont = false;
            }
        } else {
            cout << "Please only enter a number" << endl;
        }

    }

}
