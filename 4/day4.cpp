#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>

using namespace std;

string PATH = getenv("INPUTDIR");

vector<int> splitNums(const string &numStr);
int getMatches(const vector<int> &winningNumbers, const vector<int> &elfNumbers);
int getCardsCount(vector<int> &cards);

int main() {
    PATH = "../input.txt";
    ifstream FInput(PATH);
    string line;
    int score = 0;

    regex nums(R"(Card\s+\d+: ((?:\s?\d{1,2}\s?)+)\| ((?:\s?\d{1,2}\s?)+))");
    vector<string> cards;
    vector<int> cardCopies; // stores the amount of copies of each card

    for(int i = 0; getline(FInput, line); i++) {
        cardCopies.push_back(1);
        cards.push_back(line);
    }

    FInput.close();

    for(int i = 0; i < cards.size(); i++) {
        smatch matches;
        vector<int> winningNums;
        vector<int> elfNums;

        regex_search(cards[i], matches, nums);
        winningNums = splitNums(matches[1].str());
        elfNums = splitNums(matches[2].str());

        int matchesCount = getMatches(winningNums, elfNums);
        int cardScore = 0;
        for(int j = 0; j < matchesCount; j++) {
            cardScore = cardScore ? cardScore * 2 : 1;
        }
        score += cardScore;

        for(int j = i + 1; j <= i + matchesCount; j++) {
            cardCopies[j] += cardCopies[i];
        }
    }


    cout << "Overall score is: " << score << endl;
    cout << "Card count: " << getCardsCount(cardCopies) << endl;
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


int getMatches(const vector<int> &winningNumbers, const vector<int> &elfNumbers) {
    int matches = 0;

    for(auto num : elfNumbers) {
        if(find(winningNumbers.begin(), winningNumbers.end(), num) != winningNumbers.end()) {
            matches++;
        }
    }

    return matches;
}


int getCardsCount(vector<int> &cards) {
    int sum = 0;

    for(int cardCount : cards) {
        sum += cardCount;
    }

    return sum;
}