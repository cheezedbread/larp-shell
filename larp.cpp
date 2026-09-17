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
    int exeptions_hit = 0;
    bool exeption = false;
    bool written = false;
    for (int i = 0; i < whole.size(); i++) {
        check_input = whole[i];
        exeption = false;
        written = false;
        dash = false;
        if (check_input[0] == '-') {
            if ((check_input[1] != 'b' && check_input[1] != 'u') && check_input[1] != 'c') {
                if (i == exeptions_hit) {
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
                exeption = true;
            }
            else if (whole[i] == "-bu" || whole[i] == "-ub"){
                //do nothing
                exeption = true;
            }
            if (i == 0 && exeption == false && written == false) {
                output = output + whole[i];
                written = true;
            }
            else if (i == exeptions_hit && exeption == false && written == false) {
                output = output + whole[i];
                written = true;
            }
            if (exeption == false && written == false){
                output = output + " " + whole[i];
            }
            else if (exeption == true){
                //do nothing
                exeptions_hit++;
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

