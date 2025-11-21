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

std::vector<int> array_to_int(std::vector<std::string> words) {
    std::vector<int> the_array;
    for (size_t i = 0; i < words.size(); ++i) {
        the_array.push_back(std::stoi(words[i]));
    }
    
    return the_array;
}

int comparator(std::vector<int>* the_array, int index) {
    if (index == 0) {
        return index;
    }
    if ((*the_array)[index - 1] == (*the_array)[index]) {
        return comparator(the_array, index - 1);
    }
    else {
        return index;
    }
}

int bin_search(std::vector<int>* the_array, int element,
    int left_index, int right_index) {
    int middle_index = left_index + (right_index - left_index) / 2;
    if (left_index > right_index) {
        return -1;
    }
    if ((*the_array)[middle_index] == element) {
        return comparator(the_array, middle_index);
    } 
    else if ((*the_array)[middle_index] > element) {
        return bin_search(the_array, element, left_index, middle_index - 1);
    }
    else {
        return bin_search(the_array, element, middle_index + 1, right_index);
    }
}

int main()
{
    std::vector<std::string> all_commands;
    std::string str_cin;
    std::getline(std::cin, str_cin);
    std::vector<int> the_array = array_to_int(split_space(str_cin));
    while (std::getline(std::cin, str_cin)) {
        if (str_cin.empty()) {
            break;
        }
        all_commands.push_back(str_cin);
    }
    for (size_t i = 0; i < all_commands.size(); ++i) {
        std::vector<std::string> this_command = split_space(all_commands[i]);
        if (the_array.size() != 0) {
            if (this_command[0] == "search" && this_command.size() == 2) {
                std::cout << bin_search(&the_array, std::stoi(this_command[1]),
                    0, the_array.size() - 1) << std::endl;
            }
        }
        else if (this_command[0] == "search" && this_command.size() == 2) {
            std::cout << "-1" << std::endl;
        }
    }
}
