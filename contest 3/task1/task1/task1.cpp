#include <algorithm>
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

int main()
{
    std::string str_enter;
    bool is_prev_line_empty = false;
    int count_vertex = 0;
    long long N = 0;
    long long P = 0;
    long long B = 0;
    long long B_max = 0;
    long long current_time = 0;
    bool set_parameters = false;
    std::vector<long long> the_data;

    while (std::getline(std::cin, str_enter)) { // сложность O(n) по времени - чтение первой строки и затем ещё n строк
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
            if (set_parameters) {
                if (B_max * 2 + std::stoi(str_enter) >= current_time) {
                    the_data.push_back(std::stoi(str_enter));
                }
            }
            else {
                std::vector<std::string> this_line = split_space(str_enter);
                if (this_line.size() == 5) {
                    N = std::stoi(this_line[0]);
                    P = std::stoi(this_line[1]);
                    B = std::stoi(this_line[2]);
                    B_max = std::stoi(this_line[3]);
                    current_time = std::stoi(this_line[4]);
                    set_parameters = true;
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
        }
    }

    // по памяти - O(n), т.к. нужно хранить массив из n значений

    std::sort(the_data.begin(), the_data.end()); // сложность O(n * log n) по времени в худшем для C++17 и выше согласно документации
    long long time_block = 0;
    bool is_block_earlier = false;
    long long last_time_blocked = 0;

    if (the_data.size() < N) {
        std::cout << "ok" << std::endl;
    }
    else {

        for (size_t i = 0; i < the_data.size() - N + 1; ++i) { // сложность O(n), т.к. поэлементный обход массива
            if (the_data[i + N - 1] - the_data[i] < P) {
                if (is_block_earlier) {
                    time_block *= 2;
                    if (time_block > B_max) {
                        time_block = B_max;
                    }
                }
                else {
                    time_block = B;
                }
                i += N - 1;
                is_block_earlier = true;
                last_time_blocked = the_data[i];
            }
        }

        if (last_time_blocked + time_block < current_time) {
            std::cout << "ok" << std::endl;
        }
        else {
            std::cout << last_time_blocked + time_block << std::endl;
        }
    }

    // Итого: сложность по времени вычисляется из сложности чтения (O(n)), сортировки (O(n * log n)) и работы самого алгоритма (O(n)).
    // Рассчитаем итоговую сложность по времени: O(n + n * log n + n) = O(n * (2 + log n)) =  O(n * log n)
    // Сложность по памяти (память нужна только для хранения массива значений (O(n)), отстальыне параметры постоянны). Итого O(n)
    // Ответ: по времени O(n * log n), по памяти O(n)
}
