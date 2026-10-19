#include <iostream>
#include <fstream>
#include "help.h"

using namespace std;

void cmd_help(){
    cout << "LarpOS Commands:" << endl;
    cout << "   help ------------ Shows list of commands" << endl;
    cout << "   echo ------------ Prints current input" << endl;
    cout << "   betterecho ------ Echo, but with some basic styling" << endl;
    cout << "   man ------------- Shows help on commands" << endl;
    cout << "   cat ------------- Concatenates text files" << endl;
    cout << "   clear ----------- Clears the terminal" << endl;
    cout << "   exit ------------ Exits LarpOS" << endl;
}

void cmd_man(string input){
    bool err = false;
    ifstream manfile("man/" + input + ".txt");
    if (!manfile.is_open()) {
        cout << "man: command does not have man page available." << endl;
        err = true;
    }
    if (err == false) {
        char ch = '\0';
        while (manfile.get(ch)) {
            cout << ch;
        }
    }
    manfile.close();
}
