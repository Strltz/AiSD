#include <iostream>
#include <queue>
#include <string>
#include <regex>

class BSTC {
    struct Node {
        long long key;
        std::string value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
    };

    Node* root = nullptr;

    static void zag(Node* x) {
        if (Node* parent = x->parent) {
            x->parent = parent->parent;
            if (parent->parent) {
                if (parent->parent->left == parent) {
                    parent->parent->left = x;
                }
                else {
                    parent->parent->right = x;
                }
            }
            parent->right = x->left;
            if (x->left) {
                x->left->parent = parent;
            }
            x->left = parent;
            parent->parent = x;
        }
    }

    static void zig(Node* x) {
        if (Node* parent = x->parent) {
            x->parent = parent->parent;
            if (parent->parent) {
                if (parent->parent->left == parent) {
                    parent->parent->left = x;
                }
                else {
                    parent->parent->right = x;
                }
            }
            parent->left = x->right;
            if (x->right) {
                x->right->parent = parent;
            }
            x->right = parent;
            parent->parent = x;
        }
    }

    void splay(Node* x) {
        if (!x) {
            return;
        }
        while (x->parent) {
            Node* parent = x->parent;
            Node* grandparent = parent->parent;
            if (!grandparent) {
                if (parent->left == x) zig(x);
                else zag(x);
            }
            else if (grandparent->left == parent && parent->left == x) {
                zig(parent);
                zig(x);
            }
            else if (grandparent->right == parent && parent->right == x) {
                zag(parent);
                zag(x);
            }
            else if (grandparent->left == parent && parent->right == x) {
                zag(x);
                zig(x);
            }
            else if (grandparent->right == parent && parent->left == x) {
                zig(x);
                zag(x);
            }
        }
        root = x;
    }

public:
    void add(const long long key, const std::string& value) {
        if (!root) {
            root = new Node{ key, value };
            return;
        }
        auto node = new Node{ key, value };
        Node* projection = root;
        Node* parent = nullptr;
        while (projection) {
            parent = projection;
            if (key > projection->key) {
                projection = projection->right;
            }
            else if (key < projection->key) {
                projection = projection->left;
            }
            else {
                if (value == projection->value && key == projection->key) {
                    splay(projection);
                    throw std::runtime_error("error\n");
                }
            }
        }
        node->parent = parent;
        if (key > parent->key) {
            parent->right = node;
        }
        else if (key < parent->key) {
            parent->left = node;
        }
        splay(node);
    }

    Node* search(const long long key) {
        Node* projection = root;
        Node* result = nullptr;
        Node* prev = nullptr;
        while (projection) {
            if (projection->key == key) {
                splay(projection);
                result = projection;
                return result;
            }
            prev = projection;
            projection = (projection->key > key) ? projection->left : projection->right;
        }
        splay(prev);
        return result;
    }

    void set(const long long key, const std::string& value) {
        Node* projection = root;
        Node* prev = nullptr;
        while (projection) {
            if (projection->key == key) {
                projection->value = value;
                splay(projection);
                return;
            }
            prev = projection;
            projection = (projection->key > key) ? projection->left : projection->right;
        }
        splay(prev);
        throw std::runtime_error("error\n");
    }

    std::pair<long long, std::string> min() {
        if (!root) throw std::runtime_error("error\n");
        Node* projection = root;
        while (projection->left) {
            projection = projection->left;
        }
        splay(projection);
        std::pair<long long, std::string> result = std::make_pair(projection->key, projection->value);
        return result;
    }

    std::pair<long long, std::string> max() {
        if (!root) throw std::runtime_error("error\n");
        Node* projection = root;
        while (projection->right) {
            projection = projection->right;
        }
        splay(projection);
        std::pair<long long, std::string> result = std::make_pair(projection->key, projection->value);
        return result;
    }

