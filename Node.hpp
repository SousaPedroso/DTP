#include <string>
#include <variant>

class Node{
    private:
        std::string label;
        // Acceptable types for value
        std::variant<double, long long, std::string, char, bool> value;
    public:
        Node(std::string label, std::variant<double, long long, std::string, char, bool> value);
        ~Node();
        std::string get_label();
};