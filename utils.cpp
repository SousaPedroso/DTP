#include "utils.hpp"

std::vector<std::string> split_string(std::string line, const char delimiter){
    std::vector<std::string> strings;
    std::string content;
    // Iterate on strings
    std::stringstream str(line);

    while (std::getline(str, content, delimiter)){
        strings.push_back(content);
    }
    return strings;
}

std::vector<std::string> split_string(std::string line, std::string delimiter){
    std::vector<std::string> strings;
    // TO-DO: Separate columns consisting for string delimiter
    return strings;
}

std::vector<std::vector<std::string>> transpose(std::vector<std::vector<std::string>>m){
    int columns = m.size();
    int rows = m[0].size();

    std::vector<std::vector<std::string>> transposed_m(rows, std::vector<std::string>(columns, "0"));

    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            transposed_m[i][j] = m[j][i];
        }
    }
    return transposed_m;
}