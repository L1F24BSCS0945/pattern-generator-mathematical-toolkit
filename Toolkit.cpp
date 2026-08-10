#include "toolkit.h"
#include <iostream>
using namespace std;

// ============================================================
//  PATTERN GENERATOR & MATHEMATICAL TOOLKIT - IMPLEMENTATION
// ============================================================

string trimCopy(const string& s) {
    size_t b = 0, e = s.size();
    while (b < e && (s[b] == ' ' || s[b] == '\t' || s[b] == '\r')) ++b;
    while (e > b && (s[e - 1] == ' ' || s[e - 1] == '\t' || s[e - 1] == '\r' || s[e - 1] == '\n')) --e;
    return s.substr(b, e - b);
}

string toUpperCopy(const string& s) {
    string r = s;
    for (size_t i = 0; i < r.size(); ++i)
        if (r[i] >= 'a' && r[i] <= 'z') r[i] = char(r[i] - 'a' + 'A');
    return r;
}

bool isDigitChar(char c) { return c >= '0' && c <= '9'; }

long long safeAtoll(const string& s, bool& ok) {
    ok = false;
    string t = trimCopy(s);
    if (t.empty()) return 0;
    size_t i = 0; int sign = 1;
    if (t[0] == '+' || t[0] == '-') { if (t[0] == '-') sign = -1; i = 1; }
    if (i == t.size()) return 0;
    long long val = 0;
    for (; i < t.size(); ++i) {
        if (!isDigitChar(t[i])) return 0;
        val = val * 10 + (t[i] - '0');
        if (val > 4000000000000000000LL) return 0;
    }
    ok = true;
    return val * sign;
}

long long readIntValidated(const string& prompt, long long minv, long long maxv) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) { cin.clear(); continue; }
        bool ok;
        long long v = safeAtoll(line, ok);
        if (!ok) { cout << "  Invalid integer, try again.\n"; continue; }
        if (v < minv || v > maxv) { cout << "  Value must be between " << minv << " and " << maxv << ".\n"; continue; }
        return v;
    }
}

string readValidBaseString(const string& prompt, int base) {
    string digits = "0123456789ABCDEF";
    string valid = digits.substr(0, base);
    string s;
    while (true) {
        cout << prompt;
        if (!getline(cin, s)) { cin.clear(); continue; }
        s = toUpperCopy(trimCopy(s));
        bool ok = !s.empty();
        for (size_t i = 0; i < s.size(); ++i)
            if (valid.find(s[i]) == string::npos) { ok = false; break; }
        if (ok) return s;
        cout << "  Invalid digits for base " << base << ", try again.\n";
    }
}

void pauseForUser() {
    cout << "\nPress Enter to return to the menu...";
    string dummy;
    getline(cin, dummy);
}

// ======================= DISPLAY HELPERS ======================
void printLine(char c, int len) {
    for (int i = 0; i < len; ++i) cout << c;
    cout << "\n";
}

void printCenter(const string& text, int width) {
    int len = (int)text.size();
    int pad = (width - len) / 2;
    if (pad < 0) pad = 0;
    for (int i = 0; i < pad; ++i) cout << ' ';
    cout << text << "\n";
}

void printTableHeader(const string& c1, const string& c2, int w1, int w2) {
    cout << "+"; for (int i = 0; i < w1; ++i) cout << '-';
    cout << "+"; for (int i = 0; i < w2; ++i) cout << '-';
    cout << "+\n";
    cout << "| " << c1; for (int i = (int)c1.size(); i < w1 - 2; ++i) cout << ' ';
    cout << "| " << c2; for (int i = (int)c2.size(); i < w2 - 2; ++i) cout << ' ';
    cout << "|\n";
    cout << "+"; for (int i = 0; i < w1; ++i) cout << '=';
    cout << "+"; for (int i = 0; i < w2; ++i) cout << '=';
    cout << "+\n";
}

void printTableRow(const string& c1, const string& c2, int w1, int w2) {
    cout << "| " << c1; for (int i = (int)c1.size(); i < w1 - 2; ++i) cout << ' ';
    cout << "| " << c2; for (int i = (int)c2.size(); i < w2 - 2; ++i) cout << ' ';
    cout << "|\n";
}

void printTableBottom(int w1, int w2) {
    cout << "+"; for (int i = 0; i < w1; ++i) cout << '-';
    cout << "+"; for (int i = 0; i < w2; ++i) cout << '-';
    cout << "+\n";
}

