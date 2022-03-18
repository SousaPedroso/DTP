#include "DecisionTree.hpp"

DecisionTree::DecisionTree(std::string criterion){
    this->criterion = criterion;
    this->n_classes = 0;
}

// Destroys the tree
DecisionTree::~DecisionTree() = default;

std::map<std::string, std::map<std::string, int>> DecisionTree::class_association(std::vector<std::string> sample, std::vector<std::string> classes){
    // Stores the number of diferent classes, the first map is for the feature and second one to the class
    std::map<std::string, std::map<std::string, int>> differences;
    std::map<std::string, std::map<std::string, int>>::iterator d_iterator;

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
                differences[sample[i]][classes[i]] = 1;
            }
        }
        // Attribute First time seen
        else{
            differences[sample[i]][classes[i]] = 1;
        }
    }
    return differences;
}

std::map<std::string, int> DecisionTree::c_distribution(std::vector<std::string> classes){
    std::map<std::string, int> distribution;

    for (auto class_value: classes){
        if (distribution.find(class_value) != distribution.end()){
            distribution[class_value] ++;
        }
        else {
            distribution[class_value] = 1;
        }
    }

    return distribution;
}

double DecisionTree::entropy_S(std::map<std::string, int>values, int samples){
    double e=0;

    for (auto target: values){
        e += -1*((double)target.second/(double)samples)*log2((double)target.second/(double)samples);
    }
    return e;
}

double DecisionTree::entropy_a(std::map<std::string, std::map<std::string, int>>values, int samples){
    double e=0, e_i;
    // Checks the counting of samples for a feature
    int attribute_count;

    for (auto attribute_value: values){
        attribute_count = 0;
        e_i=0;
        // Update the counting of samples for a feature
        for (auto class_value: attribute_value.second){
            attribute_count += class_value.second;
        }
        // Consider each class associated with an attribute value
        for (auto class_value: attribute_value.second){
            e_i += -1*((double)class_value.second/(double)attribute_count)* log2((double)class_value.second/(double)attribute_count);
        }
        e_i *= ((double)attribute_count/(double)samples);
        e += e_i;
    }

    return e;
}

// Gini impurity
double DecisionTree::gini_S(std::map<std::string, int>values, int samples){
    double gi=1;
    double p_i=0;

    for (auto target: values){
        p_i += ((double)target.second/(double)samples)*((double)target.second/(double)samples);
    }

    return gi-p_i;
}

double DecisionTree::gini_a(std::map<std::string, std::map<std::string, int>>values, int samples){
    double gi=0;
    double p_i;
    int attribute_count;

    for (auto feat_value: values){
        p_i=0;
        attribute_count=0;
        for (auto s_value: feat_value.second){
            attribute_count += s_value.second;
        }
        gi += ((double)attribute_count/(double)samples) * this->gini_S(feat_value.second, attribute_count);
    }
    return gi;
}

double DecisionTree::gain(double set, double attribute){
    return set - attribute;
}

void DecisionTree::names(std::vector<std::string>feature_names, std::string target_name){
    this->target_name = target_name;
    this->feature_names = feature_names;
    this->n_features = feature_names.size();
}

std::vector<std::string> DecisionTree::get_features(){
    return this->feature_names;
}

