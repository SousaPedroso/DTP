#include "DecisionTree.hpp"

DecisionTree::DecisionTree(std::string criterion){
    this->criterion = criterion;
    this->n_classes = 0;
}

std::map<multitype, std::map<multitype, int>> get_values(std::vector<multitype> sample, std::vector<multitype, int> classes){
    // Stores the number of diferent classes, the first map is for the feature and second one to the class
    std::map<multitype, std::map<multitype, int>> differences;
    std::map<multitype, std::map<multitype, int>>::iterator d_iterator;

    // TO-DO: Stores the index in the dataset to fast check to compute entropy

    // Computes the number of differences and saves for calculating the entropy
    for (int i=0; i< sample.size(); i++){
        d_iterator = differences.find(sample[i]);
        // Already found this attribute value
        if (d_iterator != differences.end()){
            // Check if the output it is on the map
            if (d_iterator->second.find(classes[i]) != d_iterator->second.end()){
                differences[sample[i]][classes[i]]++;
            }
        }
        // Attribute First time seen
        else{
            differences[sample[i]][classes[i]] = 0;
        }
    }
    return differences;
}

double DecisionTree::entropy(std::map<multitype, int> classes){
    double e=0;

    // entropy
    // Somatório da multiplicação de um atributo pelo log de quantas saídas ele resulta

    return e;
}
double DecisionTree::gini(){

}

double DecisionTree::gain(double entropy1, double entropy2){
    return entropy2 - entropy1;
}

void DecisionTree::fit(std::vector<std::vector<multitype>>X, std::vector<multitype>y){

    // Entropy/gini for the output classes
    double y_dispersion;

    std::map<multitype, std::map<multitype, int>> y_classes = this->get_values(y, y);
    if (this->criterion == "entropy"){
        
    }
    else{
        y_dispersion = this->gini();
    }
}

multitype DecisionTree::predict(std::vector<multitype>X){

}

multitype DecisionTree::predict(std::vector<std::vector<multitype>>X){

}