    void deleteNode(long long key) {
        if (!root) {
            throw std::runtime_error("error\n");
        }
        Node* projection = root;
        Node* prev = nullptr;
        while (projection) {
            if (projection->key == key) break;
            prev = projection;
            projection = (projection->key > key) ? projection->left : projection->right;
        }
        if (!projection) {
            splay(prev);
            throw std::runtime_error("error\n");
        }
        if (!projection->parent && !projection->left && !projection->right) {
            root = nullptr;
            return;
        }
        splay(projection);

        Node* rootleft = root->left;
        Node* rootright = root->right;
        if (!rootleft) {
            root = rootright;
            root->parent = nullptr;
            return;
        }
        if (!rootright) {
            root = rootleft;
            root->parent = nullptr;
            return;
        }
        root->left = nullptr;
        root->right = nullptr;
        root = rootleft;
        root->parent = nullptr;
        Node* max = root;
        while (max->right) {
            max = max->right;
        }
        splay(max);
        root->right = rootright;
        root->right->parent = root;
    }

    void print(std::ostream& out) const {
        if (!root) {
            out << "_\n";
            return;
        }
        out << "[" << root->key << " " << root->value << "]\n";
        std::deque<Node*> q;
        int indexlast = -1;
        if (root->left) {
            q.push_back(root->left);
            indexlast = 0;
        }
        if (root->right) {
            if (!root->left) q.push_back(nullptr);
            q.push_back(root->right);
            indexlast = 1;
        }
        int indexlastbef = indexlast;
        int levelSize = 2;
        while (indexlast != -1) {
            indexlast = -1;
            int tr = 0;
            for (auto visiting : q) {
                if (visiting) {
                    if (visiting->left) indexlast = tr * 2;
                    if (visiting->right) indexlast = tr * 2 + 1;
                }
                ++tr;
            }
            int checker = -1;
            for (int i = 0; i <= indexlastbef; ++i) {
                Node* visiting = q.front();
                q.pop_front();
                if (checker == indexlast) {
                    out << (visiting ? "[" + std::to_string(visiting->key) + " " + visiting->value + " " + std::to_string(visiting->parent->key) + "] " : "_ ");
                }
                else {
                    out << (visiting ? "[" + std::to_string(visiting->key) + " " + visiting->value + " " + std::to_string(visiting->parent->key) + "] " : "_ ");
                    q.push_back((visiting ? visiting->left : nullptr));
                    ++checker;
                    if (checker == indexlast) continue;
                    q.push_back((visiting ? visiting->right : nullptr));
                    ++checker;
                }
            }
            if (indexlastbef < levelSize - 1) {
                for (int j = indexlastbef; j < levelSize - 1; ++j) {
                    out << "_ ";
                }
            }
            out << "\n";
            if (indexlast == -1) return;
            levelSize *= 2;
            indexlastbef = indexlast;
        }
    }
};

int main() {
    std::vector<TheVertex> BinarySearchTree;
    std::string str_enter;
    bool is_prev_line_empty = false;
    TheVertex* root = new TheVertex(0, "");
    int count_vertex = 0;
    while (std::getline(std::cin, str_enter)) {
        if (str_enter.empty() && is_prev_line_empty) {
            break;
        }
        else if (str_enter.empty()) {
            is_prev_line_empty = true;
            continue;
        }
        else
        {
            is_prev_line_empty = false;
            std::vector<std::string> this_line = split_space(str_enter);

            if (this_line[0] == "add" && this_line.size() == 3) {
                std::string ret_add = "";
                if (count_vertex != 0) {
                    ret_add = add_(&root, std::stoll(this_line[1]), this_line[2]);
                }
                else {
                    root = new TheVertex(std::stoll(this_line[1]), this_line[2]);
                }
                if (ret_add != "error") {
                    ++count_vertex;
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "set" && this_line.size() == 3) {
                if (count_vertex != 0) {
                    set_(&root, std::stoll(this_line[1]), this_line[2]);
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "delete" && this_line.size() == 2) {
                if (count_vertex != 0) {
                    std::string ret_del = delete_(&root, std::stoll(this_line[1]));
                    if (ret_del != "error") {
                        --count_vertex;
                    }
                    else {
                        std::cout << "error" << std::endl;
                    }
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "min" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    min_(&root);
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "max" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    max_(&root);
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "print" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    if (count_vertex == 1) {
                        std::cout << '[' << root->the_key << ' ' << root->the_value << ']' << std::endl;
                    }
                    else {
                        print_(root, count_vertex);
                    }
                }
                else {
                    std::cout << "_" << std::endl;
                }
            }
            else if (this_line[0] == "search" && this_line.size() == 2) {
                search_(&root, std::stoll(this_line[1]));
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
    }
}