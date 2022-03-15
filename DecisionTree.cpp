#include "DecisionTree.hpp"

DecisionTree::DecisionTree(std::string criterion){
    this->criterion = criterion;
    this->n_classes = 0;
}

std::map<multitype, std::map<multitype, int>> DecisionTree::get_values(std::vector<multitype> sample, std::vector<multitype> classes){
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

void DecisionTree::names(std::vector<std::string>feature_names, std::string target_name){
    this->target_name = target_name;
    this->feature_names = feature_names;
    this->n_features = feature_names.size();
}

std::vector<std::string> DecisionTree::get_features(){
    return this->feature_names;
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
        // All values are equal, get the first one
        Node leave = Node(target_name, this->n_features, y[0]);
        this->features.push(leave);
        return ;
    }

    if (this->criterion == "entropy"){
        y_dispersion = this->entropy(y_classes, y.size());
    }
    else{
        y_dispersion = this->gini(y_classes, y.size());
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
            feature_dispersion = this->gini(y_classes, y.size());
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
    Node feature_gain_node = Node(this->feature_names[index_max_gain], index_max_gain, -1);

    if (this->tree == NULL){
        this->tree = &feature_gain_node;
    }
    else {
        features.push(feature_gain_node);
    }

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
        index ++;
    }
    // Get the targets associated to next fit
    std::map<multitype, std::map<multitype, int>> feature_classes = this->get_values(X[index_max_gain], y);

    // Split the data according to the indices for solve the fit
    // for expand the tree for each type of attribute
    for (auto feature_value: features_indices){
        // Get the data associated with the feature
        std::vector<std::vector<multitype>>splitted_X = {{}};
        std::vector<multitype>splitted_y = {};
        // index of current data
        index = 0;
        // Get the indices containing the features, group the data and continues splitting
        for (auto data: X){
            // Get the values for each data at a certain index
            for (auto feature_index: feature_value.second){
                splitted_X[splitted_X.size()-1].push_back(data[feature_index]);
            }
            // Check Y associated with the feature
            if (feature_classes[feature_value.first].find(y[index]) != feature_classes[feature_value.first].end()){
                splitted_y.push_back(y[index]);
            }
            index ++;
        }
        // Solve the problem for the next attributes and values
        // It is considered as a node, but it is the edge between two different attributes
        Node edge = Node(feature_gain_node.get_label(),
                feature_gain_node.get_index(), feature_value.first);

        // Edge for a feature
        feature_gain_node.set_adjacent(edge);
        this->fit(splitted_X, splitted_y);
        // Update with the results for each depth
        edge.set_adjacent(this->features.top());
        // Remove the element
        this->features.pop();
    }
}

multitype DecisionTree::predict(std::vector<multitype>X){
    if (this->tree == NULL){
        std::cout<< "Model not trained"<< std::endl;
        return -1;
    }
    else {
        int index = 0;
        // Goes through the tree according to the index
        Node root = *this->tree;
        while (true){
            multitype X_value = X[root.get_index()];
            for (auto feature_values: root.get_adjacents()){
                if (feature_values.get_value() == X_value){
                    root = feature_values;
                    break;
                }
            }
            // Check if it is a leave
            if (root.get_index() == this->n_features){
                return root.get_value();
            }
        }
    }
}

std::vector<multitype> DecisionTree::predict(std::vector<std::vector<multitype>>X){
    std::vector<multitype> predictions;
    if (this->tree == NULL){
        std::cout<< "Model not trained"<< std::endl;
        return {};
    }
    for (auto data: X){
        multitype output = this->predict(data);
        predictions.push_back(output);
    }
    return predictions;
}

Node* DecisionTree::get_tree(){
    return this->tree;
}