// ===================== CALCULATION HISTORY (STACK) =============
HistoryStack::HistoryStack() : top(-1) {}

bool HistoryStack::isFull()  const { return top == HISTORY_SIZE - 1; }
bool HistoryStack::isEmpty() const { return top == -1; }

void HistoryStack::push(const string& entry) {
    if (isFull()) {
        for (int i = 0; i < top; ++i) entries[i] = entries[i + 1];
        entries[top] = entry;
        return;
    }
    entries[++top] = entry;
}

void HistoryStack::display() {
    printLine('=');
    printCenter("CALCULATION HISTORY (Stack - LIFO)");
    printLine('=');
    if (isEmpty()) {
        cout << "  No calculations yet.\n";
        printLine('=');
        return;
    }
    for (int i = top; i >= 0; --i) {
        cout << "  #" << (top - i + 1) << "  " << entries[i] << "\n";
    }
    printLine('=');
}

// ======================= MATH TOOLKIT ========================

// ---- Number System Converter helpers ----
long long MathToolkit::toDecimal(const string& s, int base) {
    long long result = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        int digit = isDigitChar(c) ? (c - '0') : (c - 'A' + 10);
        result = result * base + digit;
    }
    return result;
}

string MathToolkit::fromDecimal(long long value, int base) {
    if (value == 0) return "0";
    bool negative = value < 0;
    if (negative) value = -value;
    string digits = "0123456789ABCDEF";
    string result = "";
    while (value > 0) { result = digits[value % base] + result; value /= base; }
    if (negative) result = "-" + result;
    return result;
}

// ---- Prime helper ----
bool MathToolkit::isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

// ---- Armstrong helpers ----
long long MathToolkit::intPower(long long base, int exp) {
    long long r = 1;
    for (int i = 0; i < exp; ++i) r *= base;
    return r;
}

int MathToolkit::countDigits(long long n) {
    if (n == 0) return 1;
    int c = 0;
    while (n > 0) { ++c; n /= 10; }
    return c;
}

bool MathToolkit::isArmstrong(long long n) {
    if (n < 0) return false;
    int digits = countDigits(n);
    long long sum = 0, temp = n;
    while (temp > 0) { sum += intPower(temp % 10, digits); temp /= 10; }
    return sum == n;
}

// ---- Factorial helper ----
unsigned long long MathToolkit::factorial(int n) {
    unsigned long long r = 1;
    for (int i = 2; i <= n; ++i) r *= i;
    return r;
}

// ---- Pattern helpers ----
void MathToolkit::patternRightTriangle(int rows) {
    for (int i = 1; i <= rows; ++i) { for (int j = 0; j < i; ++j) cout << "* "; cout << "\n"; }
}

void MathToolkit::patternInvertedTriangle(int rows) {
    for (int i = rows; i >= 1; --i) { for (int j = 0; j < i; ++j) cout << "* "; cout << "\n"; }
}

void MathToolkit::patternPyramid(int rows) {
    for (int i = 1; i <= rows; ++i) {
        for (int s = 0; s < rows - i; ++s) cout << "  ";
        for (int j = 0; j < 2 * i - 1; ++j) cout << "* ";
        cout << "\n";
    }
}

void MathToolkit::patternNumberTriangle(int rows) {
    for (int i = 1; i <= rows; ++i) { for (int j = 1; j <= i; ++j) cout << j << " "; cout << "\n"; }
}

void MathToolkit::patternPascal(int rows) {
    for (int i = 0; i < rows; ++i) {
        for (int s = 0; s < rows - i; ++s) cout << "  ";
        long long value = 1;
        for (int j = 0; j <= i; ++j) { cout << value << " "; value = value * (i - j) / (j + 1); }
        cout << "\n";
    }
}

void MathToolkit::patternDiamond(int rows) {
    patternPyramid(rows);
    for (int i = rows - 1; i >= 1; --i) {
        for (int s = 0; s < rows - i; ++s) cout << "  ";
        for (int j = 0; j < 2 * i - 1; ++j) cout << "* ";
        cout << "\n";
    }
}

// ---- Matrix helpers ----
void MathToolkit::readMatrix(Matrix m, int rows, int cols, const string& label) {
    cout << "Enter elements for matrix " << label << " (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            m[i][j] = (int)readIntValidated(
                "  [" + to_string(i) + "][" + to_string(j) + "] = ", -1000000, 1000000);
}

void MathToolkit::printMatrix(Matrix m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) cout << m[i][j] << "\t";
        cout << "\n";
    }
}

