#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

const string PATH = getenv("SOURCEDIR");

int main() {
    ifstream FInput(PATH + "/input.txt");
    string line;
    string num;
    int sum = 0;

    while (!FInput.eof()) {
        FInput >> line;

        // Find first number
        for(auto ch : line) {
            if (ch > 48 && ch < 58) {
                num[0] = ch;
                break;
            }
        }

        // Find last number
        reverse(line.begin(), line.end());
        for(auto ch : line) {
            if (ch > 48 && ch < 58) {
                num[1] = ch;
                break;
            }
        }

        sum += stoi(num);
    }

    cout << "The calibration code is " << sum << endl;
    return 0;
}