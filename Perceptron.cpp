#include "Perceptron.hpp"

Perceptron::Perceptron(int max_iter=10, int n_iter=5, std::string error="mae", double tol=1e-3, double lr=0.1, int random_state=0, bool verbose=false){
    this->max_iter = max_iter;
    this->n_iter = n_iter;
    this->error = error;
    this->tol = tol;
    this->lr = lr;
    this->random_state = random_state;
    this->tot_iter = 1;
    this->verbose = verbose;
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
        this->w[i] = ((double)rand()/(double)(RAND_MAX));
    }
    // bias starting negative
    this->bias = -1*((double)rand()/(double)(RAND_MAX));
}

double Perceptron::dot_product(std::vector<double>X){
    double activation = 0;

    for (int i=0; i<X.size(); i++){
        activation += (this->w[i]*X[i]);
    }
    
    return activation;
}

int Perceptron::step_function(double y_){
    return int(y_ >= 0);
}

// Update the weights according to the output
void Perceptron::update_weights(std::vector<std::vector<double>>X, std::vector<double>y_, std::vector<double>y){
    int output;
    for (int i=0; i<y.size(); i++){
        output = step_function(y_[i]);
        // Different output, update the weights
        if (output != y[i]){
            for (int j=0; j<this->w.size(); j++){
                // attribute j of data at position i
                this->w[j] = this->w[j] + (this->lr*X[i][j]*(output-y[i]));
            }
            this->bias = this->bias + (this->lr*(-1)*(output-y[i]));
        }
    }
}

void Perceptron::fit(std::vector<std::vector<double>>X, std::vector<double>y){
    // Normalize the features for X and y


    // Initialize weights according to the number of features
    this->initialize_weights(X[0].size());

    // Data necessary for compute the step function and the error
    double data_activation, e=0;

    std::vector<double> predictions(y.size(), 0);
    // index for current data
    int index;
    // Stores the number of errors lesser than the tolerance
    int consecutive_errors=0;

    while (max_iter--){
        data_activation = 0;
        index = 0;
        for (auto data: X){
            data_activation = (this->dot_product(data)+bias);
            predictions[index] = data_activation;
            // COMPUTE HERE THE STEP FUNCTION
        }

        // Computes the error
        if (this->error == "mae"){
            e = mae(predictions, y);
        }
        else if (this->error == "mse"){
            e = mse(predictions, y);
        }
        // rmse
        else{
            e = rmse(predictions, y);
        }

        // Tolerance greather than current error
        if (e < this->tol){
            consecutive_errors ++;
        }
        // Reset consecutive erros
        else{
            consecutive_errors = 0;
        }

        // Check if it can stop before goes to the next iteration
        if (consecutive_errors < this->n_iter){
            // Update weights
            this->update_weights(X, predictions, y);
        }

        this->tot_iter ++;
    }
}

int Perceptron::predict(){
    
}