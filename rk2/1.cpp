#include <iostream>
#include <stack>

template <typename T>
struct DefaultComparator {
    bool operator()(const T &l, const T &r) const {
        if (l < r) 
            return true;
        else 
            return false;
    }
};

template <typename Key, typename Value, typename Comparator = DefaultComparator<Key> >
class BinaryTree {
        struct Node {
        Node(const Key& k) : key(k), value(0), left(nullptr), right(nullptr) {
        }

        Key key;
        Value value;
        Node *left;
        Node *right;
        };
    private:
    Node *root;
    Comparator comp;
    public:
    BinaryTree() {
        comp = Comparator();
        root = nullptr;
    }
    ~BinaryTree(){
        if (root == nullptr) {
            return;
        }
        std::stack<Node*> stack1;
        std::stack<Node*> stack2;
        Node *cur = root;
        stack1.push(cur);
        while (!stack1.empty())
        {
            cur = stack1.top();
            stack1.pop();
            if (cur != nullptr){
                stack2.push(cur);
                if (cur->left != nullptr) {
                    stack1.push(cur->left);
                }
                if (cur->right != nullptr) {
                    stack1.push(cur->right);
                }
            }
        }
        while (!stack2.empty()) {
            cur = stack2.top();
            stack2.pop();
            delete cur;
        }
    }
    void add(const Key &key) {
        if (root == nullptr) {
            root = new Node(key);
            return;
        }
        Node *cur = root;
        while (true) {
            if (comp(key, cur->key)) {
                if (cur->left == nullptr) {
                    cur->left = new Node(key);
                    return;
                }
                cur = cur->left;
            } else {
                if (cur->right == nullptr) {
                    cur->right = new Node(key);
                    return;
                }
                cur = cur->right;
            }
        }
    }

    bool checkSameInOrder() {
        if (root == nullptr) {
            return true;
        }
        std::stack<Node*> q;
        Node *temp = this->root;
        int rootKey = temp->key;
        while (temp != nullptr || !q.empty())
        {
            while (temp != nullptr){
                q.push(temp);
                temp = temp->left;
            }
            temp = q.top();
            q.pop();
            if (temp->key != rootKey)
                return false;
            temp = temp->right;
        }
        return true;
    }
};

int main() {
    BinaryTree<int, int> bt;
    int k = 0;
    while (std::cin >> k) {
        bt.add(k);
    }
    std::cout << bt.checkSameInOrder() << std::endl;
    return 0;
}