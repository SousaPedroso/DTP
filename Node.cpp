#include "Node.hpp"

Node::Node(std::string label, int index, std::string value){
    this->label = label;
    this->index = index; // Stores the index, considering the data containing it
    this->value = value;
}

// Destroys the node
Node::~Node() = default;

std::string Node::get_label(){
    return this->label;
}

int Node::get_index(){
    return this->index;
}

std::string Node::get_value(){
    return this->value;
}

void Node::set_adjacent(Node* no){
    this->adjacents.push_back(no);
}

std::vector<Node*> Node::get_adjacents(){
    return this->adjacents;
}