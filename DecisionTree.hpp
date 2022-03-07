#include "Node.hpp"
#include "error.hpp"

class DecisionTree{
    private:
        int n_features, n_classes;
        std::string criterion;

    public:
        DecisionTree(std::string criterion);
        double entropy();
        double gini();
        void fit();
}