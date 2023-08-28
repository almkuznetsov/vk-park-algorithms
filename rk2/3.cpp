#include <unordered_set>
#include <string>
#include <iostream>

struct Node {
    std::string product_name;
    int color;
    int size;
    bool operator==(const Node& r) const { 
        return product_name == r.product_name &&
           color == r.color &&
           size == r.size;  
    }
};


namespace std {
    template <>
    struct hash<Node> {
        size_t operator()(const Node& node) const {
            size_t result = 17;
            result = result * 31 + hash<string>()(node.product_name);
            result = result * 31 + hash<int>()(node.color);
            result = result * 31 + hash<int>()(node.size);
            return result;
        }
    };
}

int main() {
    std::unordered_set<Node> ht;
    char operation = '\0';
   std::string product_name;
   int color = 0;
   int size = 0;
   while (std::cin >> operation >> product_name >> color >> size) {
    Node node{product_name, color, size};
    switch (operation)
    {
    case '+':
        ht.insert(node);
            std::cout << "OK" << std::endl;
        break;
    case '-':
        if (ht.erase(node)) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
        break;
    case '?':
        std::cout << (ht.count(node) ? "OK" : "FAIL") << std::endl;
        break;
    default:
        break;
    }
   }
    return 0;

}

