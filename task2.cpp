#include <iostream>

using namespace std;

int main() {
    double num1, num2, result;
    char operation;

    // Display menu
    cout << "Simple Calculator" << endl;
    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter an operator (+, -, *, /): ";
    cin >> operation;

    cout << "Enter second number: ";
    cin >> num2;

    // Perform calculation
    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0)
                result = num1 / num2;
            else {
                cout << "Error: Division by zero is not allowed." << endl;
                return 1; // Exit with error
            }
            break;
        default:
            cout << "Error: Invalid operator." << endl;
            return 1; // Exit with error
    }

    // Display result
    cout << "Result: " << result << endl;

    return 0;
}