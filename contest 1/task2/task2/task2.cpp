#include <iostream>
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


class TheDeque {
private:
    size_t capacity_deq;
    size_t first_index;
    size_t last_index;
    std::vector<std::string> the_data;
    
public:
    TheDeque(size_t the_capacity) {
        the_data = std::vector<std::string>(the_capacity + 1);
        capacity_deq = the_capacity;
        first_index = 0;
        last_index = 0;
    }

    ~TheDeque() { }

    void pushb(std::string new_x) {
        if (last_index >= first_index) {
            if (last_index - first_index == capacity_deq) {
                std::cout << "overflow" << std::endl;
            }
            else {
                the_data[last_index] = new_x;
                if (last_index == capacity_deq) {
                    last_index = 0;
                }
                else {
                    ++last_index;
                }
            }
        }
        else {
            if (first_index - last_index == 1) {
                std::cout << "overflow" << std::endl;
            }
            else {
                the_data[last_index] = new_x;
                ++last_index;
            }
        }
    }

    void pushf(std::string new_x) {
        if (last_index >= first_index) {
            if (last_index - first_index == capacity_deq) {
                std::cout << "overflow" << std::endl;
            }
            else {
                if (first_index == 0) {
                    first_index = capacity_deq;
                    the_data[first_index] = new_x;
                }
                else {
                    --first_index;
                    the_data[first_index] = new_x;
                }
            }
        }
        else {
            if (first_index - last_index == 1) {
                std::cout << "overflow";
            }
            else {
                --first_index;
                the_data[first_index] = new_x;
            }
        }
    }

    void popf() {
        if (first_index == last_index) {
            std::cout << "underflow" << std::endl;
        }
        else {
            std::cout << the_data[first_index] << std::endl;
            if (last_index > first_index) {
                ++first_index;
            }
            else {
                if (first_index == capacity_deq) {
                    first_index = 0;
                }
                else {
                    ++first_index;
                }
            }
        }
    }

    void popb() {
        if (first_index == last_index) {
            std::cout << "underflow" << std::endl;
        }
        else {
            if (last_index > first_index) {
                --last_index;
            }
            else {
                if (last_index == 0) {
                    last_index = capacity_deq;
                }
                else {
                    --last_index;
                }
            }
            std::cout << the_data[last_index] << std::endl;
        }
    }

    void print_deq() {
        if (first_index == last_index) {
            std::cout << "empty" << std::endl;
        }
        else {
            if (last_index > first_index) {
                for (size_t i = first_index; i < last_index; ++i) {
                    std::cout << the_data[i] << " ";
                }
            }
            else {
                for (size_t i = first_index; i <= capacity_deq; ++i) {
                    std::cout << the_data[i] << " ";
                }
                for (size_t i = 0; i < last_index; ++i) {
                    std::cout << the_data[i] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    std::string str_enter;
    bool is_prev_line_empty = false;

    bool is_size_set = false;
    
    TheDeque* deq = nullptr;
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
            if (this_line[0] == "set_size" && this_line.size() == 2) {
                if (is_size_set) {
                    std::cout << "error" << std::endl;
                }
                else {
                    int the_size = std::stoi(this_line[1]);
                    if (the_size >= 0) {
                        deq = new TheDeque(the_size);
                        is_size_set = true;
                    }
                    else {
                        std::cout << "error" << std::endl;
                    }
                }
            }
            else if (this_line[0] == "pushb" && this_line.size() == 2 && is_size_set) {
                (*deq).pushb(this_line[1]);
            }
            else if (this_line[0] == "pushf" && this_line.size() == 2 && is_size_set) {
                (*deq).pushf(this_line[1]);
            }
            else if (str_enter == "popb" && is_size_set) {
                (*deq).popb();
            }
            else if (str_enter == "popf" && is_size_set) {
                (*deq).popf();
            }
            else if (str_enter == "print" && is_size_set) {
                (*deq).print_deq();
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
    }
    delete deq;
    return 0;
}