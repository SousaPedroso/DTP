#include "Perceptron.hpp"

Perceptron::Perceptron(int max_iter=10, int n_iter=5, std::string error="mae", double tol=1e-3, double lr=0.1, int random_state=0){
    this->tol = tol;
    this->max_iter = max_iter;
    this->error = error;
    this->n_iter = n_iter;
    this->random_state = random_state;
}

void Perceptron::initialize_weights(int n){
    if (this->random_state > 0){
        // Reproducibility
        srand(random_state);
    }
    // Avoid reallocation of space
    this->w.assign(n, 0);

    for (int i=0; i<n; i++){
        // Initialize between 0 and 1
        this->w[i] = ((float)rand()/(float)(RAND_MAX));
    }
}

int Perceptron::step_function(double y_){
    return int(y_ >= 0);
}

void Perceptron::fit(std::vector<std::vector<multitype>>X, std::vector<multitype>y){

}

int Perceptron::predict(){
    
}