#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <limits>

template<class T>
struct DefaultComparator {
    bool operator()(const T &l, const T &r) const {
        if (l < r)
            return true;
        else
            return false;
    }
};

template<class Key, class Comparator = DefaultComparator<Key> >
class BinaryTree {
    struct Node {
        Node(Key val) :
                val(val),
                left(nullptr),
                right(nullptr) {}

        Key val;
        Node *left;
        Node *right;
    };

public:
    BinaryTree() {
        comp = Comparator();
        root = nullptr;
    }

    ~BinaryTree(){
        if (root == nullptr) {
            return;
        }
        std::stack<Node*> q1;
        std::stack<Node*> q2;
        Node *temp = root;
        while (temp != nullptr || !q1.empty())
        {
            while (temp != nullptr){
                q1.push(temp);
                temp = temp->left;
            }
            temp = q1.top();
            q1.pop();
            q2.push(temp);
            temp = temp->right;
        }
        while (!q2.empty()) {
            delete q2.top();
            q2.pop();
        }
    }

    Node *add(const Key &key) {
        if (root == nullptr) {
            root = new Node(key);
            return root;
        }
        Node *temp = root;
        while (true) {
            if (comp(key, temp->val)) {
                if (temp->left == nullptr) {
                    temp->left = new Node(key);
                    break;
                }
                temp = temp->left;
            } else {
                if (temp->right == nullptr) {
                    temp->right = new Node(key);
                    break;
                }
                temp = temp->right;
            }
        }
        return root;
    }

    void in_order() {
        if (root == nullptr) {
            return;
        }
        std::stack<Node*> q;
        Node *temp = this->root;
        while (temp != nullptr || !q.empty())
        {
            while (temp != nullptr){
                q.push(temp);
                temp = temp->left;
            }
            temp = q.top();
            q.pop();
            std::cout << temp->val << " ";
            temp = temp->right;
        }
    }

    int min_depth() {
        if (root == nullptr) {
            return 0;
        }
        std::queue<std::pair<Node*, int> > q;
        int min_depth = std::numeric_limits<int>::max();
        q.push(std::make_pair(root, 1));
        while (!q.empty()) {
            Node* curr = q.front().first;
            int curr_depth = q.front().second;
            q.pop();
            if (curr->left == nullptr && curr->right == nullptr) {
                if (curr_depth < min_depth) {
                    min_depth = curr_depth;
                }
            } else {
                if (curr->left != nullptr) {
                    q.push(std::make_pair(curr->left, curr_depth + 1));
                }
                if (curr->right != nullptr) {
                    q.push(std::make_pair(curr->right, curr_depth + 1));
                }
            }
        }
        return min_depth;
    }

private:
    Node *root;
    Comparator comp;
};

int main() {
    BinaryTree<int> a;
    int temp = 0;
    while (std::cin >> temp) {
        a.add(temp);
    }
    std::cout << a.min_depth() << std:: endl;
    return 0;
}