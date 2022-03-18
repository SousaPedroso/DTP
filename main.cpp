#include "DecisionTree.hpp"
#include "Perceptron.hpp"
#include "utils.hpp"
#include "encoder.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <limits>

#define endLine '\n'

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
    std::string answer = "";

    std::cout<< "\t This program accepts a file as input for both training and predict."<< endLine;
    std::cout<< "\t You can pass a relative path for this, like data/sample.in"<< endLine;
    std::cout<< endLine;
    std::cout<< "Are you ready?Type anything: ";

    std::getline(std::cin, answer);

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

    if (method == "1"){
        DecisionTree decision_tree = DecisionTree("entropy");
        // Receive the data for prepare the decision_tree
        std::string target_feature = features.back();
        features.pop_back();
        // Remove column 'name'
        features.erase(features.begin(), features.begin()+1);
        decision_tree.names(features, target_feature);
        // Fit the algorithm according to the data passed
        std::vector<std::vector<std::string>>X;
        std::vector<std::string>y;

        // Get the data
        while (true){
            // read data feature
            std::string feature_value;

            if (target_file.eof()){
                break;
            }

            // get the feature values
            X.push_back({});
            // name column will not be inserted
            target_file >> feature_value;
            for (int i=0; i < decision_tree.get_features().size(); i++){
                target_file >> feature_value;
                X[X.size()-1].push_back(feature_value);
            }

            // target feature
            target_file >> feature_value;
            y.push_back(feature_value);
        }
        clear();
        std::cout<< "Starting training..."<< endLine;
        decision_tree.fit(X, y);
        std::cout<< endLine;
        std::cout<< "Model trained!"<< endLine;

        // Display the accuracy of training
        int index=0;
        double acc=0;
        for (auto data: X){
            acc += int(decision_tree.predict(data) == y[index]);
            index ++;
        }
        std::cout<< endLine;
        acc /= index;
        std::cout<< "Accuracy for "<<target_feature<< ": "<< acc*100<< "%"<< endLine;

        std::cout<< "Type the filename to the Decision Tree predict: "<< endLine;
        std::cin>> filename;

        // Keep checking existing file
        while (!fs::exists(filename)){
            clear();
            std::cout<< "Filename "<< filename << " does not exist. Type again the filename: ";
            std::cin>> filename;
        }
        std::ifstream predict_file;
        fs::path filepath = filename;
        predict_file.open(filename);
        
        // Get the names
        std::vector<std::string> names;
        // features data
        std::vector<std::vector<std::string>>X_;

        // Get the data
        while (true){
            // read data feature
            std::string feature_value;

            if (predict_file.eof()){
                break;
            }
            // name column will not be inserted
            predict_file >> feature_value;
            names.push_back(feature_value);
            X_.push_back({});
            for (int i=0; i < features.size(); i++){
                predict_file >> feature_value;
                // get the encoding for this feature
                X_[X_.size()-1].push_back(feature_value);
            }
        }

        // Get the root for the tree built
        std::vector<std::string>y_ = decision_tree.predict(X_);

        clear();
        for (int i=0; i<names.size(); i++){
            std::cout<< target_feature<< " for "<< names[i]<< ": "<< y_[i]<< endLine;
        }

    }
    // Perceptron
    else {
        Perceptron perceptron = Perceptron(true, 20);
        // Receive the data for prepare the perceptron
        
        std::string target_feature = features.back();
        features.pop_back();
        // Get the number of features to encode each one

        std::vector<std::string> target_data;
        // Group the data for feature (ignoring column 'name')
        std::vector<std::vector<std::string>> feat_data(features.size()-1, std::vector<std::string>{});
        // Get the data
        while (true){
            // read data feature
            std::string feature_value;

            if (target_file.eof()){
                break;
            }
            // name column will not be inserted
            target_file >> feature_value;
            for (int i=0; i < features.size()-1; i++){
                target_file >> feature_value;
                feat_data[i].push_back(feature_value);
            }
            // target feature
            target_file >> feature_value;
            target_data.push_back(feature_value);
        }

        std::vector<std::vector<double>>X_t;
        // Stores the encoder for each feature
        std::vector<std::map<std::string, int>> features_encoding;
        // a single encoder for each feature
        std::pair<std::vector<double>, std::map<std::string, int>> feat_encoding;

        // Encode the features for fit perceptron
        for (auto feat_column: feat_data){
            feat_encoding = integer_encoding(feat_column);
            // Stores the column encoded and a map for this encoding
            X_t.push_back(feat_encoding.first);
            features_encoding.push_back(feat_encoding.second);
        }
        // Encode y data
        std::map<std::string, int> y_encoding;
        feat_encoding = integer_encoding(target_data);
        std::vector<double>y = feat_encoding.first;
        y_encoding = feat_encoding.second;

        // Transpose X to contains rows of features, instead rows of just one feature
        std::vector<std::vector<double>>X(X_t[0].size(), std::vector<double>(X_t.size(), 0));

        for (int i=0; i<X_t.size(); i++){
            for (int j=0; j<X_t[0].size(); j++){
                X[j][i] = X_t[i][j];
            }
        }

        clear();
        std::cout<< "Starting training..."<< endLine;
        perceptron.fit(X, y);
        std::cout<< endLine;
        std::cout<< "Model trained!"<< endLine;
        std::cout<< endLine;
        std::cout<< "Performance on training: "<< endLine;

        // Display the accuracy of training
        int index=0;
        double acc=0;
        for (auto data: X){
            acc += int(perceptron.predict(data)==y[index]);
            index ++;
        }
        std::cout<< endLine;
        acc /= index;
        std::cout<< "Accuracy for "<<target_feature<< ": "<< acc*100<< "%"<< endLine;

        std::cout<< "Type the filename to the Perceptron predict: "<< endLine;
        std::cin>> filename;

        // Keep checking existing file
        while (!fs::exists(filename)){
            clear();
            std::cout<< "Filename "<< filename << " does not exist. Type again the filename: ";
            std::cin>> filename;
        }
        std::ifstream predict_file;
        fs::path filepath = filename;
        predict_file.open(filename);

        // Get the names
        std::vector<std::string> names;
        // features data
        std::vector<std::vector<double>>X_;

        // Get the data
        while (true){
            // read data feature
            std::string feature_value;

            if (predict_file.eof()){
                break;
            }
            // name column will not be inserted
            predict_file >> feature_value;
            names.push_back(feature_value);
            X_.push_back({});
            for (int i=0; i < features.size()-1; i++){
                predict_file >> feature_value;
                // get the encoding for this feature
                X_[X_.size()-1].push_back(features_encoding[i][feature_value]);
            }
        }
        // predict the output
        std::vector<int>y_ = perceptron.predict(X_);

        clear();
        std::string label_y;
        for (int i=0; i<y_.size(); i++){
            // Get in the map what is the output
            for (auto label: y_encoding){
                if (label.second == y_[i]){
                    label_y = label.first;
                }
            }
            std::cout<< target_feature<< " for "<< names[i]<< ": "<< label_y<< endLine;
        }
    }

    return 0;
}