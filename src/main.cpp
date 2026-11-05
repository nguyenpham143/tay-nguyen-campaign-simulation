/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2025
* Date: 07.02.2025
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "tay_nguyen_campaign.h"

using namespace std;

void tnc_tc_01(const string &input_file = "tests/tnc_tc_01_input") {
    cout << "----- Sample Testcase 01 -----" << endl;
    int LF1[17], LF2[17], EXP1, EXP2, T1, T2, E;
    if (!readFile(input_file, LF1, LF2, EXP1, EXP2, T1, T2, E)) {
        return;
    }

    cout << "LF1[0]: " << LF1[0] << ", LF2[0]: " << LF2[0] << endl;
    int result = gatherForces(LF1, LF2);
    cout << "Result: " << result << endl;
}

int main(int argc, const char * argv[]) {
    string input_file = (argc > 1) ? argv[1] : "tests/tnc_tc_01_input";
    tnc_tc_01(input_file);
    return 0;
}
