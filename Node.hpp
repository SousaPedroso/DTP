#include <string>
#include <variant>
#include <vector>

class Node{
    private:
        int index;
        std::string label;
        std::string value;
        // Adjacents
        std::vector<Node> adjacents;
        // Index to track the values coming to decision tree and goes through
    public:
        Node(std::string label, int index, std::string value);
        ~Node();
        std::string get_label();
        int get_index();
        void set_adjacent(Node no);
        std::string get_value();
        std::vector<Node> get_adjacents();
};