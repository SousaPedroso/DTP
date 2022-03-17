#include <sstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split_string(std::string line, const char delimiter);
std::vector<std::string> split_string(std::string line, std::string delimiter);
std::vector<std::vector<std::string>> transpose(std::vector<std::vector<std::string>>m);