void MathToolkit::addMatrices(Matrix a, Matrix b, Matrix r, int rows, int cols) {
    for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j) r[i][j] = a[i][j] + b[i][j];
}

void MathToolkit::subMatrices(Matrix a, Matrix b, Matrix r, int rows, int cols) {
    for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j) r[i][j] = a[i][j] - b[i][j];
}

void MathToolkit::mulMatrices(Matrix a, Matrix b, Matrix r, int rowsA, int inner, int colsB) {
    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsB; ++j) {
            r[i][j] = 0;
            for (int k = 0; k < inner; ++k) r[i][j] += a[i][k] * b[k][j];
        }
}

void MathToolkit::transposeMatrix(Matrix a, Matrix r, int rows, int cols) {
    for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j) r[j][i] = a[i][j];
}

// ---- 1. Number System Converter ----
void MathToolkit::numberSystemConverter() {
    printLine('=');
    printCenter("NUMBER SYSTEM CONVERTER");
    printLine('=');
    cout << "  1. Binary (base 2)   2. Octal (base 8)\n";
    cout << "  3. Decimal (base 10) 4. Hexadecimal (base 16)\n";

    int fromChoice = (int)readIntValidated("  Convert FROM which system? (1-4): ", 1, 4);
    int toChoice = (int)readIntValidated("  Convert TO which system?   (1-4): ", 1, 4);
    int bases[] = { 0, 2, 8, 10, 16 };
    int srcBase = bases[fromChoice], dstBase = bases[toChoice];

    string input = readValidBaseString("  Enter the number to convert: ", srcBase);
    long long dec = toDecimal(input, srcBase);
    string output = fromDecimal(dec, dstBase);

    printLine('-');
    cout << "  Result: " << input << " (base " << srcBase << ")  =  "
        << output << " (base " << dstBase << ")\n";
    printLine('=');

    history.push("Converter: " + input + " [base " + to_string(srcBase) +
        "] -> " + output + " [base " + to_string(dstBase) + "]");
}

// ---- 2. Prime Number Checker ----
void MathToolkit::primeChecker() {
    printLine('=');
    printCenter("PRIME NUMBER CHECKER");
    printLine('=');
    int choice = (int)readIntValidated(
        "  1. Check a single number\n  2. List primes up to N\n  Choice: ", 1, 2);

    if (choice == 1) {
        long long n = readIntValidated("  Enter a number: ", 0, 1000000000000LL);
        bool prime = isPrime(n);
        printLine('-');
        cout << "  " << n << (prime ? " IS a prime number.\n" : " is NOT a prime number.\n");
        printLine('=');
        history.push("Prime check: " + to_string(n) + (prime ? " -> prime" : " -> not prime"));
    }
    else {
        long long n = readIntValidated("  List primes up to: ", 0, 100000);
        printLine('-');
        cout << "  Primes up to " << n << ": ";
        bool any = false;
        for (long long i = 2; i <= n; ++i) if (isPrime(i)) { cout << i << " "; any = true; }
        if (!any) cout << "(none)";
        cout << "\n";
        printLine('=');
        history.push("Prime list up to " + to_string(n));
    }
}

// ---- 3. Armstrong Number Checker ----
void MathToolkit::armstrongChecker() {
    printLine('=');
    printCenter("ARMSTRONG NUMBER CHECKER");
    printLine('=');
    int choice = (int)readIntValidated(
        "  1. Check a single number\n  2. List Armstrong numbers in a range\n  Choice: ", 1, 2);

    if (choice == 1) {
        long long n = readIntValidated("  Enter a number: ", 0, 1000000000000LL);
        bool arm = isArmstrong(n);
        printLine('-');
        cout << "  " << n << (arm ? " IS an Armstrong number.\n" : " is NOT an Armstrong number.\n");
        printLine('=');
        history.push("Armstrong check: " + to_string(n) + (arm ? " -> yes" : " -> no"));
    }
    else {
        long long lo = readIntValidated("  Start of range: ", 0, 1000000);
        long long hi = readIntValidated("  End of range: ", lo, 1000000);
        printLine('-');
        cout << "  Armstrong numbers between " << lo << " and " << hi << ": ";
        bool any = false;
        for (long long i = lo; i <= hi; ++i) if (isArmstrong(i)) { cout << i << " "; any = true; }
        if (!any) cout << "(none)";
        cout << "\n";
        printLine('=');
        history.push("Armstrong range " + to_string(lo) + "-" + to_string(hi));
    }
}

