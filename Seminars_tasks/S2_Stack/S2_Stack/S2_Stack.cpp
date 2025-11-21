#include <iostream>
#include <vector>

std::string is_brackets_string_correct(std::string string_brackets) {
    std::vector<char> the_stack; // stack
    for (size_t i = 0; i < string_brackets.size(); ++i) {
        if (the_stack.size() == 0) {
            if (string_brackets[i] == ']' || string_brackets[i] == ')') {
                return "Error1\n";
            }
            else {
                the_stack.push_back(string_brackets[i]);
            }
        }
        else {
            if (string_brackets[i] == '(' || string_brackets[i] == '[') {
                the_stack.push_back(string_brackets[i]);
            }
            else {
                if (string_brackets[i] == ']') {
                    if (the_stack[the_stack.size() - 1] == '[') {
                        the_stack.pop_back();
                    }
                    else {
                        return "Error2\n";
                    }
                }
                else {
                    if (the_stack[the_stack.size() - 1] == '(') {
                        the_stack.pop_back();
                    }
                    else {
                        return "Error3\n";
                    }
                }
            }
        }
    }
    if (the_stack.size() == 0) {
        return "Correct\n";
    }
    else {
        return "Error4\n";
    }
}

int main()
{
    std::string the_string;
    std::cout << "Enter brackets-string" << std::endl;
    std::cin >> the_string;
    std::cout << is_brackets_string_correct(the_string) << std::endl;
}
