#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const string PATH = getenv("SOURCEDIR");

bool checkSymbols(vector<string> &arr, int row, int col);
int checkGearRatio(vector<string> &arr, int row, int col);
int findNumLength(string &line, int pos);

int main() {
    ifstream FInput(PATH + "/input.txt");
    string line;
    int partSum = 0;
    int ratioSum = 0;

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
        for(int j = 0; j < width; j++) {
            if(isdigit(diagram[i][j])) {
                int digitCnt = findNumLength(diagram[i], j);
                string numStr = diagram[i].substr(j, digitCnt);

                for(int k = j; k < j + digitCnt; k++) {
                    if (checkSymbols(diagram, i, k)) {
                        partSum += stoi(numStr);
                        break;
                    }
                }

                j += digitCnt - 1;
            } else if (diagram[i][j] == '*') {
                ratioSum += checkGearRatio(diagram, i, j);
            }
        }
    }

    cout << "Sum of part numbers: " << partSum << endl;
    cout << "Sum of gear ratios: " << ratioSum << endl;
    return 0;
}

bool checkSymbols(vector<string> &arr, int row, int col) {
    int width = (int) arr[row].length();
    int length = (int) arr.size();

    for(int i = max(row - 1, 0); i < min(row + 2, length); i++) {
        for(int j = max(col - 1, 0); j < min(col + 2, width); j++) {
            char val = arr[i][j];

            if(val != '.' && not isdigit(arr[i][j]) && val > ' ') {
                return true;
            }
        }
    }

    return false;
}

int checkGearRatio(vector<string> &arr, int row, int col) {
    int width = (int) arr[row].length();
    int length = (int) arr.size();
    vector<int> nums;

    for(int i = max(row - 1, 0); i < min(row + 2, length); i++) {
        for(int j = max(col - 1, 0); j < min(col + 2, width); j++) {
            if(isdigit(arr[i][j])) {
                // Find the first digit by iterating backwards until it finds a non-number
                while(isdigit(arr[i][j-1])) {
                    j--;
                }

                int digitCount = findNumLength(arr[i], j);
                nums.push_back(stoi(arr[i].substr(j, digitCount)));
                j += digitCount;
            }
        }
    }

    if (nums.size() == 2) {
        return nums[0] * nums[1];
    }

    return 0;
}

int findNumLength(string &line, int pos) {
    for(int i = pos; i < line.length(); i++) {
        if(not isdigit(line[i])) {

            return i - pos;
        }
    }

    // If the line ends before a non-numerical character is reached,
    // return the length from pos to eol
    return (int) line.length() - pos;
}

