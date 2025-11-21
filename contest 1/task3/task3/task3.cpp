#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
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

int main()
{
    std::string str_enter;
    std::getline(std::cin, str_enter);
    std::vector<std::string> this_line = split_space(str_enter);
    std::string* graph_type = new std::string{ this_line[0] };
    std::string* start_vertex = new std::string{ this_line[1] };
    std::string* search_type = new std::string{ this_line[2] };
    std::map<std::string, std::set<std::string>> the_adjency_list;
    if (this_line.size() == 3) {
        while (std::getline(std::cin, str_enter))
        {
            if (!str_enter.empty()) {
                this_line = split_space(str_enter);
                if (the_adjency_list.count(this_line[0]) != 0) {
                    the_adjency_list[this_line[0]].insert(this_line[1]);
                }
                else {
                    the_adjency_list[this_line[0]] =
                        std::set<std::string>{ this_line[1] };
                }
                if (*graph_type == "u") {
                    if (the_adjency_list.count(this_line[1])) {
                        the_adjency_list[this_line[1]].insert(this_line[0]);
                    }
                    else {
                        the_adjency_list[this_line[1]] =
                            std::set<std::string>{ this_line[0] };
                    }
                }
            }
            else {
                break;
            }
        }
        delete graph_type;
        std::set<std::string> already;
        if (*search_type == "b") {
            delete search_type;
            std::queue<std::string> the_queue;
            the_queue.push(*start_vertex);
            delete start_vertex;
            std::string current_vertex;
            while (!the_queue.empty()) {
                if (already.count(the_queue.front()) == 0) {
                    current_vertex = the_queue.front();
                    std::cout << current_vertex << std::endl;
                    already.insert(current_vertex);
                    the_queue.pop();
                    for (auto i : the_adjency_list[current_vertex]) {
                        if (already.count(i) == 0) {
                            the_queue.push(i);
                        }
                    }
                }
                else {
                    the_queue.pop();
                }
            }
        }
        else {
            delete search_type;
            std::stack<std::string> the_stack;
            the_stack.push(*start_vertex);
            delete start_vertex;
            std::string current_vertex;
            while (!the_stack.empty()) {
                if (already.count(the_stack.top()) == 0) {
                    current_vertex = the_stack.top();
                    std::cout << current_vertex << std::endl;
                    already.insert(current_vertex);
                    the_stack.pop();
                    for (auto iter = the_adjency_list[current_vertex].rbegin();
                        iter != the_adjency_list[current_vertex].rend(); ++iter) {
                        if (already.count(*iter) == 0) {
                            the_stack.push(*iter);
                        }
                    }
                }
                else
                {
                    the_stack.pop();
                }
            }
        }
    }

    return 0;
}
