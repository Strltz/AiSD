#include <cmath>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <vector>

std::vector<std::string> split_for_functions(std::string the_string) {
    std::string func = "";
    size_t i = 0;
    for (; i < the_string.size(); ++i) {
        if (the_string[i] == ' ') {
            break;
        }
        func.push_back(the_string[i]);
    }
    int count_parts = 0;
    std::vector<std::string> parts;
    if (func == "add" || func == "set") {
        count_parts = 3;
    }
    else if (func == "search" || func == "delete") {
        count_parts = 2;
    }
    else if (func == "min" || func == "max" || func == "print") {
        count_parts = 1;
    }
    else {
        return { "error" };
    }
    std::string part_k = "";
    std::string part_v = "";
    parts.push_back(func);
    if (count_parts == 3) {
        ++i;
        for (; i < the_string.size(); ++i) {
            if (the_string[i] == ' ') {
                break;
            }
            part_k.push_back(the_string[i]);
        }
        parts.push_back(part_k);
        ++i;
        for (; i < the_string.size(); ++i) {
            part_v.push_back(the_string[i]);
        }
        parts.push_back(part_v);
    }
    else if (count_parts == 2) {
        ++i;
        for (; i < the_string.size(); ++i) {
            part_k.push_back(the_string[i]);
        }
        parts.push_back(part_k);
    }
    else {
        if (the_string.size() > func.size()) {
            return { "error" };
        }
    }

    if (parts.size() != count_parts) {
        return { "error" };
    }
    else {
        return parts;
    }
}

class TheVertex {
public:
    TheVertex(long long k, std::string v) {
        the_key = k;
        the_value = v;
        father = nullptr;
        right_child = nullptr;
        left_child = nullptr;
    }

    long long the_key;
    std::string the_value;
    TheVertex* father;
    TheVertex* right_child;
    TheVertex* left_child;

    ~TheVertex() {}
};

class TheBSPTree {
public:
    TheBSPTree() {
        root_tree = new TheVertex(0, "");
    }
    TheVertex* root_tree;
    void Zig_(TheVertex* x) {
        TheVertex* p = x->father;
        if (p) {
            x->father = p->father;
            if (p->father) {
                if (p->father->left_child == p) {
                    p->father->left_child = x;
                }
                else {
                    p->father->right_child = x;
                }
            }
            p->left_child = x->right_child;
            if (x->right_child) {
                x->right_child->father = p;
            }
            x->right_child = p;
            p->father = x;
        }
    }

    void Zag_(TheVertex* x) {
        TheVertex* p = x->father;
        if (p) {
            x->father = p->father;
            if (p->father) {
                if (p->father->left_child == p) {
                    p->father->left_child = x;
                }
                else {
                    p->father->right_child = x;
                }
            }
            p->right_child = x->left_child;
            if (x->left_child) {
                x->left_child->father = p;
            }
            x->left_child = p;
            p->father = x;
        }
    }

    void splay_(TheVertex** root, TheVertex* x) {
        if (!x) {
            return;
        }
        while (x->father) {
            TheVertex* p = x->father;
            TheVertex* g = p->father;
            if (!g) {
                if (p->left_child == x) {
                    Zig_(x);
                }
                else {
                    Zag_(x);
                }
            }
            else if (g->left_child == p && p->left_child == x) {
                Zig_(p);
                Zig_(x);
            }
            else if (g->right_child == p && p->right_child == x) {
                Zag_(p);
                Zag_(x);
            }
            else if (g->left_child == p && p->right_child == x) {
                Zag_(x);
                Zig_(x);
            }
            else if (g->right_child == p && p->left_child == x) {
                Zig_(x);
                Zag_(x);
            }
        }
        *root = x;
    }

