#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const string PATH = getenv("SOURCEDIR");

bool checkSymbols(vector<string> &arr, int row, int col);
int findNumLength(string &line, int pos);

int main() {
    ifstream FInput(PATH + "/input.txt");
    string line;
    int sum = 0;

    // Get width
    getline(FInput, line);
    int width = (int) line.length();
    FInput.seekg(0);


    // Get length
    int length;
    while(getline(FInput, line)) {
        length++;
    }
    FInput.clear();
    FInput.seekg(0);

    // Store file as an array.
    vector<string> diagram;
    for(int i = 0; i < length; i++) {
        getline(FInput, line);
        diagram.push_back(line);
    }
    FInput.close();

    for(int i = 0; i < length; i++) {
        cout << "Row " << i + 1 << endl;
        for(int j = 0; j < width; j++) {
            if(diagram[i][j] <= '9' && diagram[i][j] >= '0' && diagram[i][j] != '\n') {
                int digitCnt = findNumLength(diagram[i], j);
                string numStr = diagram[i].substr(j, digitCnt);
                cout << "Target Char: " << diagram[i][j] << endl;
                cout << "Digits found: " << digitCnt << endl;
                cout << "Num string: " << numStr << endl;

                for(int k = j; k < j + digitCnt; k++) {
                    if (checkSymbols(diagram, i, k)) {
                        cout << "Found num: " << stoi(numStr) << endl;
                        sum += stoi(numStr);
                        break;
                    }
                }

                cout << "Continuing search from char: " << diagram[i][j+digitCnt] << endl;
                j += digitCnt;
            }
        }
    }

    cout << "Sum of part numbers: " << sum << endl;
    return 0;
}

bool checkSymbols(vector<string> &arr, int row, int col) {
    int width = (int) arr[row].length();
    int length = (int) arr.size();

    for(int i = max(row - 1, 0); i < min(row + 2, length); i++) {
        for(int j = max(col - 1, 0); j < min(col + 2, width); j++) {
            char val = arr[i][j];

            if(val != '.' && ('0' > val || '9' < val) && val > ' ') {
                return true;
            }
        }
    }

    return false;
}

int findNumLength(string &line, int pos) {
    for(int i = pos; i < line.length(); i++) {
        if('0' > line[i] || '9' < line[i]) {

            return i - pos;
        }
    }

    // If the line ends before a non-numerical character is reached,
    // return the length from pos to eol
    return (int) line.length() - pos;
}
