#include "toolkit.h"
#include <iostream>
using namespace std;

// ============================================================
//  PATTERN GENERATOR & MATHEMATICAL TOOLKIT - MAIN
// ============================================================

void showWelcomeBanner() {
    printLine('*');
    printCenter("PATTERN GENERATOR & MATHEMATICAL TOOLKIT", 60);
    printCenter("Functions | Loops | Arrays | Mathematics", 60);
    printLine('*');
    cout << "\n";
}

void showMainMenu() {
    printLine('=');
    printCenter("MAIN MENU");
    printLine('=');
    cout << "  1. Number System Converter\n";
    cout << "  2. Prime Number Checker\n";
    cout << "  3. Armstrong Number Checker\n";
    cout << "  4. Fibonacci Series\n";
    cout << "  5. Factorial Calculator\n";
    cout << "  6. Pattern Printing\n";
    cout << "  7. Matrix Operations\n";
    cout << "  8. View Calculation History\n";
    cout << "  0. Exit\n";
    printLine('=');
    cout << "  Choice: ";
}

int main() {
    showWelcomeBanner();
    MathToolkit toolkit;

    while (true) {
        showMainMenu();
        string line;
        if (!getline(cin, line)) { cin.clear(); continue; }
        bool ok;
        long long choice = safeAtoll(line, ok);
        if (!ok) { cout << "  Invalid choice.\n"; continue; }

        if (choice == 1) toolkit.numberSystemConverter();
        else if (choice == 2) toolkit.primeChecker();
        else if (choice == 3) toolkit.armstrongChecker();
        else if (choice == 4) toolkit.fibonacciSeries();
        else if (choice == 5) toolkit.factorialCalculator();
        else if (choice == 6) toolkit.patternPrinting();
        else if (choice == 7) toolkit.matrixOperations();
        else if (choice == 8) toolkit.showHistory();
        else if (choice == 0) break;
        else { cout << "  Invalid choice.\n"; continue; }

        pauseForUser();
    }

    printLine('=');
    cout << "  Thank you for using the Mathematical Toolkit!\n";
    printLine('=');
    return 0;
}