#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// Set path to day 1 folder in the run config
const string PATH = getenv("INPUTDIR");
const map<string, char> numWords = {
        {"one", '1'},
        {"two", '2'},
        {"three", '3'},
        {"four", '4'},
        {"five", '5'},
        {"six", '6'},
        {"seven", '7'},
        {"eight", '8'},
        {"nine", '9'}
};


string checkForWords(const string &line, int index = 0);
template<typename keyType, typename ValType> vector<keyType> getKeys(const map<keyType, ValType> &map);
int findPartOneSum(const string &line); // Just so I can output both part 1 and part 2 answer, not actually needed

int main() {
    ifstream FInput(PATH);
    string line;
    int sum = 0;
    int alphaSum = 0;


    while (!FInput.eof()) {
        FInput >> line;
        string num = "00";

        // Find first number
        for (int i = 0; i < line.length(); i++) {
            if (line[i] > 48 && line[i] < 58) {
                num[0] = line[i];
                break;
            } else if (!checkForWords(line, i).empty()) {
                num[0] = numWords.at(checkForWords(line, i));
                break;
            }
        }

        // Find last number
        for (int i = (int) line.length() - 1; i >= 0; i--) {
            if (line[i] > 48 && line[i] < 58) {
                num[1] = line[i];
                break;
            } else if (!checkForWords(line, i).empty()) {
                num[1] = numWords.at(checkForWords(line, i));
                break;
            }
        }

        sum += findPartOneSum(line);
        alphaSum += stoi(num);
    }

    cout << "The calibration code is " << sum << endl;
    cout << "The calibration code including spelled numbers is " << alphaSum << endl;
    return 0;
}

// Checks for number words at a given index.
// Returns the word it finds, or an empty string if there is no word
string checkForWords(const string &line, int index) {
    vector<string> keys = getKeys(numWords);
    string firstWord;

    for (const auto &word : keys) {
        string str = line.substr(index, word.length());
        if (str == word) {
            return word;
        }
    }

    return "";
}

// Grabs all the keys in a map
template<typename keyType, typename ValType>
vector<keyType> getKeys(const map<keyType, ValType> &map) {
    vector<keyType> keys;

    for (auto const& element: map) {
        keys.push_back(element.first);
    }

    return keys;
}

int findPartOneSum(const string &line) {
    string num = "00";

    // Find first number
    for (int i = 0; i < line.length(); i++) {
        if (line[i] > 48 && line[i] < 58) {
            num[0] = line[i];
            break;
        }
    }

    // Find last number
    for (int i = (int) line.length() - 1; i >= 0; i--) {
        if (line[i] > 48 && line[i] < 58) {
            num[1] = line[i];
            break;
        }
    }

     return stoi(num);
}