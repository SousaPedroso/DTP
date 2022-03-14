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