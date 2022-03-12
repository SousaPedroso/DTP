#include "error.hpp"

double rmse(std::vector<double> y_, std::vector<double> y){
    double error=0;

    for (int i=0; i<y_.size(); i++){
        error += pow(y_[i]-y[i], 2);
    }
    error /= y.size();
    error = sqrt(error);

    return error;
}

double mse(std::vector<double> y_, std::vector<double> y){
    double error=0;

    for (int i=0; i<y_.size(); i++){
        error += pow(y_[i]-y[i], 2);
    }
    error /= y.size();

    return error;
}

double mae(std::vector<double> y_, std::vector<double> y){
    double error=0;

    for (int i=0; i<y_.size(); i++){
        error += abs(y_[i]-y[i]);
    }
    error /= y.size();

    return error;
}