#include <string>
#include <variant>
#include <vector>
#include <map>
#include <utility>

// Vector of double to facilitate fit of Perceptron
std::pair<std::vector<double>, std::map<std::string, int>> integer_encoding(std::vector<std::string>X);