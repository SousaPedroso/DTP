#include <string>
#include <variant>
#include <vector>
#include "error.hpp"

#define multitype std::variant<double, int, long long, std::string, char, bool>

class Perceptron{
    private:
        std::vector<double> w;
        double tol;
        int max_iter, n_iter, random_state, tot_iter;
        std::string error;
        void initialize_weights(int n);
        int step_function(double y_);

    public:
        Perceptron(int max_iter=10, int n_iter=5, std::string error="mae", double tol=1e-3, double lr=0.1, int random_state=0);
        void fit(std::vector<std::vector<multitype>>X, std::vector<multitype>y);
        int predict();
};