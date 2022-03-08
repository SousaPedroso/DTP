#include "DecisionTree.hpp"

DecisionTree::DecisionTree(std::string criterion){
    this->criterion = criterion;
    this->n_classes = 0;
}

std::map<std::variant<double, long long, std::string, char, bool>, int> get_values(std::vector<std::variant<double, long long, std::string, char, bool>> sample){
    // Stores the number of diferent classes
    std::map<std::variant<double, long long, std::string, char, bool>, int> differences;
    std::map<std::variant<double, long long, std::string, char, bool>, int>::iterator d_iterator;

    // TO-DO: Stores the index in the dataset to fast check to compute entropy

    // Computes the number of differences and saves for calculating the entropy
    for (int i=0; i< sample.size(); i++){
        d_iterator = differences.find(sample[i]);
        if (d_iterator != differences.end()){
            differences[sample[i]]++;
        }
        else{
            differences[sample[i]] = 0;
        }
    }
    return differences;
}

double DecisionTree::entropy(std::map<std::variant<double, long long, std::string, char, bool>, int> classes){
    double e=0;

    // entropy
    // Somatório da multiplicação de um atributo pelo log de quantas saídas ele resulta

    return e;
}
double DecisionTree::gini(){

}

void DecisionTree::fit(std::vector<std::vector<std::variant<double, long long, std::string, char, bool>>>X, std::vector<std::variant<double, long long, std::string, char, bool>>y){

    // Entropy/gini for the output classes
    double y_dispersion;

    std::map<std::variant<double, long long, std::string, char, bool>, int> y_classes = this->get_values(y);
    if (this->criterion == "entropy"){
        y_dispersion = this->entropy(y_classes);
    }
    else{
        y_dispersion = this->gini();
    }
}