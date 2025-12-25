#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

std::vector<std::string> split_space(std::string the_string) {
    std::vector<std::string> words;
    std::string this_word;
    for (size_t i = 0; i < the_string.size(); ++i) {
        if (the_string[i] == ' ') {
            if (this_word.size() != 0) {
                words.push_back(this_word);
            }
            else {
                return { "print_error" };
            }
            this_word = "";
        }
        else {
            this_word.push_back(the_string[i]);
        }
        if (i == the_string.size() - 1) {
            if (this_word.size() != 0) {
                words.push_back(this_word);
            }
        }
    }

    return words;
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

    ~TheVertex() { }
};

std::string add_(TheVertex* root, long long k, std::string v) {
    TheVertex* last_vertex = root;
    TheVertex* new_vertex = new TheVertex(k, v);
    bool stop_search = false;
    while (!stop_search) {
        if (k > (*last_vertex).the_key) {
            if ((*last_vertex).right_child == nullptr) {
                stop_search = true;
                (*new_vertex).father = last_vertex;
                (*last_vertex).right_child = new_vertex;
            }
            else {
                last_vertex = (*last_vertex).right_child;
            }
        }
        else {
            if (k == (*last_vertex).the_key) {
                return "error";
            }
            if ((*last_vertex).left_child == nullptr) {
                stop_search = true;
                (*new_vertex).father = last_vertex;
                (*last_vertex).left_child = new_vertex;
            }
            else {
                last_vertex = (*last_vertex).left_child;
            }
        }
    }
    return "";
}

void set_(TheVertex* root, long long k, std::string v) {
    TheVertex* this_vertex = root;
    while ((*this_vertex).the_key != k) {
        if (k > (*this_vertex).the_key) {
            if ((*this_vertex).right_child == nullptr) {
                std::cout << "error" << std::endl;
                return;
            }
            else {
                this_vertex = (*this_vertex).right_child;
            }
        }
        else {
            if ((*this_vertex).left_child == nullptr) {
                std::cout << "error";
                return;
            }
            else {
                this_vertex = (*this_vertex).left_child;
            }
        }
    }
    (*this_vertex).the_value = v;
}

std::string delete_(TheVertex** root, long long k) {
    TheVertex* this_vertex = *root;
    std::string father_go_to = "left";
    while ((*this_vertex).the_key != k) {
        if (k > (*this_vertex).the_key) {
            if ((*this_vertex).right_child == nullptr) {
                return "error";
            }
            else {
                this_vertex = (*this_vertex).right_child;
                father_go_to = "right";
            }
        }
        else {
            if ((*this_vertex).left_child == nullptr) {
                return "error";
            }
            else {
                this_vertex = (*this_vertex).left_child;
                father_go_to = "left";
            }
        }
    }
    TheVertex* deleted_vertex = this_vertex;
    TheVertex copy_deleted_vertex = *deleted_vertex;
    TheVertex* father_deleted = new TheVertex(0, "");
    TheVertex* max_in_left = new TheVertex(0, "");
    TheVertex copy_max_in_left = *max_in_left;
    bool delete_root = false;
    if (deleted_vertex != *root) {
        father_deleted = deleted_vertex->father;
    }
    else {
        delete_root = true;
    }

    if (deleted_vertex->left_child == nullptr
        && deleted_vertex->right_child == nullptr) {
        if (father_go_to == "left") {
            father_deleted->left_child = nullptr;
        }
        else {
            father_deleted->right_child = nullptr;
        }
        deleted_vertex->father = nullptr;
        delete deleted_vertex;
    }
    else if (deleted_vertex->right_child == nullptr) {
        if (delete_root) {
            *root = deleted_vertex->left_child;
            (*root)->father = nullptr;
            deleted_vertex->left_child = nullptr;
            delete deleted_vertex;
        }
        else {
            if (father_go_to == "left") {
                father_deleted->left_child = deleted_vertex->left_child;
            }
            else {
                father_deleted->right_child = deleted_vertex->left_child;
            }
            deleted_vertex->left_child->father = deleted_vertex->father;
            deleted_vertex->father = nullptr;
            deleted_vertex->left_child = nullptr;
            delete deleted_vertex;
        }
    }
    else if (deleted_vertex->left_child == nullptr) {
        if (delete_root) {
            *root = deleted_vertex->right_child;
            (*root)->father = nullptr;
            deleted_vertex->right_child = nullptr;
            delete deleted_vertex;
        }
        else {
            if (father_go_to == "left") {
                father_deleted->left_child = deleted_vertex->right_child;
            }
            else {
                father_deleted->right_child = deleted_vertex->right_child;
            }
            deleted_vertex->right_child->father = deleted_vertex->father;
            deleted_vertex->father = nullptr;
            deleted_vertex->right_child = nullptr;
            delete deleted_vertex;
        }
    }
    else {
        max_in_left = deleted_vertex->left_child;
        bool father_right_delete = false;
        while (max_in_left->right_child != nullptr) {
            max_in_left = max_in_left->right_child;
            father_right_delete = true;
        }
        copy_max_in_left = *max_in_left;
        max_in_left->the_key = copy_deleted_vertex.the_key;
        max_in_left->the_value = copy_deleted_vertex.the_value;
        deleted_vertex->the_key = copy_max_in_left.the_key;
        deleted_vertex->the_value = copy_max_in_left.the_value;
        
        if (max_in_left->left_child == nullptr) {
            if (father_right_delete) {
                max_in_left->father->right_child = nullptr;
            }
            else {
                max_in_left->father->left_child = nullptr;
            }
            max_in_left->father = nullptr;
            max_in_left->the_key = 0;
            max_in_left->the_value = "";
            delete max_in_left;
        }
        else {
            max_in_left->the_key = max_in_left->left_child->the_key;
            max_in_left->the_value = max_in_left->left_child->the_value;
            max_in_left->left_child->father = nullptr;
            max_in_left->left_child->the_key = 0;
            max_in_left->left_child->the_value = "";
            delete max_in_left->left_child;
            max_in_left->left_child = nullptr;
        }
    }
    return "";
}

