#include "Node.hpp"

Node::Node(std::string label){
    this->label = label;
}

// Destroys the node
Node::~Node() = default;

std::string Node::get_label(){
    return this->label;
}
