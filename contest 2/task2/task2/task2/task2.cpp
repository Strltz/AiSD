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
    friend class TheBSPTree;
private:
    long long the_key;
    std::string the_value;
    TheVertex* father;
    TheVertex* right_child;
    TheVertex* left_child;

public:
    TheVertex(long long k, std::string v) {
        the_key = k;
        the_value = v;
        father = nullptr;
        right_child = nullptr;
        left_child = nullptr;
    }

    long long get_key() {
        return the_key;
    }

    std::string get_value() {
        return the_value;
    }

    TheVertex* get_father() {
        return father;
    }

    ~TheVertex() {}
};

class TheBSPTree {
private:
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

public:
    TheBSPTree() {
        root_tree = new TheVertex(0, "");
    }
    TheVertex* root_tree;
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

    std::string set_(long long k, std::string v) {
        TheVertex** root = &root_tree;
        TheVertex* this_vertex = *root;
        while ((*this_vertex).the_key != k) {
            if (k > (*this_vertex).the_key) {
                if ((*this_vertex).right_child == nullptr) {
                    splay_(root, this_vertex);
                    return "error";
                }
                else {
                    this_vertex = (*this_vertex).right_child;
                }
            }
            else {
                if ((*this_vertex).left_child == nullptr) {
                    splay_(root, this_vertex);
                    return "error";
                }
                else {
                    this_vertex = (*this_vertex).left_child;
                }
            }
        }
        (*this_vertex).the_value = v;
        splay_(root, this_vertex);
        return "";
    }

    std::pair<bool, std::string> search_(long long k) {
        TheVertex** root = &root_tree;
        TheVertex* this_vertex = *root;
        while ((*this_vertex).the_key != k) {
            if (k > (*this_vertex).the_key) {
                if ((*this_vertex).right_child == nullptr) {
                    splay_(root, this_vertex);
                    return { false, "" };
                }
                else {
                    this_vertex = (*this_vertex).right_child;
                }
            }
            else {
                if ((*this_vertex).left_child == nullptr) {
                    splay_(root, this_vertex);
                    return { false, "" };
                }
                else {
                    this_vertex = (*this_vertex).left_child;
                }
            }
        }
        splay_(root, this_vertex);
        return { true, this_vertex->the_value };
    }

    std::pair<long long, std::string> min_() {
        TheVertex** root = &root_tree;
        TheVertex* this_vertex = *root;
        while ((*this_vertex).left_child != nullptr) {
            this_vertex = (*this_vertex).left_child;
        }
        splay_(root, this_vertex);
        return { this_vertex->the_key, this_vertex->the_value };
    }

    std::pair<long long, std::string> max_() {
        TheVertex** root = &root_tree;
        TheVertex* this_vertex = *root;
        while ((*this_vertex).right_child != nullptr) {
            this_vertex = (*this_vertex).right_child;
        }
        splay_(root, this_vertex);
        return { this_vertex->the_key, this_vertex->the_value };
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

    void print_(std::ostream& the_out) {
        the_out << "[" << root_tree->the_key << " " << root_tree->the_value << "]\n";
        std::deque<TheVertex*> the_queue;
        int index_last = -1;
        if (root_tree->left_child) {
            the_queue.push_back(root_tree->left_child);
            index_last = 0;
        }
        if (root_tree->right_child) {
            if (!root_tree->left_child) {
                the_queue.push_back(nullptr);
                the_queue.push_back(root_tree->right_child);
                index_last = 1;
            }
            else {
                the_queue.push_back(root_tree->right_child);
                index_last = 1;
            }
        }
        int index_last_b = index_last;
        int level_size = 2;
        while (index_last != -1) {
            index_last = -1;
            int t = 0;
            for (auto this_vertex : the_queue) {
                if (this_vertex) {
                    if (this_vertex->left_child) {
                        index_last = t * 2;
                    }
                    if (this_vertex->right_child) {
                        index_last = t * 2 + 1;
                    }
                }
                ++t;
            }
            int checker = -1;
            for (int i = 0; i <= index_last_b; ++i) {
                TheVertex* this_vertex = the_queue.front();
                the_queue.pop_front();
                if (checker == index_last) {
                    if (this_vertex) {
                        the_out << "[" << this_vertex->the_key << " " + this_vertex->the_value << " " << this_vertex->father->the_key << "] ";
                    }
                    else {
                        the_out << "_ ";
                    }
                }
                else {
                    if (this_vertex) {
                        the_out << "[" << this_vertex->the_key << " " << this_vertex->the_value << " " << this_vertex->father->the_key << "] ";
                        the_queue.push_back(this_vertex->left_child);
                    }
                    else {
                        the_out << "_ ";
                        the_queue.push_back(nullptr);
                    }
                    ++checker;
                    if (checker == index_last) {
                        continue;
                    }
                    the_queue.push_back((this_vertex ? this_vertex->right_child : nullptr));
                    ++checker;
                }
            }
            if (index_last_b < level_size - 1) {
                for (int j = index_last_b; j < level_size - 1; ++j) {
                    the_out << "_ ";
                }
            }
            the_out << "\n";
            if (index_last == -1) {
                return;
            }
            level_size *= 2;
            index_last_b = index_last;
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
            std::string ret = "";
            if (this_line[0] == "add" && this_line.size() == 3) {
                if (this_line[1].size() == 0) {
                    std::cout << "error" << std::endl;
                }
                else {
                    if (count_vertex != 0) {
                        ret = TheTree.add_(std::stoll(this_line[1]), this_line[2]);
                    }
                    else {
                        TheTree.root_tree = new TheVertex(std::stoll(this_line[1]), this_line[2]);
                    }
                    if (ret != "error") {
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
                        ret = TheTree.set_(std::stoll(this_line[1]), this_line[2]);
                        if (ret == "error") {
                            std::cout << "error" << std::endl;
                        }
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
                        ret = TheTree.delete_(std::stoll(this_line[1]));
                        if (ret != "error") {
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
                    std::pair<long long, std::string> ret_min = TheTree.min_();
                    std::cout << ret_min.first << " " << ret_min.second << std::endl;
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "max" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    std::pair<long long, std::string> ret_max = TheTree.max_();
                    std::cout << ret_max.first << " " << ret_max.second << std::endl;
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "print" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    TheTree.print_(std::cout);
                    
                }
                else {
                    std::cout << "_" << std::endl;
                }
            }
            else if (this_line[0] == "search" && this_line.size() == 2) {
                std::pair<bool, std::string> ret_search = TheTree.search_(std::stoll(this_line[1]));
                if (ret_search.first) {
                    std::cout << "1" << " " << ret_search.second << std::endl;
                }
                else {
                    std::cout << "0" << std::endl;
                }
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
    }
}
