#include <string>
#include <variant>
#include <vector>

// Define variant to avoid repetition of term
#define multitype std::variant<double, int, long long, std::string, char, bool>

class Node{
    private:
        int index;
        std::string label;
        // Acceptable types for value
        multitype value;
        // Adjacents
        std::vector<Node> adjacents;
        // Index to track the values coming to decision tree and goes through
    public:
        Node(std::string label, int index, multitype value);
        ~Node();
        std::string get_label();
        int get_index();
        void set_adjacent(Node no);
        multitype get_value();
        std::vector<Node> get_adjacents();
};