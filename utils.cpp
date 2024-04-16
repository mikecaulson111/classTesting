#include "utils.hpp"
#include <string>
#include <iostream>

using namespace std;


bool is_numb(string &s, bool is_float) {
    for(int i = 0; i < s.length(); i++) {
        if ((!is_float) && (s[i] > 57 || s[i] < 48)) {
            return false;
        } else if ((is_float && s[i] != '.') && (s[i] > 57 || s[i] < 48)) {
            return false;
        }
    }
    return true;
}
