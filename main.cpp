#include <iostream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

int prompt(const string& prompt_message, const string& error_message, int lower_bound = numeric_limits<int>::min(), int upper_bound = numeric_limits<int>::max(), int default_value = numeric_limits<int>::min()) {
    int value;
    string input;
    while (true) {
        cout << prompt_message;
        if (default_value != numeric_limits<int>::min()) {
            cout << " (or press Enter to use default value " << default_value << ")";
        }
        cout << " (or type 'exit' to abort)" << endl;
        getline(cin, input);
        if (input.empty() && default_value != numeric_limits<int>::min()) {
            return default_value;
        }
        if (input == "exit") {
            throw runtime_error("User aborted the prompt.");
        }
        try {
            value = stoi(input);
            if (value < lower_bound || value > upper_bound) {
                throw out_of_range("out of range");
            }
            return value;
        } catch (exception& e) {
            cout << error_message << endl;
        }
    }
}

string prompt(const string& prompt_message, const string& error_message, const string& default_value = "") {
    string input;
    while (true) {
        cout << prompt_message;
        if (!default_value.empty()) {
            cout << " (or press Enter to use default value \"" << default_value << "\")";
        }
        cout << " (or type 'exit' to abort)" << endl;
        getline(cin, input);
        if (input.empty() && !default_value.empty()) {
            return default_value;
        }
        if (input == "exit") {
            throw runtime_error("User aborted the prompt.");
        }
        if (!input.empty()) {
            return input;
        } else {
            cout << error_message << endl;
        }
    }
}

int main() {
    try {
        int value1 = prompt("Please enter a value between 0 and 100:", "Your value is invalid. Please try again.", 0, 100, 50);
        cout << "The value chosen by the user is " << value1 << endl;

        int value2 = prompt("Please enter any integer:", "Your value is invalid. Please try again.", numeric_limits<int>::min(), numeric_limits<int>::max(), 10);
        cout << "The value chosen by the user is " << value2 << endl;

        int value3 = prompt("Please enter a value greater than 50:", "Your value is invalid. Please try again.", 50, numeric_limits<int>::max(), 75);
        cout << "The value chosen by the user is " << value3 << endl;

        int value4 = prompt("Please enter a value less than 10:", "Your value is invalid. Please try again.", numeric_limits<int>::min(), 10, 5);
        cout << "The value chosen by the user is " << value4 << endl;

        string value5 = prompt("Please enter a string:", "Your input is invalid. Please try again.", "default string");
        cout << "The string chosen by the user is \"" << value5 << "\"" << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
