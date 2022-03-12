#include <string>
#include <variant>
#include <vector>
#include <map>
#include <utility>

#define multitype std::variant<double, int, long long, std::string, char, bool>

std::vector<int> integer_encoding(std::vector<multitype>X);