// https://code.visualstudio.com/docs/cpp/config-msvc
// https://github.com/ocornut/imgui (biblioteca GUI- Possivelmente usar)
#include "DecisionTree.hpp"
#include "Perceptron.hpp"
#include "utils.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <limits>

#define endLine std::endl

namespace fs = std::filesystem;

// Thanks to Cat Plus Plus answer: https://stackoverflow.com/questions/6486289/how-can-i-clear-console 
#if defined _WIN32
    #include <windows.h>
    void clear(){
        COORD topLeft  = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
    }
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::cout << "\x1B[2J\x1B[H";
#elif defined (__APPLE__)
    void clear(){
        // I did not find any other solution
        system("clear");
    }
#endif

int main(){
    std::ifstream target_file; // https://www.cplusplus.com/reference/fstream/ifstream/ifstream/
    std::string line;
    std::string filename;
    std::vector<std::string> features;
    std::string method = "-1";

    std::cout<< "Type the filename to the Machine Learning models fit: ";
    std::cin>> filename;

    // Keep checking existing file
    while (!fs::exists(filename)){
        clear();

        std::cout<< "Filename "<< filename << " does not exist. Type again the filename: ";
        std::cin>> filename;
    }

    fs::path filepath = filename;
    target_file.open(filename);

    // First line (features)
    std::getline(target_file, line);

    // If ended as csv, delimiter as ','. For other extensions assumes ' '
    if (filepath.extension() == ".csv"){
        features = split_string(line, ',');
    }
    else {
        features = split_string(line, ' ');
    }

    // for (auto feature: features){
    //     std::cout<< feature<< std::endl;
    // }

    clear();
    // Ignore \n Thanks to David G answer: https://stackoverflow.com/questions/25516221/numeric-limitsmax-and-invalid-conversion-from-int-noexcept-true-to
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout<< "What Machine Learning algorithm will be used?"<< endLine;
    std::cout<< "---------------------------------------------"<< endLine;
    std::cout<< "1- Decision Tree"<< endLine;
    std::cout<< "2- Perceptron"<< endLine;
    std::cout<< "---------------------------------------------"<< endLine;
    std::getline(std::cin, method);

    // Check an error and keep until right input
    while (method != "1" && method != "2"){
        clear();
        std::cout<< "\tType a valid number!!!"<< endLine;
        std::cout<< "What Machine Learning algorithm will be used?"<< endLine;
        std::cout<< "---------------------------------------------"<< endLine;
        std::cout<< "1- Decision Tree"<< endLine;
        std::cout<< "2- Perceptron"<< endLine;
        std::cout<< "---------------------------------------------"<< endLine;
        std::getline(std::cin, method);
    }
    // Ignore \n
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}