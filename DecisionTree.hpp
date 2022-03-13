#include "Node.hpp"
#include "error.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <utility>

// Define variant to avoid repetition of term
#define multitype std::variant<double, int, long long, std::string, char, bool>

class DecisionTree{
    private:
        int n_features, n_classes;
        std::string criterion;
        std::vector<Node> tree;

        std::map<multitype, std::map<multitype, int>> get_values(std::vector<multitype> sample, std::vector<multitype> classes);
        // Get the classes for each attribute
        double entropy(std::map<multitype, std::map<multitype, int>>values, int samples);
        double gini(std::map<multitype, std::map<multitype, int>>values, int samples);
        double gain(double entropy1, double entropy2);
    public:
        DecisionTree(std::string criterion);
        void fit(std::vector<std::vector<multitype>>X, std::vector<multitype>y);
        multitype predict(std::vector<multitype>X);
        std::vector<multitype> predict(std::vector<std::vector<multitype>>X);
        std::vector<Node> get_tree();
};