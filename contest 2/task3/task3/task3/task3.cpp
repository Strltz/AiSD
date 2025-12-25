#include <cmath>
#include <iostream>
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
    else if (func == "min" || func == "max" || func == "print" || func == "extract") {
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
    long long the_key;
    std::string the_value;
    TheVertex(long long k, std::string v) {
        the_key = k;
        the_value = v;
    }
};

class Heap {
public:
    std::vector<TheVertex> heap_data;

    Heap() {
        heap_data = { };
    }

    void Zig_swap(long long ind_l, long long ind_r) {
        TheVertex copy_l = heap_data[ind_l];
        heap_data[ind_l] = heap_data[ind_r];
        heap_data[ind_r] = copy_l;
    }

    long long father_index(long long vertex_index) {
        long long ret;
        if (vertex_index == 0) {
            ret = -1;
        }
        else {
            ret = floor((vertex_index - 1) / 2);
        }
        return ret;
    }

    long long left_child_index(long long vertex_index) {   
        int ret = 2 * vertex_index + 1;
        return ret;
    }

    long long right_child_index(long long vertex_index) {
        int ret = 2 * vertex_index + 2;
        return ret;
    }

    void siftUp(long long i) {
        while (i > 0) {
            int father_indx = father_index(i);
            if (heap_data[father_indx].the_key < heap_data[i].the_key) {
                break;
            }
            Zig_swap(i, father_indx);
            i = father_indx;
        }
    }

    void siftDown(long long i) {
        long long left_child = left_child_index(i);
        long long right_child = right_child_index(i);
        while (left_child < heap_data.size()) {
            long long min_i = left_child;
            if (right_child < heap_data.size() && heap_data[right_child].the_key < heap_data[left_child].the_key) {
                min_i = right_child;
            }
            if (heap_data[min_i].the_key > heap_data[i].the_key) {
                return;
            }
            Zig_swap(i, min_i);
            i = min_i;
            left_child = left_child_index(i);
            right_child = right_child_index(i);
        }
    }

    void correction_function(long long vertex_index) {
        if (heap_data.size() == 0 || vertex_index >= heap_data.size()) {
            return;
        }
        long help_vertex = father_index(vertex_index);
        if (help_vertex >= 0) {
            if (heap_data[vertex_index].the_key < heap_data[help_vertex].the_key) {
                siftUp(vertex_index);
                return;
            }
        }
        siftDown(vertex_index);
    }

    std::string add_(long long k, std::string v) {
        bool is_error = false;
        for (size_t i = 0; i < heap_data.size(); ++i) {
            if (heap_data[i].the_key == k) {
                return "error";
            }
        }
        TheVertex new_vertex = TheVertex(k, v);
        heap_data.push_back(new_vertex);
        siftUp(heap_data.size() - 1);
        return "";
    }

    std::string delete_(long long k) {
        long long indx = -1;
        for (size_t i = 0; i < heap_data.size(); ++i) {
            if (heap_data[i].the_key == k) {
                indx = i;
                break;
            }
        }
        if (indx == -1) {
            return "error";
        }
        Zig_swap(indx, heap_data.size() - 1);
        heap_data.pop_back();
        correction_function(indx);
        return "";
    }

    std::string set_(long long k, std::string v) {
        for (size_t i = 0; i < heap_data.size(); ++i) {
            if (heap_data[i].the_key == k) {
                heap_data[i].the_value = v;
                return "";
            }
        }
        return "error";
    }

    long long search_(long long k) {
        for (size_t i = 0; i < heap_data.size(); ++i) {
            if (heap_data[i].the_key == k) {
                return i;
            }
        }
        return -1;
    }

    int min_() {
        return 0;
    }

    long long max_() {
        if (heap_data.size() == 1) {
            return 0;
        }
        long long max_index = heap_data.size() - 1;
        for (size_t i = heap_data.size() - 1; i > floor((heap_data.size() - 2) / 2); --i) {
            if (heap_data[i].the_key > heap_data[max_index].the_key) {
                max_index = i;
            }
        }
        return max_index;
    }

