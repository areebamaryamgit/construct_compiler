#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const vector<string> CUSTOM_DATA_TYPES = {"myint", "myfloat", "mychar", "mybool", "mydouble"};
const vector<string> CUSTOM_RESERVED_WORDS = {"start", "stop", "check", "show", "end"};

const regex VARIABLE_REGEX("^[a-zA-Z_][a-zA-Z0-9_]*_z$");
const regex NUMBER_REGEX("^[-+]?[0-9]*\\.?[0-9]+$");
const regex OPERATOR_REGEX("^[=+\\-*/]$");

bool isCustomDataType(const string &word) {
    return find(CUSTOM_DATA_TYPES.begin(), CUSTOM_DATA_TYPES.end(), word) != CUSTOM_DATA_TYPES.end();
}

bool isCustomReservedWord(const string &word) {
    return find(CUSTOM_RESERVED_WORDS.begin(), CUSTOM_RESERVED_WORDS.end(), word) != CUSTOM_RESERVED_WORDS.end();
}

bool isValidVariableName(const string &name) {
    return regex_match(name, VARIABLE_REGEX);
}

bool isNumber(const string &word) {
    return regex_match(word, NUMBER_REGEX);
}

bool isOperator(const string &word) {
    return regex_match(word, OPERATOR_REGEX);
}

bool isBooleanLiteral(const string &word) {
    return word == "true" || word == "false";
}

void processFile(const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    cout << left << setw(10) << "Line" 
         << setw(15) << "Token" 
         << setw(15) << "Type" 
         << "Value/Attr" << endl;
    cout << string(50, '-') << endl;

    string line;
    int lineNum = 1;

    while (getline(file, line)) {
        istringstream stream(line);
        string word;
        while (stream >> word) {
            if (isCustomDataType(word)) {
                cout << left << setw(10) << lineNum
                     << setw(15) << word
                     << setw(15) << "DATA_TYPE"
                     << "-" << endl;
            } else if (isCustomReservedWord(word)) {
                cout << left << setw(10) << lineNum
                     << setw(15) << word
                     << setw(15) << "RESERVED"
                     << "-" << endl;
            } else if (isValidVariableName(word)) {
                cout << left << setw(10) << lineNum
                     << setw(15) << word
                     << setw(15) << "ID"
                     << "-" << endl;
            } else if (isBooleanLiteral(word)) {
                cout << left << setw(10) << lineNum
                     << setw(15) << word
                     << setw(15) << "BOOLEAN"
                     << word << endl;
            } else if (isNumber(word)) {
                cout << left << setw(10) << lineNum
                     << setw(15) << word
                     << setw(15) << "NUMBER"
                     << word << endl;
            } else if (isOperator(word)) {
                cout << left << setw(10) << lineNum
                     << setw(15) << word
                     << setw(15) << "OPERATOR"
                     << "-" << endl;
            } else {
                cout << left << setw(10) << lineNum
                     << setw(15) << word
                     << setw(15) << "UNKNOWN"
                     << "-" << endl;
            }
        }
        lineNum++;
    }

    file.close();
}

int main() {
    string fileName = "D:\\bscs\\CC\\CCproject\\CCproject\\data 3.txt";

    cout << "Starting lexical analysis..." << endl;
    processFile(fileName);
    cout << "Lexical analysis complete." << endl;

    return 0;
}
