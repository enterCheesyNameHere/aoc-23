#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex> // I would parse manually but I'm lazy

#define MAXRED 12
#define MAXGREEN 13
#define MAXBLUE 14

using namespace std;


const string PATH = getenv("SOURCEDIR");

int main() {
    ifstream FInput(PATH + "/input.txt");
    smatch match;
    int sum = 0;

    // Loop through each line
    while(!FInput.eof()) {
        string line;
        getline(FInput, line);
        int gameID ;
        string gameData;


        // Parse the line
        regex IDexp(R"(Game (\d{1,3}): ((?:(?:\d{1,3} \w{3,5},?\s?){1,3};?\s?)+))");
        if(regex_search(line, match, IDexp)) {
            gameID = stoi(match[1]);
            gameData = match[2];
        }

        // Grab individual round data
        vector<string> rounds;
        regex roundexp(R"(((?:\d{1,3} \w{3,5},?\s?){1,3}))");
        while(regex_search(gameData, match, roundexp)) {
            rounds.push_back(match[1]);
            gameData = match.suffix().str();
        }


        // Get shape data from each round and test if its possible
        // Map will contain a color and the highest count of it  in the list
        map<string, int> cubeData;
        regex cubeexp(R"((\d{1,3}) (\w{3,5}),?\s?)");
        for(auto &round : rounds) {
            while(regex_search(round, match, cubeexp)) {
                if (cubeData.find(match[2]) == cubeData.end()) {
                    cubeData[match[2]] = stoi(match[1]);
                } else {
                    if (cubeData.at(match[2]) < stoi(match[1])) {
                        cubeData[match[2]] = stoi(match[1]);
                    }
                }
                round = match.suffix().str();
            }
        }

        if (cubeData.at("red") > MAXRED ||
            cubeData.at("green") > MAXGREEN ||
            cubeData.at("blue") > MAXBLUE) {
            cout << line;
            cout << "Game " << gameID << " is impossible" << endl;
            continue;
        }

        cout << line;
        cout << "Game " << gameID << " is possible" << endl;
        sum += gameID;
    }

    cout << "Sum of possible game IDs: " << sum << endl;
    return 0;
}