void DecisionTree::fit(std::vector<std::vector<std::string>>X, std::vector<std::string>y){

    // Entropy/gini for the output classes
    double y_dispersion;
    double feature_dispersion;
    double feature_gain;
    // Computes the gain in execution time for the root
    double max_gain=0;
    int index_max_gain=0;

    std::map<std::string, int> y_distribution = this->c_distribution(y);
    // Data of one class means entropy equals 0, no dispersion (leaf)
    if (y_distribution.size() == 1){
        // All values are equal, get the first one
        std::cout<< "Leaf for "<< y[0]<< endLine;
        Node* leave = new Node(target_name, this->n_features, y[0]);
        this->features.push(leave);
        return ;
    }

    if (this->criterion == "entropy"){
        y_dispersion = this->entropy_S(y_distribution, y.size());
    }
    else{
        y_dispersion = this->gini_S(y_distribution, y.size());
    }
    
    // Index for each feature
    int index=0;
    // Entropy and gain for each attribute
    std::vector<std::vector<std::string>> transposed_X = transpose(X);

    for (auto feature: transposed_X){
        std::map<std::string, std::map<std::string, int>> feature_classes = this->class_association(feature, y);
        if (this->criterion == "entropy"){
            feature_dispersion = this->entropy_a(feature_classes, y.size());
        }
        else{
            feature_dispersion = this->gini_a(feature_classes, y.size());
        }
        feature_gain = this->gain(y_dispersion, feature_dispersion);
        if (feature_gain >= max_gain){
            max_gain = feature_gain;
            index_max_gain = index;
        }
        index ++;
    }
    // Add a node for a feature
    std::string label = index_max_gain +"";
    std::cout<< "Max gain: "<<max_gain<< endLine;
    std::cout<< "Feature of max gain: "<< this->feature_names[index_max_gain]<< endLine;
    Node* feature_gain_node = new Node(this->feature_names[index_max_gain], index_max_gain, "-1");

    if (this->tree == NULL){
        this->tree = feature_gain_node;
    }
    this->features.push(feature_gain_node);

    // Stores the indices for each different value
    // To proceed in DT calculating gain and the leaves
    std::map<std::string, std::vector<int>> features_indices;

    // Add a node for each value in this feature
    index = 0;
    for (auto feature_value: transposed_X[index_max_gain]){
        // Check if this value was found for iterate through the tree
        if (features_indices.find(feature_value) != features_indices.end()){
            features_indices[feature_value].push_back(index);
        }
        else{
            // Insert the first occurence of this value
            features_indices.insert(std::pair<std::string, std::vector<int>>(feature_value, {index}));
        }
        index ++;
    }

    // Split the data according to the indices for solve the fit
    // for expand the tree for each type of attribute
    for (auto feature_value: features_indices){
        // Get the data associated with the feature
        std::vector<std::vector<std::string>>splitted_X;
        std::vector<std::string>splitted_y = {};
        // index of current data
        index = 0;
        // Get the indices containing the features, group the data and continues splitting
        for (auto feat_index: feature_value.second){
            splitted_X.push_back(X[feat_index]);
            splitted_y.push_back(y[feat_index]);
            // Remove the data for the index of the feature
            // splitted_X[splitted_X.size()-1].erase(splitted_X[splitted_X.size()-1].begin()+index_max_gain, splitted_X[splitted_X.size()-1].begin()+index_max_gain+1);
        }
        // Solve the problem for the next attributes and values
        // It is considered as a node, but it is the edge between two different attributes
        Node* edge = new Node((*feature_gain_node).get_label(),
                (*feature_gain_node).get_index(), feature_value.first);

        // Edge for a feature
        feature_gain_node->set_adjacent(edge);
        this->fit(splitted_X, splitted_y);
        // Update with the results for each depth
        edge->set_adjacent(this->features.top());
        // Remove the element
        this->features.pop();
    }
}

std::string DecisionTree::predict(std::vector<std::string>X){
    if (this->tree == NULL){
        std::cout<< "Model not trained"<< endLine;
        return "-1";
    }
    else {
        // Goes through the tree according to the index
        Node* r = this->tree;
        std::string X_value = X[r->get_index()];
        while (true){
            for (auto feature_values: r->get_adjacents()){
                // Atualizar o indice conforme o adjacente
                if (feature_values->get_value() == X_value){
                    // It is an attribute, it has just one adjacent
                    r = feature_values->get_adjacents()[0];
                    break;
                }
            }
            // Check if it is a leave
            if (r->get_index() == this->n_features){
                return r->get_value();
            }
            // Update X
            X_value = X[r->get_index()];
        }
    }
}

std::vector<std::string> DecisionTree::predict(std::vector<std::vector<std::string>>X){
    std::vector<std::string> predictions;
    if (this->tree == NULL){
        std::cout<< "Model not trained"<< endLine;
        return {};
    }
    for (auto data: X){
        std::string output = this->predict(data);
        predictions.push_back(output);
    }
    return predictions;
}

Node* DecisionTree::get_tree(){
    return this->tree;
}