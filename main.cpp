#include <iostream>
#include <cstdlib> // needed for system()
#include <string> // needed for to_string()
#include <sstream> // needed for stringstream
#include <map> // needed for maps
#include <vector> // god help us all
#include "help.h"
#include "files.h"

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
    cout << "\033[22m"; //disable bold
    cout << "\033[24m"; //disable underline
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

void quickStyle(string inputColor, bool bold, bool underline) {
    /*
        for developers:
        please use quickstyle instead of manually using setstyle to make LarpOS consistent in its color scheme
        the following list describes available colors along with their red, green and blue values, in that order.
            - red: 255,85,85
            - green: 80,250,123
            - yellow: 241,250,140
            - purple: 187,149,249
            - pink: 255,121,198
            - blue: 139,233,253
            - white: 255,255,255
        ------------------------------------------------------------------------
        colors are taken from https://terminalcolors.com/themes/dracula/default/
    */
    int r = 0;
    int g = 0;
    int b = 0;
    map <string, int> red = {
        {"red",255},
        {"green",80},
        {"yellow",241},
        {"purple",187},
        {"pink",255},
        {"blue",139},
        {"white",255}
    };
    map <string, int> green = {
        {"red",85},
        {"green",250},
        {"yellow",250},
        {"purple",149},
        {"pink",121},
        {"blue",233},
        {"white",255}
    };
    map <string, int> blue = {
        {"red",85},
        {"green",123},
        {"yellow",140},
        {"purple",249},
        {"pink",198},
        {"blue",253},
        {"white",255}
    };
    if (red.find(inputColor) == red.end()) {
        cerr << "quickstyle: err: color not defined in list of available colors (red, green, yellow, purple, pink, blue, white)" << endl;
    }
    else {
        r = red[inputColor];
        g = green[inputColor];
        b = blue[inputColor];
        setStyle(r,g,b,bold,underline);
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
        if (check_input[0] == '-') {
            if ((check_input[1] != 'b' && check_input[1] != 'u') && check_input[1] != 'c') {
                if (i == exceptions_hit) {
                    output = output + whole[i];
                }
                else {
                    output = output + " " + whole[i];
                }
                written = true;
            }
            else if (check_input.size() == 3){
                if (check_input[1] == 'b' || check_input[2] == 'b') {
                    setBold = true;
                }
                if (check_input[1] == 'u' || check_input[2] == 'u') {
                    setLine = true;
                }
            }
            else if (check_input.size() == 2){
                if (check_input[1] == 'b') {
                    setBold = true;
                }
                else if (check_input[1] == 'u') {
                    setLine = true;
                }
                else if (check_input[1] == 'c') {
                    setColor = true;
                    colorToken = i; //from here, make another loop that takes input starting at token, get the next 3 tokens as r, g and b and then use setstyle
                }
            }
        }
        if (setColor == true) {
            if (i == (colorToken + 1) || i == (colorToken + 2)) {
                //do nothing
            }
            else if (i == (colorToken + 3) || i == colorToken) {
                //do nothing
            }
            else {
                if (i == (colorToken + 4)) {
                    output = output + whole[i];
                }
                else {
                    output = output + " " + whole[i];
                }
            }
        }
        else {
            if (whole[i] == "-b" || whole[i] == "-u" || whole[i] == "-c"){
                //do nothing
                exception = true;
            }
            else if (whole[i] == "-bu" || whole[i] == "-ub"){
                //do nothing
                exception = true;
            }
            if (i == 0 && exception == false && written == false) {
                output = output + whole[i];
                written = true;
            }
            else if (i == exceptions_hit && exception == false && written == false) {
                output = output + whole[i];
                written = true;
            }
            if (exception == false && written == false){
                output = output + " " + whole[i];
            }
            else if (exception == true){
                //do nothing
                exceptions_hit++;
            }
        }
    }
    int color_values[4] = {0,255,255,255};
    if (setColor == true) {
        for (int i = 1; i < 4; i++) {
            color_values[i] = stoi(whole[colorToken + i]);
        }
    }
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
            {"betterecho", cmd_betterecho},
            {"man", cmd_man},
            {"cat", cmd_cat}
        };
        map<string, void (*)()> lonley_commands = { //ignore my last comment i think i understand it now
            {"clear", clearScreen},
            {"help", cmd_help}
        };

        bool found_cmd = false;
        if (commands.find(command[0]) == commands.end() && lonley_commands.find(command[0]) == lonley_commands.end()) {
            cerr << "lsh: command not found: " << command[0] << endl;
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
    quickStyle("white",false,false);
    cout << R"( ______________________  _________________ )" << endl;
    cout << R"(|  _                   ||    ___  ____    |   larper@larp)" << endl;
    cout << R"(| | | __ _ _ __ _ __   ||   / _ \/ ___|   |   -----------)" << endl;
    cout << R"(| | |/ _` | '__| '_ \  ||  | | | \___ \   |   OS: LarpOS 1.2.1 x64_86)" << endl;
    cout << R"(| | | (_| | |  | |_) | ||  | |_| |___) |  |   Commands: 6 (built-in))" << endl;
    cout << R"(| |_|\__,_|_|  | .__/  ||   \___/|____/   |   Shell: lsh)" << endl;
    cout << R"(| -------------|_|---- ||  -------------  |   Terminal: Larp-Terminal)" << endl;
    cout << R"(|______________________||_________________|   -----------)" << endl;
    resetStyle();
}

int main(){
    bool first_run = true;
    string user_input = "";
    while (true) {
        if (first_run == true) {
            resetStyle();
            welcomeScreen();
            first_run = false;
            cout << endl;
            quickStyle("white",true,false);
            cout << "           Welcome to LarpOS v1.2.1 on Larp Linux v1.0.0!" << endl;
        }
        quickStyle("green",false,false);
        cout << "/";
        quickStyle("white",false,false);
        cout << "> ";
        getline(cin,user_input);
        if (user_input == "exit") {
            cout << "[exit]" << endl;
            break;
        }
        detect_cmd(user_input);
    }
    return 0;
}
