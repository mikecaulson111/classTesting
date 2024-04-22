#ifndef CLASSROOM_HPP
#define CLASSROOM_HPP

#include "person.hpp"

#include <vector>

using namespace std;


class classroom {
    private:
        int num_students;
        vector<person> students;
        int length;
        int width;
        int height;
        float class_avg;

    public:
        classroom() {
            num_students = 0;
            length = 0;
            width = 0;
            height = 0;
            class_avg = 0;
        }

        void add_student(person *p);
        void change_dimensions(int l, int w, int h);
        float calculate_average();
        void make_person();
        void edit_student();
        person *get_person(int place);

        void print_students(bool show_nums, bool show_assignments=false);
        void print_student_subjects();
        int get_num_students();

};


#endif