void search_(TheVertex* root, long long k) {
    TheVertex* this_vertex = root;
    while ((*this_vertex).the_key != k) {
        if (k > (*this_vertex).the_key) {
            if ((*this_vertex).right_child == nullptr) {
                std::cout << "0" << std::endl;
                return;
            }
            else {
                this_vertex = (*this_vertex).right_child;
            }
        }
        else {
            if ((*this_vertex).left_child == nullptr) {
                std::cout << "0" << std::endl;
                return;
            }
            else {
                this_vertex = (*this_vertex).left_child;
            }
        }
    }
    std::cout << "1 " << (*this_vertex).the_value << std::endl;
}

void min_(TheVertex* root) {
    TheVertex* this_vertex = root;
    while ((*this_vertex).left_child != nullptr) {
        this_vertex = (*this_vertex).left_child;
    }
    std::cout << (*this_vertex).the_key << ' ' <<
        (*this_vertex).the_value << std::endl;
}

void max_(TheVertex* root) {
    TheVertex* this_vertex = root;
    while ((*this_vertex).right_child != nullptr) {
        this_vertex = (*this_vertex).right_child;
    }
    std::cout << (*this_vertex).the_key << ' ' <<
        (*this_vertex).the_value << std::endl;
}

void print_(TheVertex* root, int count_vertex) {
    std::queue<TheVertex*> the_queue;
    the_queue.push(root);
    int count_printed_in_queue = 1;
    int level = 0;
    while (count_printed_in_queue < count_vertex) {
        for (size_t v_in_lev = 0; v_in_lev < pow(2, level); ++v_in_lev) {
            TheVertex this_vertex = *the_queue.front(); 
            if (level == 0) {
                std::cout << '[' << this_vertex.the_key << ' ' <<
                    this_vertex.the_value << ']';
            }
            else {
                if (this_vertex.father == nullptr &&
                    this_vertex.right_child == nullptr &&
                    this_vertex.left_child == nullptr) {
                    std::cout << '_';
                }
                else {
                    std::cout << '[' << this_vertex.the_key << ' ' <<
                        this_vertex.the_value << ' ' << this_vertex.father->the_key << ']';
                }
                if (v_in_lev != pow(2, level) - 1) {
                    std::cout << ' ';
                }
            }

            // delete from queue
            the_queue.pop();

            // push in queue
            if (this_vertex.father == nullptr &&
                this_vertex.right_child == nullptr &&
                this_vertex.left_child == nullptr) {
                for (size_t j = 0; j < 2; ++j) {
                    the_queue.push(new TheVertex(0, ""));
                }
            }
            else {
                if (this_vertex.left_child == nullptr) {
                    the_queue.push(new TheVertex(0, ""));
                }
                else {
                    the_queue.push(this_vertex.left_child);
                    ++count_printed_in_queue;
                }
                if (this_vertex.right_child == nullptr) {
                    the_queue.push(new TheVertex(0, ""));
                }
                else {
                    the_queue.push(this_vertex.right_child);
                    ++count_printed_in_queue;
                }
            }
        }
        ++level;
        std::cout << std::endl;
    }

    // print last level (in queue)
    int size_queue_last = the_queue.size();
    for (size_t i = 0; i < size_queue_last; ++i) {
        if (the_queue.front()->father == nullptr &&
            the_queue.front()->right_child == nullptr &&
            the_queue.front()->left_child == nullptr) {
            std::cout << '_';
        }
        else {
            std::cout << '[' << the_queue.front()->the_key << ' ' << the_queue.front()->the_value << ' ' << 
                the_queue.front()->father->the_key << ']';
        }
        if (i != size_queue_last - 1) {
            std::cout << ' ';
        }
        the_queue.pop();
    }
    std::cout << std::endl;
}

int main()
{
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
                    ret_add = add_(root, std::stoll(this_line[1]), this_line[2]);
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
                    set_(root, std::stoll(this_line[1]), this_line[2]);
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
                    min_(root);
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "max" && this_line.size() == 1) {
                if (count_vertex != 0) {
                    max_(root);
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
                search_(root, std::stoll(this_line[1]));
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
    }
}