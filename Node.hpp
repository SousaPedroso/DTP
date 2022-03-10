#include <string>
#include <variant>
#include <vector>

class Node{
    private:
        std::string label;
        // Acceptable types for value
        std::variant<double, int,  long long, std::string, char, bool> value;
        // Adjacents
        std::vector<Node> adjacents;
        // Index to track the values coming to decision tree and goes through
    public:
        Node(std::string label, std::variant<double, int,  long long, std::string, char, bool> value);
        ~Node();
        std::string get_label();
        void set_adjacent(Node no);
};