

#include <string>

// ============================================================
//  PATTERN GENERATOR & MATHEMATICAL TOOLKIT - HEADER
// ============================================================

const int MAX_ROWS = 20;
const int MAX_MATRIX_SIZE = 10;
const int HISTORY_SIZE = 50;

std::string trimCopy(const std::string& s);
std::string toUpperCopy(const std::string& s);
bool isDigitChar(char c);

// Safely parses an integer from a string. Sets ok=false on any bad input
// instead of throwing, so callers can re-prompt cleanly.
long long safeAtoll(const std::string& s, bool& ok);

long long readIntValidated(const std::string& prompt, long long minv, long long maxv);

// Reads a string and validates that every character belongs to the allowed
// digit set for a given numeral-system base (used by the converter).
std::string readValidBaseString(const std::string& prompt, int base);

void pauseForUser();

// ======================= DISPLAY HELPERS ======================
void printLine(char c = '=', int len = 60);
void printCenter(const std::string& text, int width = 60);
void printTableHeader(const std::string& c1, const std::string& c2, int w1, int w2);
void printTableRow(const std::string& c1, const std::string& c2, int w1, int w2);
void printTableBottom(int w1, int w2);

// ===================== CALCULATION HISTORY (STACK) =============
// A tiny array-based stack that logs every operation the user runs, in
// LIFO order, mirroring the "Prediction History" idea from the DSA
// reference project but scaled to this assignment's own feature set.
class HistoryStack {
    std::string entries[HISTORY_SIZE];
    int top;
public:
    HistoryStack();
    bool isFull()  const;
    bool isEmpty() const;
    void push(const std::string& entry);
    void display();
};

// ======================= MATH TOOLKIT ========================
class MathToolkit {
    HistoryStack history;

    // ---- Number System Converter helpers ----
    long long toDecimal(const std::string& s, int base);
    std::string fromDecimal(long long value, int base);

    // ---- Prime helper ----
    bool isPrime(long long n);

    // ---- Armstrong helpers ----
    long long intPower(long long base, int exp);
    int countDigits(long long n);
    bool isArmstrong(long long n);

    // ---- Factorial helper ----
    unsigned long long factorial(int n);

    // ---- Pattern helpers ----
    void patternRightTriangle(int rows);
    void patternInvertedTriangle(int rows);
    void patternPyramid(int rows);
    void patternNumberTriangle(int rows);
    void patternPascal(int rows);
    void patternDiamond(int rows);

    // ---- Matrix helpers ----
    typedef int Matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

    void readMatrix(Matrix m, int rows, int cols, const std::string& label);
    void printMatrix(Matrix m, int rows, int cols);
    void addMatrices(Matrix a, Matrix b, Matrix r, int rows, int cols);
    void subMatrices(Matrix a, Matrix b, Matrix r, int rows, int cols);
    void mulMatrices(Matrix a, Matrix b, Matrix r, int rowsA, int inner, int colsB);
    void transposeMatrix(Matrix a, Matrix r, int rows, int cols);

public:
    // ---- 1. Number System Converter ----
    void numberSystemConverter();

    // ---- 2. Prime Number Checker ----
    void primeChecker();

    // ---- 3. Armstrong Number Checker ----
    void armstrongChecker();

    // ---- 4. Fibonacci Series ----
    void fibonacciSeries();

    // ---- 5. Factorial Calculator ----
    void factorialCalculator();

    // ---- 6. Pattern Printing ----
    void patternPrinting();

    // ---- 7. Matrix Operations ----
    void matrixOperations();

    // ---- 8. History viewer ----
    void showHistory();
};


