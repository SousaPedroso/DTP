#include "encoder.hpp"

std::pair<std::vector<double>, std::map<std::string, int>> integer_encoding(std::vector<std::string>X){
    // Atribute integer value to each different value
    std::map<std::string, int> int_encoder;

    // Allocate the space
    std::vector<double> encoded_features(X.size(), 0);

    // Iterate through each feature and stores the last update
    int index=0, last_value=0;
    // Walk through the value for the feature
    for (auto feature_value: X){
        // Insert in the map the first the attribute was seen
        if (int_encoder.find(feature_value) == int_encoder.end()){
            int_encoder.insert(std::pair<std::string, int>(feature_value, last_value));
            last_value ++;
        }
        // Encode the feature for the vector
        encoded_features[index] = int_encoder[feature_value];
        index ++;
    }
    return std::pair<std::vector<double>, std::map<std::string, int>>(encoded_features, int_encoder);
}