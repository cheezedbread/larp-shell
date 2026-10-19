#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "help.h"

using namespace std;

void cmd_cat(string input){
    bool err = false;
    stringstream splicer(input);
    vector<string> requested_files;
    string splice_util = "";
    while (splicer >> splice_util) {
        requested_files.push_back(splice_util);
    }
    for (int i = 0; i < requested_files.size(); i++) {
        ifstream catfile(requested_files[i]);
        if (!catfile.is_open()) {
            cerr << "cat: file \"" << requested_files[i] << "\" does not exist." << endl;
            err = true;
        }
        if (err == false) {
            char ch = '\0';
            while (catfile.get(ch)) {
                cout << ch;
            }
        }
        err = false;
        catfile.close();
    }
}
