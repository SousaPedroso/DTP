#include "Node.hpp"
#include "error.hpp"
#include "utils.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <stack>
#include <utility>

#define endLine '\n'

class DecisionTree{
    private:
        int n_features, n_classes;
        std::string criterion, target_name;
        Node* tree = NULL;
        std::vector<std::string> feature_names;
        // Store the feature nodes to merge the edge and a feature node
        std::stack<Node*> features;

        std::map<std::string, std::map<std::string, int>> class_association(std::vector<std::string> sample, std::vector<std::string> classes);
        // Get the distribution of the target data
        std::map<std::string, int> c_distribution(std::vector<std::string> classes);
        double entropy_S(std::map<std::string, int>values, int samples);
        double entropy_a(std::map<std::string, std::map<std::string, int>>values, int samples);
        double gini_S(std::map<std::string, int>values, int samples);
        double gini_a(std::map<std::string, std::map<std::string, int>>values, int samples);
        double gain(double set, double attribute);
    public:
        DecisionTree(std::string criterion);
        ~DecisionTree();
        void names(std::vector<std::string>feature_names, std::string target_name);
        std::vector<std::string> get_features();
        void fit(std::vector<std::vector<std::string>>X, std::vector<std::string>y);
        std::string predict(std::vector<std::string>X);
        std::vector<std::string> predict(std::vector<std::vector<std::string>>X);
        Node* get_tree();
};