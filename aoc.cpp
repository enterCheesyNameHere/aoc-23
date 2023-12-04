#include <iostream>
#include <filesystem>

using namespace std;

int main() {
    DAY_INPUT:
    string choice;
    cout << "What day would you like to run? (0 to exit)" << endl;
    getline(cin, choice);

    if(stoi(choice) > 25 || stoi(choice) < 0) {
        cout << "Invalid input, choose number between 0 and 25" << endl << endl;
        goto DAY_INPUT;
    }

    if(stoi(choice) == 0) {
        cout << "Goodbye" << endl;
        return 0;
    }

    // I'm assuming the bin directory is in the same directory as the source file for everything
    // Kind of jank but no one else is using this so ¯\_(ツ)_/¯
    filesystem::path sourceDir = filesystem::current_path().parent_path();
    string dayDir = (string) sourceDir + '/' + choice;

    // Make sure I've actually done that day:
    if(!filesystem::exists(dayDir)) {
        cout << "I haven't done that day yet" << endl << endl;
        goto DAY_INPUT;
    }

    FILE_INPUT:
    string inputFile;
    cout << "CWD (For relative paths): " << filesystem::current_path() << endl;
    cout << "Enter an alternate input (press enter to just use the default): " << endl;
    getline(cin, inputFile);

    if (inputFile.empty()) {
        inputFile = dayDir + "/input.txt";
    }

    if (!filesystem::exists(inputFile)) {
        cout << "File " << inputFile << " does not exist" << endl << endl;
        goto FILE_INPUT;
    }

    setenv("INPUTDIR", inputFile.c_str(), 1);

    cout.fill('-');
    cout << setw(50) << left << "----Day " + choice + "" << endl;

    string dayBinDir = dayDir + "/bin/day" + choice;
    system(dayBinDir.c_str());

    cout << setw(50) << "" << endl;

    cout.fill(' ');
    goto DAY_INPUT; // I know how it looks
}