#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include "error.hpp"

class Perceptron{
    private:
        std::vector<double> w;
        double tol, bias, lr;
        bool verbose;
        int max_iter, n_iter, random_state, tot_iter;
        std::string error;

        void initialize_weights(int n);
        void update_weights(std::vector<std::vector<double>>X, std::vector<double>y_, std::vector<double>y);
        double dot_product(std::vector<double>X);
        int step_function(double y_);

    public:
        Perceptron(bool verbose, int max_iter=10, int n_iter=5, std::string error="mae", double tol=1e-3,
                    double lr=0.1, int random_state=0);
        void fit(std::vector<std::vector<double>>X, std::vector<double>y);
        int predict(std::vector<double>X);
        std::vector<int> predict(std::vector<std::vector<double>>X);
};