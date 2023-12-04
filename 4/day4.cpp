#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

const string PATH = getenv("INPUTDIR");

vector<int> splitNums(const string &numStr);
int getScore(const vector<int> &winningNumbers, const vector<int> &elfNumbers);

int main() {
    ifstream FInput(PATH);
    string line;
    int score = 0;
    regex nums(R"(Card\s+\d+: ((?:\s?\d{1,2}\s?)+)\| ((?:\s?\d{1,2}\s?)+))");


    while(getline(FInput, line)) {
        smatch matches;
        vector<int> winningNums;
        vector<int> elfNums;

        regex_search(line, matches, nums);
        winningNums = splitNums(matches[1].str());
        elfNums = splitNums(matches[2].str());

        score += getScore(winningNums, elfNums);
    }

    cout << "Overall score is: " << score << endl;
    return 0;
}

vector<int> splitNums(const string &numStr) {
    vector<int> nums;
    regex num(R"((?:\s?(\d{1,2})\s?))");
    smatch matches;
    string::const_iterator strIter = numStr.begin();

    while(regex_search(strIter, numStr.end(), matches, num)) {
        nums.push_back(stoi(matches[1]));
        strIter = matches[0].second;
    }

    return nums;
}

int getScore(const vector<int> &winningNumbers, const vector<int> &elfNumbers) {
    int score = 0;

    for(auto num : elfNumbers) {
        if(find(winningNumbers.begin(), winningNumbers.end(), num) != winningNumbers.end()) {
            score = score ? score * 2 : 1;
        }
    }

    return score;
}