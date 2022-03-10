#include "Node.hpp"

Node::Node(std::string label, std::variant<double, int, long long, std::string, char, bool> value){
    this->label = label;
    this->value = value;
}

// Destroys the node
Node::~Node() = default;

std::string Node::get_label(){
    return this->label;
}

void Node::set_adjacent(Node no){
    this->adjacents.push_back(no);
}