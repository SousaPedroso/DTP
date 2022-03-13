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
            else{
                differences[sample[i]][classes[i]] = 0;
            }
        }
        // Attribute First time seen
        else{
            differences[sample[i]][classes[i]] = 0;
        }
    }
    return differences;
}

double DecisionTree::entropy(std::map<multitype, std::map<multitype, int>>values, int samples){
    double e=0;
    // Checks the counting of samples for a feature
    int attribute_count;

    for (auto attribute_value: values){
        attribute_count = 0;
        // Update the counting of samples for a feature
        for (auto class_value: attribute_value.second){
            attribute_count += class_value.second;
        }
        // Consider each class associated with an attribute value
        for (auto class_value: attribute_value.second){
            e += (class_value.second/attribute_count)* log2(class_value.second/attribute_count);
        }
        e += (attribute_count/samples)*(-e);
    }

    return e;
}

// Gini impurity
double DecisionTree::gini(std::map<multitype, std::map<multitype, int>>values, int samples){
    double gi=1;
    int attribute_count;

    for (auto attribute_value: values){
        attribute_count = 0;
        // Update the counting of samples for a feature
        for (auto class_value: attribute_value.second){
            attribute_count += class_value.second;
        }
        // For each possibility of class, update gini impurity [(p_i)^2]
        for (auto class_value: attribute_value.second){
            gi -= pow(class_value.second/attribute_count, 2);
        }
    }
    return gi;
}

double DecisionTree::gain(double entropy1, double entropy2){
    return entropy2 - entropy1;
}

void DecisionTree::fit(std::vector<std::vector<multitype>>X, std::vector<multitype>y){

    // Entropy/gini for the output classes
    double y_dispersion;
    double feature_dispersion;
    double feature_gain;
    // Computes the gain in execution time for the root
    double max_gain=0;
    int index_max_gain;

    std::map<multitype, std::map<multitype, int>> y_classes = this->get_values(y, y);

    // Data of one class means entropy equals 0, no dispersion (leaf)
    if (y_classes.size() == 1){
        return ;
    }

    if (this->criterion == "entropy"){
        y_dispersion = this->entropy(y_classes, y.size());
    }
    else{
        y_dispersion = this->gini();
    }
    // Index for each feature
    int index=0;
    // Entropy and gain for each attribute
    for (auto feature: X){
        std::map<multitype, std::map<multitype, int>> feature_classes = this->get_values(feature, y);
        if (this->criterion == "entropy"){
            feature_dispersion = this->entropy(y_classes, y.size());
        }
        else{
            feature_dispersion = this->gini();
        }
        feature_gain = this->gain(y_dispersion, feature_dispersion);
        if (feature_gain > max_gain){
            max_gain = feature_gain;
            index_max_gain = index;
        }
        index ++;
    }
    // Add a node for a feature
    std::string label = index_max_gain +"";
    Node feature_gain_node = Node(label, -1);
    this->tree.push_back(feature_gain_node);

    // Stores the indices for each different value
    // To proceed in DT calculating gain and the leaves
    std::map<multitype, std::vector<int>> features_indices;

    // Add a node for each value in this feature
    index = 0;
    for (auto feature_value: X[index_max_gain]){
        // Check if this value was found for iterate through the tree
        if (features_indices.find(feature_value) != features_indices.end()){
            features_indices[feature_value].push_back(index);
        }
        else{
            // Insert the first occurence of this value
            features_indices.insert(std::pair<multitype, std::vector<int>>(feature_value, {index}));
        }
    }
    // Solve the problem for the next attributes and values
    
}

multitype DecisionTree::predict(std::vector<multitype>X){
    if (this->tree.size() == 0){
        std::cout<< "Model not trained"<< std::endl;
        return -1;
    }
    else {
        // Goes through the tree according to the index
    }
}

std::vector<multitype> DecisionTree::predict(std::vector<std::vector<multitype>>X){

}

std::vector<Node> get_tree(){

}