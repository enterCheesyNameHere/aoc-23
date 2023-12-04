#include <iostream>
#include <filesystem>

using namespace std;

int main() {
    DAY_INPUT:
    int choice;
    cout << "What day would you like to run? (0 to exit)" << endl;
    cin >> choice;

    if(choice > 25 || choice < 0) {
        cout << "Invalid input, choose number between 0 and 25" << endl << endl;
        goto DAY_INPUT;
    }

    if(choice == 0) {
        cout << "Goodbye" << endl;
        return 0;
    }

    // I'm assuming the bin directory is in the same directory as the source file for everything
    // Kind of jank but no one else is using this so ¯\_(ツ)_/¯
    filesystem::path sourceDir = filesystem::current_path().parent_path();
    string dayDir = (string) sourceDir + '/' + char(choice + '0');
    setenv("SOURCEDIR", dayDir.c_str(), 1);

    // Make sure I've actually done that day:
    if(!filesystem::exists(dayDir)) {
        cout << "I haven't done that day yet" << endl << endl;
        goto DAY_INPUT;
    }

    string dayBinDir = dayDir + "/bin/day" + char(choice + '0');
    system(dayBinDir.c_str());

    cout << endl;
    goto DAY_INPUT; // I know how it looks
}