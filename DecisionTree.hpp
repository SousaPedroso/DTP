#include "Node.hpp"
#include "error.hpp"
#include <cmath>
#include <map>
#include <utility>
#include <vector>

// Define variant to avoid repetition of term
#define multitype std::variant<double, long long, std::string, char, bool>

class DecisionTree{
    private:
        int n_features, n_classes;
        std::string criterion;

        std::map<multitype, std::map<multitype, int>> get_values(std::vector<multitype> sample, std::vector<multitype> classes);
        double entropy(std::map<multitype, int> values);
        double gini();
        double gain(double entropy1, double entropy2);
    public:
        DecisionTree(std::string criterion);
        void fit(std::vector<std::vector<multitype>>X, std::vector<multitype>y);
        multitype predict(std::vector<multitype>X);
        multitype predict(std::vector<std::vector<multitype>>X);
}