    std::string add_(long long k, std::string v) {
        TheVertex** root = &root_tree;
        TheVertex* last_vertex = *root;
        TheVertex* new_vertex = new TheVertex(k, v);
        bool stop_search = false;
        while (!stop_search) {
            if (k > (*last_vertex).the_key) {
                if ((*last_vertex).right_child == nullptr) {
                    stop_search = true;
                    (*new_vertex).father = last_vertex;
                    (*last_vertex).right_child = new_vertex;
                    splay_(root, new_vertex);
                }
                else {
                    last_vertex = (*last_vertex).right_child;
                }
            }
            else {
                if (k == (*last_vertex).the_key) {
                    splay_(root, last_vertex);
                    return "error";
                }
                if ((*last_vertex).left_child == nullptr) {
                    stop_search = true;
                    (*new_vertex).father = last_vertex;
                    (*last_vertex).left_child = new_vertex;
                    splay_(root, new_vertex);
                }
                else {
                    last_vertex = (*last_vertex).left_child;
                }
            }
        }
        return "";
    }

    void set_(long long k, std::string v) {
        TheVertex** root = &root_tree;
        TheVertex* this_vertex = *root;
        while ((*this_vertex).the_key != k) {
            if (k > (*this_vertex).the_key) {
                if ((*this_vertex).right_child == nullptr) {
                    std::cout << "error" << std::endl;
                    splay_(root, this_vertex);
                    return;
                }
                else {
                    this_vertex = (*this_vertex).right_child;
                }
            }
            else {
                if ((*this_vertex).left_child == nullptr) {
                    std::cout << "error" << std::endl;
                    splay_(root, this_vertex);
                    return;
                }
                else {
                    this_vertex = (*this_vertex).left_child;
                }
            }
        }
        (*this_vertex).the_value = v;
        splay_(root, this_vertex);
    }

    void search_(long long k) {
        TheVertex** root = &root_tree;
        TheVertex* this_vertex = *root;
        while ((*this_vertex).the_key != k) {
            if (k > (*this_vertex).the_key) {
                if ((*this_vertex).right_child == nullptr) {
                    std::cout << "0" << std::endl;
                    splay_(root, this_vertex);
                    return;
                }
                else {
                    this_vertex = (*this_vertex).right_child;
                }
            }
            else {
                if ((*this_vertex).left_child == nullptr) {
                    std::cout << "0" << std::endl;
                    splay_(root, this_vertex);
                    return;
                }
                else {
                    this_vertex = (*this_vertex).left_child;
                }
            }
        }
        std::cout << "1 " << (*this_vertex).the_value << std::endl;
        splay_(root, this_vertex);
    }

    void min_() {
        TheVertex** root = &root_tree;
        TheVertex* this_vertex = *root;
        while ((*this_vertex).left_child != nullptr) {
            this_vertex = (*this_vertex).left_child;
        }
        std::cout << (*this_vertex).the_key << ' ' <<
            (*this_vertex).the_value << std::endl;
        splay_(root, this_vertex);
    }

    void max_() {
        TheVertex** root = &root_tree;
        TheVertex* this_vertex = *root;
        while ((*this_vertex).right_child != nullptr) {
            this_vertex = (*this_vertex).right_child;
        }
        std::cout << (*this_vertex).the_key << ' ' <<
            (*this_vertex).the_value << std::endl;
        splay_(root, this_vertex);
    }

    std::string delete_(long long k) {
        TheVertex** root = &root_tree;
        if (!(*root)) {
            return "error";
        }
        TheVertex* projection = *root;
        TheVertex* prev = nullptr;
        while (projection) {
            if (projection->the_key == k) {
                break;
            }
            prev = projection;
            projection = (projection->the_key > k) ? projection->left_child : projection->right_child;
        }
        if (!projection) {
            splay_(root, prev);
            return "error";
        }
        if (!projection->father && !projection->left_child && !projection->right_child) {
            root = nullptr;
            return "";
        }
        splay_(root, projection);

        TheVertex* rootleft = (*root)->left_child;
        TheVertex* rootright = (*root)->right_child;
        if (!rootleft) {
            *root = rootright;
            (*root)->father = nullptr;
            return "";
        }
        if (!rootright) {
            *root = rootleft;
            (*root)->father = nullptr;
            return "";
        }
        (*root)->left_child = nullptr;
        (*root)->right_child = nullptr;
        (*root) = rootleft;
        (*root)->father = nullptr;
        TheVertex* max = *root;
        while (max->right_child) {
            max = max->right_child;
        }
        splay_(root, max);
        (*root)->right_child = rootright;
        (*root)->right_child->father = *root;
        return "";
    }

