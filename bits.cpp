#include "bits.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

void convert_to_binary(void*, string&, size_t);

int main() {
    int64_t inputtedNum;

    cout << "Please input a number: " << flush;
    cin >> inputtedNum;
    char c;
    //while ((c = getchar()) != '\n' && c != EOF);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear the input buffer

    string bits = "";
    convert_to_binary(&inputtedNum, bits, sizeof(int64_t));
    cout << "The value in binary is " << bits << endl;
    for(;;) {
        string command;

        cout << "Bit CLI> " << flush;
        getline(cin, command);
        //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // getline does NOT consume the newline character, so we must clear the input buffer

        if (command == "exit") {
            break;
        } else if (command == "") {
            continue;
        }

        if (command == "printb") {
            convert_to_binary(&inputtedNum, bits, sizeof(int64_t));
            cout << "The value in binary is " << bits << endl;
            continue;
        } else if (command == "printd") {
            cout << "The value in decimal is " << inputtedNum << endl;
            continue;
        }

        size_t spacePos = command.find(' ');
        if (spacePos == string::npos) {
            // Check if the command really is not an actual command before assuming there was no seperator
            if (!(command == "test" || command == "set" || command == "reset" || command == "toggle" || command == "printd" || command == "printb" || command == "setVal")) {
                cerr << "Invalid command" << endl;
                continue;
            }

            cerr << "Error parsing command: no seperator" << endl;
            continue;
        }

        string instruction, value;
        try {
            instruction = command.substr(0, spacePos);
            value = command.substr(spacePos + 1);
        } catch (out_of_range &e) {
            cerr << "Error parsing command: No value for the instruction" << endl;
            continue;
        } catch (exception &e) {
            cerr << "Caught an exception: " << e.what() << endl;
            continue;
        } catch (...) {
            cerr << "Caught an unknown exception" << endl;
            continue;
        }

        if (instruction == "test") {
            int bitToTest;
            try {
                bitToTest = stoi(value);
            } catch (invalid_argument &e) {
                cerr << "Invalid argument, value is not a number" << endl;
                continue;
            } catch (out_of_range &e) {
                cerr << "Invalid argument, value is not within [0, 63]" << endl;
                continue;
            }
            if (bitToTest < 0 || bitToTest > 63) {
                cerr << "Invalid argument, value is not within [0, 63]" << endl;
                continue;
            }
            cout << "Bit " << bitToTest << " is " << (char)(testbit(&inputtedNum, bitToTest) + 0x30) << endl;
            continue;
        } else if (instruction == "set") {
            int bitToSet;
            try {
                bitToSet = stoi(value);
            } catch (invalid_argument &e) {
                cerr << "Invalid argument, value is not a number" << endl;
                continue;
            } catch (out_of_range &e) {
                cerr << "Invalid argument, value is not within [0, 63]" << endl;
                continue;
            }
            if (bitToSet < 0 || bitToSet > 63) {
                cerr << "Invalid argument, value is not within [0, 63]" << endl;
                continue;
            }
            setbit(&inputtedNum, bitToSet);
            cout << "Bit " << bitToSet << " set to 1" << endl;
            continue;
        } else if (instruction == "reset") {
            int bitToReset;
            try {
                bitToReset = stoi(value);
            } catch (invalid_argument &e) {
                cerr << "Invalid argument, value is not a number" << endl;
                continue;
            } catch (out_of_range &e) {
                cerr << "Invalid argument, value is not within [0, 63]" << endl;
                continue;
            }
            if (bitToReset < 0 || bitToReset > 63) {
                cerr << "Invalid argument, value is not within [0, 63]" << endl;
                continue;
            }
            resetbit(&inputtedNum, bitToReset);
            cout << "Bit " << bitToReset << " reset to 0" << endl;
            continue;
        } else if (instruction == "toggle") {
            int bitToToggle;
            try {
                bitToToggle = stoi(value);
            } catch (invalid_argument &e) {
                cerr << "Invalid argument, value is not a number" << endl;
                continue;
            } catch (out_of_range &e) {
                cerr << "Invalid argument, value is not within [0, 63]" << endl;
                continue;
            }
            if (bitToToggle < 0 || bitToToggle > 63) {
                cerr << "Invalid argument, value is not within [0, 63]" << endl;
                continue;
            }
            cout << "Bit " << bitToToggle << " toggled to " << (char)(togglebit(&inputtedNum, bitToToggle) + 0x30) << endl;
            continue;
        } else if (instruction == "setVal") {
            int64_t newValue;
            try {
                newValue = stoll(value);
            } catch (invalid_argument &e) {
                cerr << "Invalid argument, value is not a number" << endl;
                continue;
            } catch (out_of_range &e) {
                cerr << "Invalid argument, value is too small or too large" << endl;
                continue;
            }
            inputtedNum = newValue;
            cout << "Value set to " << inputtedNum << endl;
            continue;
        }

        cerr << "Invalid command" << endl;
    }
    return 0;
}

void convert_to_binary(void *data, string &bits, size_t size) {
    size *= 8; // because size should be the size of data in bytes
    bits = ""; // clear the string

    bool hadFirstOne = false;
    for (size_t i = 0; i < size; ++i) {
        uint8_t currentBit = testbit(data, size - i - 1);
        if (i == size - 1 && !hadFirstOne && currentBit == 0) {
            bits += currentBit + 0x30; // 0x30 corrosponds to '0' in ASCII
            continue;
        }
        if (currentBit == 0 && !hadFirstOne) continue;
        hadFirstOne = true;
        bits += currentBit + 0x30; // 0x30 corrosponds to '0' in ASCII
    }
}