// ---- 4. Fibonacci Series ----
void MathToolkit::fibonacciSeries() {
    printLine('=');
    printCenter("FIBONACCI SERIES");
    printLine('=');
    int n = (int)readIntValidated("  How many terms to generate? ", 1, 90);
    long long a = 0, b = 1;
    cout << "  Series: ";
    for (int i = 0; i < n; ++i) { cout << a << " "; long long nx = a + b; a = b; b = nx; }
    cout << "\n";
    printLine('=');
    history.push("Fibonacci: first " + to_string(n) + " terms");
}

// ---- 5. Factorial Calculator ----
void MathToolkit::factorialCalculator() {
    printLine('=');
    printCenter("FACTORIAL CALCULATOR");
    printLine('=');
    int n = (int)readIntValidated("  Enter a number (0-20): ", 0, 20);
    unsigned long long f = factorial(n);
    cout << "  " << n << "! = " << f << "\n";
    printLine('=');
    history.push(to_string(n) + "! = " + to_string(f));
}

// ---- 6. Pattern Printing ----
void MathToolkit::patternPrinting() {
    printLine('=');
    printCenter("PATTERN PRINTING");
    printLine('=');
    cout << "  1. Right Triangle\n  2. Inverted Right Triangle\n  3. Pyramid\n"
        << "  4. Number Triangle\n  5. Pascal's Triangle\n  6. Diamond\n";
    int choice = (int)readIntValidated("  Choose a pattern (1-6): ", 1, 6);
    int rows = (int)readIntValidated("  Enter number of rows (1-" + to_string(MAX_ROWS) + "): ", 1, MAX_ROWS);

    cout << "\n";
    switch (choice) {
    case 1: patternRightTriangle(rows); break;
    case 2: patternInvertedTriangle(rows); break;
    case 3: patternPyramid(rows); break;
    case 4: patternNumberTriangle(rows); break;
    case 5: patternPascal(rows); break;
    case 6: patternDiamond(rows); break;
    }
    printLine('=');
    history.push("Pattern #" + to_string(choice) + " with " + to_string(rows) + " rows");
}

// ---- 7. Matrix Operations ----
void MathToolkit::matrixOperations() {
    printLine('=');
    printCenter("MATRIX OPERATIONS");
    printLine('=');
    cout << "  1. Addition\n  2. Subtraction\n  3. Multiplication\n  4. Transpose\n";
    int choice = (int)readIntValidated("  Choose an operation (1-4): ", 1, 4);

    static Matrix a, b, result;

    if (choice == 4) {
        int r = (int)readIntValidated("  Rows: ", 1, MAX_MATRIX_SIZE);
        int c = (int)readIntValidated("  Columns: ", 1, MAX_MATRIX_SIZE);
        readMatrix(a, r, c, "A");
        transposeMatrix(a, result, r, c);
        cout << "\n  Transpose:\n";
        printMatrix(result, c, r);
        printLine('=');
        history.push("Matrix transpose " + to_string(r) + "x" + to_string(c));
        return;
    }

    int r1 = (int)readIntValidated("  Matrix A rows: ", 1, MAX_MATRIX_SIZE);
    int c1 = (int)readIntValidated("  Matrix A columns: ", 1, MAX_MATRIX_SIZE);
    readMatrix(a, r1, c1, "A");

    int r2, c2;
    if (choice == 3) {
        cout << "  (Matrix B must have " << c1 << " rows to allow multiplication)\n";
        r2 = c1;
        c2 = (int)readIntValidated("  Matrix B columns: ", 1, MAX_MATRIX_SIZE);
    }
    else {
        cout << "  (Matrix B must be " << r1 << "x" << c1 << " to match Matrix A)\n";
        r2 = r1; c2 = c1;
    }
    readMatrix(b, r2, c2, "B");

    cout << "\n  Result:\n";
    string opName;
    switch (choice) {
    case 1: addMatrices(a, b, result, r1, c1); printMatrix(result, r1, c1); opName = "Addition"; break;
    case 2: subMatrices(a, b, result, r1, c1); printMatrix(result, r1, c1); opName = "Subtraction"; break;
    case 3: mulMatrices(a, b, result, r1, c1, c2); printMatrix(result, r1, c2); opName = "Multiplication"; break;
    }
    printLine('=');
    history.push("Matrix " + opName + " " + to_string(r1) + "x" + to_string(c1));
}

// ---- 8. History viewer ----
void MathToolkit::showHistory() { history.display(); }