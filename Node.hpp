#include <string>
#include <variant>
#include <vector>

// Define variant to avoid repetition of term
#define multitype std::variant<double, int, long long, std::string, char, bool>

class Node{
    private:
        std::string label;
        // Acceptable types for value
        multitype value;
        // Adjacents
        std::vector<Node> adjacents;
        // Index to track the values coming to decision tree and goes through
    public:
        Node(std::string label, multitype value);
        ~Node();
        std::string get_label();
        void set_adjacent(Node no);
};