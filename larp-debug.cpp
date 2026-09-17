#include <iostream>
#include <cstdlib> // needed for system()
#include <string> // needed for to_string()
#include <sstream> // needed for stringstream
#include <map> // needed for maps
#include <vector> // god help us all

using namespace std; // it's so over

//begin ai slop
void clearScreen() {
#ifdef _WIN32
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#else
    cout << "Clear screen not supported on this OS" << endl;
#endif
}
//end ai slop

void setStyle(int r, int g, int b, bool bold, bool underline) {
    if (bold == false && underline == false) {
        cout << "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
    }
    else if (bold == true && underline == false) {
        cout << "\033[1;38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
    }
    else if (bold == false && underline == true) {
        cout << "\033[4;38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
    }
    else {
        cout << "\033[1;4;38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
    }
}

void resetStyle() {
    cout << "\033[0m";
}

void cmd_echo(string input) {
    cout << input << endl;
}

void cmd_betterecho(string input) {
    stringstream splicer(input);
    vector<string> whole;
    string splice_util = "";
    while (splicer >> splice_util) {
        whole.push_back(splice_util);
    }
    string check_input = "";
    string output = "";
    bool setBold = false;
    bool setLine = false;
    bool setColor = false;
    bool dash = false;
    int colorToken = 0;
    int exceptions_hit = 0;
    bool exception = false;
    bool written = false;
    for (int i = 0; i < whole.size(); i++) {
        check_input = whole[i];
        exception = false;
        written = false;
        dash = false;
        cout << endl << "==================debug time!!==================" << endl;
        cout << "--------loop at loop " << i << " --------" << endl;
        cout << "whole at " << i << " is: " << whole[i] << endl;
        cout << "check for dash..." << endl;
        if (check_input[0] == '-') {
            cout << "check_input has dash, proceeding with check for flags..." << endl;
            if ((check_input[1] != 'b' && check_input[1] != 'u') && check_input[1] != 'c') {
                cout << "flags NOT found! will be adding to output current whole[" << i << "]" << endl;
                if (i == exceptions_hit) {
                    output = output + whole[i];
                }
                else {
                    output = output + " " + whole[i];
                }
                cout << "current output:" << output << endl;
                written = true;
            }
            else if (check_input.size() == 3){
                cout << "flags found!" << endl;
                cout << "flag size 3! checking WHICH flag in particular..." << endl;
                if (check_input[1] == 'b' || check_input[2] == 'b') {
                    cout << "flag 'b' found! setting setBold to true..." << endl;
                    setBold = true;
                }
                if (check_input[1] == 'u' || check_input[2] == 'u') {
                    cout << "flag 'u' found! setting setLine to true..." << endl;
                    setLine = true;
                }
            }
            else if (check_input.size() == 2){
                cout << "flags found!" << endl;
                cout << "flag size 2! checking WHICH flag in particular..." << endl;
                if (check_input[1] == 'b') {
                    cout << "flag 'b' found! setting setBold to true..." << endl;
                    setBold = true;
                }
                else if (check_input[1] == 'u') {
                    cout << "flag 'u' found! setting setLine to true..." << endl;
                    setLine = true;
                }
                else if (check_input[1] == 'c') {
                    cout << "flag 'c' found! setting setColor to true..." << endl;
                    setColor = true;
                    cout << "colorToken set to " << i << "." << endl;
                    colorToken = i; //from here, make another loop that takes input starting at token, get the next 3 tokens as r, g and b and then use setstyle
                }
            }
        }
        cout << "finished checking for dash. now proceeding with writing to output if needed." << endl;
        if (setColor == true) {
            cout << "setColor detected as true! special case..." << endl;
            if (i == (colorToken + 1) || i == (colorToken + 2)) {
                //do nothing
                cout << "colorToken: " << colorToken << endl;
                cout << "i = " << i << endl;
                cout << "if i == colorToken + 1/2, do nothing." << endl;
                cout << "current output:" << output << endl;
            }
            else if (i == (colorToken + 3) || i == colorToken) {
                //do nothing
                cout << "colorToken: " << colorToken << endl;
                cout << "i = " << i << endl;
                cout << "if i == colorToken + 3/colortoken, do nothing." << endl;
                cout << "current output:" << output << endl;
            }
            else {
                cout << "i is not colortoken + 1/2/3, adding the following to output:" << whole[i] << endl;
                if (i == (colorToken + 4)) {
                    output = output + whole[i];
                }
                else {
                    output = output + " " + whole[i];
                }
                cout << "current output:" << output << endl;
            }
        }
        else {
            cout << "standard writing to output: " << whole[i] << endl;
            if (whole[i] == "-b" || whole[i] == "-u" || whole[i] == "-c"){
                //do nothing
                cout << "exception CAUGHT! flag was about to be written to output" << endl;
                exception = true;
            }
            else if (whole[i] == "-bu" || whole[i] == "-ub"){
                cout << "exception CAUGHT! flag was about to be written to output" << endl;
                exception = true;
            }
            if (i == 0 && exception == false && written == false) {
                cout << "exception CAUGHT! current loop states i==0, avoiding leading spaces..." << endl;
                output = output + whole[i];
                written = true;
            }
            else if (i == exceptions_hit && exception == false && written == false) {
                cout << "exception CAUGHT! i = exceptions hit so same as i==0, avoid leading spaces..." << endl;
                output = output + whole[i];
                written = true;
            }
            if (exception == false && written == false){
                cout << "default write to output..." << endl;
                output = output + " " + whole[i];
            }
            else if (exception == true){
                //do nothing
                cout << "did nothing." << endl;
                exceptions_hit++;
                cout << "current exceptions hit:" << exceptions_hit << endl;
            }
            cout << "current output:" << output << endl;
        }
    }
    cout << "--------exiting from loop--------" << endl;
    int color_values[4] = {0,255,255,255};
    cout << "current color_values:";
    for (int i = 0; i < 4; i++) {
        cout << color_values[i] << ",";
    }
    cout << "." << endl;
    if (setColor == true) {
        cout << "setColor is true! initiating writing new color values..." << endl;
        for (int i = 1; i < 4; i++) {
            cout << "writing " << whole[colorToken + i] << " to " << i << " of color_values array" << endl;
            color_values[i] = stoi(whole[colorToken + i]);
        }
    }
    cout << "current color_values:";
    for (int i = 0; i < 4; i++) {
        cout << color_values[i] << ",";
    }
    cout << "." << endl;
    cout << "setBold: " << setBold << " setLine: " << setLine << endl;
    cout << "output:" << output << endl;
    cout << "applying style and output..." << endl;
    cout << "==================end debug!!==================" << endl;
    setStyle(color_values[1],color_values[2],color_values[3],setBold,setLine); //the actual settings
    cout << output << endl;
    resetStyle();
}

