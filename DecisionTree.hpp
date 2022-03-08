#include "Node.hpp"
#include "error.hpp"
#include <cmath>
#include <map>
#include <vector>

class DecisionTree{
    private:
        int n_features, n_classes;
        std::string criterion;

        std::map<std::variant<double, long long, std::string, char, bool>, int> get_values(std::vector<std::variant<double, long long, std::string, char, bool>> sample);
        double entropy(std::map<std::variant<double, long long, std::string, char, bool>, int> values);
        double gini();
    public:
        DecisionTree(std::string criterion);
        void fit(std::vector<std::vector<std::variant<double, long long, std::string, char, bool>>>X, std::vector<std::variant<double, long long, std::string, char, bool>>y);
}