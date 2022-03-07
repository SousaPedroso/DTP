#include "Node.hpp"

Node::Node(std::string label, std::variant<double, long long, std::string, char, bool> value){
    this->label = label;
    this->value = value;
}

// Destroys the node
Node::~Node() = default;

std::string Node::get_label(){
    return this->label;
}
