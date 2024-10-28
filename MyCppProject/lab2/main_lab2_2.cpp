#include "include/lab2_2.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    try {
        string input1, input2;
        string operation;

        // Input data
        cout << "Enter the first hexadecimal number: ";
        cin >> input1;
        cout << "Enter the second hexadecimal number: ";
        cin >> input2;
        cout << "Choose an operation (+, -, ==, !=, <, >): ";
        cin >> operation;

        // Initialize Hex objects
        Hex num1(input1);
        Hex num2(input2);

        // Perform the selected operation
        if (operation == "+") {
            num1.add(num2);
            cout << "Result of addition: " << num1.toString() << endl;
        }
        else if (operation == "-") {
            num1.subtract(num2);
            cout << "Result of subtraction: " << num1.toString() << endl;
        }
        else if (operation == "==") {
            cout << (num1.isEqual(num2) ? "Numbers are equal" : "Numbers are not equal") << endl;
        }
        else if (operation == "!=") {
            cout << (!num1.isEqual(num2) ? "Numbers are not equal" : "Numbers are equal") << endl;
        }
        else if (operation == "<") {
            cout << (num1.isLess(num2) ? "The first number is less than the second" : "The first number is not less than the second") << endl;
        }
        else if (operation == ">") {
            cout << (num1.isGreater(num2) ? "The first number is greater than the second" : "The first number is not greater than the second") << endl;
        }
        else {
            cout << "Invalid operation" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Unhandled exception: " << e.what() << endl;
    }

    return 0;
}