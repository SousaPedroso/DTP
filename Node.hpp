#include <string>

class Node{
    private:
        std::string label;

    public:
        Node(std::string label);
        ~Node();
        std::string get_label();
};