    std::pair<long long, std::string> extract_() {
        if (heap_data.size() == 0) {
            return { -1, ""};
        }
        std::pair<long long, std::string> root_ = { heap_data[0].the_key, heap_data[0].the_value };
        Zig_swap(0, heap_data.size() - 1);
        heap_data.pop_back();
        siftDown(0);
        return root_;
    }

    void print_() {
        if (heap_data.size() == 0) {
            std::cout << "_" << std::endl;
            return;
        }
        std::cout << '[' << heap_data[0].the_key << ' ' <<
            heap_data[0].the_value << ']' << std::endl;
        int count_levels = floor(log2(heap_data.size())) + 1;
        int count_for_print = pow(2, count_levels) - 1;
        int level = 1;
        int current_vert = 1;
        for (size_t i = 1; i < count_for_print; ++i) {
            if (i <= heap_data.size() - 1) {
                if (current_vert == i) {
                    std::cout << '[' << heap_data[current_vert].the_key << ' ' <<
                        heap_data[current_vert].the_value << ' ' << heap_data[father_index(current_vert)].the_key << ']';
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
    Heap TheHeap;
    bool is_prev_line_empty = false;
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
                    if (TheHeap.heap_data.size() != 0) {
                        ret_add = TheHeap.add_(std::stoll(this_line[1]), this_line[2]);
                    }
                    else {
                        TheHeap.heap_data.push_back({ std::stoll(this_line[1]), this_line[2] });
                    }
                    if (ret_add == "error") {
                        std::cout << "error" << std::endl;
                    }
                }
            }
            else if (this_line[0] == "set" && this_line.size() == 3) {
                if (this_line[1].size() == 0) {
                    std::cout << "error" << std::endl;
                }
                else {
                    std::string ret_set = "";
                    if (TheHeap.heap_data.size() != 0) {
                        ret_set = TheHeap.set_(std::stoll(this_line[1]), this_line[2]);
                    }
                    else {
                        std::cout << "error" << std::endl;
                    }
                    if (ret_set == "error") {
                        std::cout << "error" << std::endl;
                    }
                }
            }
            else if (this_line[0] == "delete" && this_line.size() == 2) {
                if (this_line[1].size() == 0) {
                    std::cout << "error" << std::endl;
                }
                else {
                    if (TheHeap.heap_data.size() != 0) {
                        std::string ret_del = TheHeap.delete_(std::stoll(this_line[1]));
                        if (ret_del == "error") {
                            std::cout << "error" << std::endl;
                        }
                    }
                    else {
                        std::cout << "error" << std::endl;
                    }
                }
            }
            else if (this_line[0] == "min" && this_line.size() == 1) {         
                if (TheHeap.heap_data.size() != 0) {
                    int min_vertex = TheHeap.min_();
                    std::cout << TheHeap.heap_data[min_vertex].the_key << ' ' << min_vertex << ' ' << TheHeap.heap_data[min_vertex].the_value << std::endl;
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "max" && this_line.size() == 1) {
                if (TheHeap.heap_data.size() != 0) {
                    long long max_vertex = TheHeap.max_();
                    std::cout << TheHeap.heap_data[max_vertex].the_key << ' ' << max_vertex << ' ' << TheHeap.heap_data[max_vertex].the_value << std::endl;
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (this_line[0] == "print" && this_line.size() == 1) {
                TheHeap.print_();
            }
            else if (this_line[0] == "search" && this_line.size() == 2) {
                if (TheHeap.heap_data.size() == 0) {
                    std::cout << "0" << std::endl;
                }
                else {
                    long long this_index = TheHeap.search_(std::stoll(this_line[1]));
                    if (this_index != -1) {
                        TheHeap.search_(std::stoll(this_line[1]));
                        std::cout << "1" << ' ' << this_index << ' ' << TheHeap.heap_data[this_index].the_value << std::endl;
                    }
                    else {
                        std::cout << '0' << std::endl;
                    }
                }
            }
            else if (this_line[0] == "extract" && this_line.size() == 1) {
                if (TheHeap.heap_data.size() != 0) {
                    std::pair<long long, std::string> this_vertex = TheHeap.extract_();
                    std::cout << this_vertex.first << ' ' << this_vertex.second << std::endl;
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
}