void detect_cmd(string input) {
    bool lonley_command = true;
    bool input_empty = false;
    stringstream splitter(input);
    vector<string> command;
    string split_util = "";
    string send_echo = "";
    while (splitter >> split_util) {
        command.push_back(split_util);
    }
    if (command.size() > 1) {
        send_echo = command[1];
        for (int i = 2; i < command.size(); i++) {
                send_echo = send_echo + " " + command[i]; //send_echo is a relic of olden times where i decided to hardcode commands to detect_cmd
        }
    }
    else if (command.size() == 0) {
        input_empty = true;
    }
    if (input_empty == false) {
        string command_input = command[0];
        void (*cmdpoint)(string);
        void (*lonleycmdpoint)();
        map<string, void (*)(string)> commands = { //what the fuck is a void (*)(string)
            {"echo", cmd_echo},
            {"betterecho", cmd_betterecho}
        };
        map<string, void (*)()> lonley_commands = { //ignore my last comment i think i understand it now
            {"clear", clearScreen}
        };

        bool found_cmd = false;
        if (commands.find(command[0]) == commands.end() && lonley_commands.find(command[0]) == lonley_commands.end()) {
            cout << "lsh: command not found: " << input << endl;
        }
        else {
            found_cmd = true;
        }
        if (commands.find(command[0]) != commands.end() && found_cmd == true) {
            lonley_command = false;
        }
        if (lonley_command == false && found_cmd == true) {
            cmdpoint = commands[command[0]];
            cmdpoint(send_echo);
        }
        else if (found_cmd == true){
            lonleycmdpoint = lonley_commands[command[0]];
            lonleycmdpoint();
        }
    }
}

void welcomeScreen(){
    cout << R"( ______________________  _________________ )" << endl;
    cout << R"(|  _                   ||    ___  ____    |   larper@larp)" << endl;
    cout << R"(| | | __ _ _ __ _ __   ||   / _ \/ ___|   |   -----------)" << endl;
    cout << R"(| | |/ _` | '__| '_ \  ||  | | | \___ \   |   OS: LarpOS 1.0 x64_86)" << endl;
    cout << R"(| | | (_| | |  | |_) | ||  | |_| |___) |  |   Commands: 3 (built-in))" << endl;
    cout << R"(| |_|\__,_|_|  | .__/  ||   \___/|____/   |   Shell: lsh)" << endl;
    cout << R"(| -------------|_|---- ||  -------------  |   Terminal: Larp-Terminal)" << endl;
    cout << R"(|______________________||_________________|   -----------)" << endl;
}

int main(){
    bool in_console = true;
    bool first_run = true;
    string user_input = "";
    while (in_console == true) {
        if (first_run == true) {
            resetStyle();
            welcomeScreen();
            first_run = false;
            cout << endl;
            cout << "> Welcome to LarpOS v1.0.0 with Larp kernel v1.0.0!" << endl;
        }
        cout << "> ";
        getline(cin,user_input);
        if (user_input == "exit") {
            cout << "exit" << endl;
            break;
        }
        detect_cmd(user_input);
    }
    return 0;
}