    void recursive_for_print(TheVertex* node, std::vector<std::pair<TheVertex*, int>>* vec, int i) {
        vec->push_back({ node, i });
        if (node->left_child != nullptr) {
            recursive_for_print(node->left_child, vec, 2 * i + 1);
        }
        if (node->right_child != nullptr) {
            recursive_for_print(node->right_child, vec, 2 * i + 2);
        }
    }

    void sortByInt_i(std::vector<std::pair<TheVertex*, int>>& list_vertex) {
        std::sort(list_vertex.begin(), list_vertex.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });
    }

    void print_(TheVertex* root, int count_vertex) {
        std::vector<std::pair<TheVertex*, int>> list_vertex{ };
        recursive_for_print(root, &list_vertex, 0);
        sortByInt_i(list_vertex);
        std::cout << '[' << list_vertex[0].first->the_key << ' ' <<
            list_vertex[0].first->the_value << ']' << std::endl;
        int num_last_real_vertex = list_vertex[list_vertex.size() - 1].second;
        int count_levels = floor(log2(num_last_real_vertex + 1)) + 1;
        int count_for_print = pow(2, count_levels) - 1;
        int level = 1;
        int current_vert = 1;
        for (size_t i = 1; i < count_for_print; ++i) {
            if (i <= list_vertex[list_vertex.size() - 1].second) {
                if (list_vertex[current_vert].second == i) {
                    std::cout << '[' << list_vertex[current_vert].first->the_key << ' ' <<
                        list_vertex[current_vert].first->the_value << ' ' << list_vertex[current_vert].first->father->the_key << ']';
                    ++current_vert;
                }
                else {
                    std::cout << '_';
                }
            }
            else {
                std::cout << '_';
            }
            if (i == pow(2, level + 1) - 2) {
                // enter
                std::cout << std::endl;
                ++level;
            }
            else {
                std::cout << ' ';
            }
        }
    }
};

int main()
{
    std::string str_enter;
    bool is_prev_line_empty = false;
    //TheVertex* root = new TheVertex(0, "");
    TheBSPTree TheTree;
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
            std::vector<std::string> this_line = split_for_functions(str_enter);
            
            if (this_line[0] == "add" && this_line.size() == 3) {
                if (this_line[1].size() == 0) {
                    std::cout << "error" << std::endl;
                }
                else {
                    std::string ret_add = "";
                    if (count_vertex != 0) {
                        ret_add = TheTree.add_(std::stoll(this_line[1]), this_line[2]);
                    }
                    else {
                        TheTree.root_tree = new TheVertex(std::stoll(this_line[1]), this_line[2]);
                    }
                    if (ret_add != "error") {
                        ++count_vertex;
                    }
                    else {
                        std::cout << "error" << std::endl;
                    }
                }
            }
            else if (this_line[0] == "set" && this_line.size() == 3) {
                if (this_line[1].size() == 0) {
                    std::cout << "error" << std::endl;
                }
                else {
                    if (count_vertex != 0) {
                        TheTree.set_(std::stoll(this_line[1]), this_line[2]);
                    }
                    else {
                        std::cout << "error" << std::endl;
                    }
                }
            }
            else if (this_line[0] == "delete" && this_line.size() == 2) {
                if (this_line[1].size() == 0) {
                    std::cout << "error" << std::endl;
                }
                else {
                    if (count_vertex != 0) {
                        std::string ret_del = TheTree.delete_(std::stoll(this_line[1]));
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
                
            }
            else if (this_line[0] == "min" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    TheTree.min_();
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "max" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    TheTree.max_();
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "print" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    if (count_vertex == 1) {
                        std::cout << '[' << TheTree.root_tree->the_key << ' ' << TheTree.root_tree->the_value << ']' << std::endl;
                    }
                    else {
                        TheTree.print_(TheTree.root_tree, count_vertex);
                    }
                }
                else {
                    std::cout << "_" << std::endl;
                }
            }
            else if (this_line[0] == "search" && this_line.size() == 2) {
                TheTree.search_(std::stoll(this_line[1]));
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
    }
}
