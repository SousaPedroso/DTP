#include "Node.hpp"
#include "error.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <stack>
#include <utility>

class DecisionTree{
    private:
        int n_features, n_classes;
        std::string criterion, target_name;
        Node* tree;
        std::vector<std::string> feature_names;
        // Store the feature nodes to merge the edge and a feature node
        std::stack<Node> features;

        std::map<multitype, std::map<multitype, int>> get_values(std::vector<multitype> sample, std::vector<multitype> classes);
        // Get the classes for each attribute
        double entropy(std::map<multitype, std::map<multitype, int>>values, int samples);
        double gini(std::map<multitype, std::map<multitype, int>>values, int samples);
        double gain(double entropy1, double entropy2);
    public:
        DecisionTree(std::string criterion);
        void names(std::vector<std::string>feature_names, std::string target_name);
        std::vector<std::string> get_features();
        void fit(std::vector<std::vector<multitype>>X, std::vector<multitype>y);
        multitype predict(std::vector<multitype>X);
        std::vector<multitype> predict(std::vector<std::vector<multitype>>X);
        Node* get_tree();
};