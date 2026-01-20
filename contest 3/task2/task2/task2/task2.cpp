#include <cmath>
#include <iostream>
#include <string>
#include <vector>

long long M_Mersen = pow(2, 31) - 1;

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

class FilterBloom {
public:
    std::vector<int8_t> the_data;
    int size_bits_;
    std::vector<unsigned long long> prime_numbers_for_hash;
    long long m;
    long long k;

    FilterBloom() {
        the_data = { };
        size_bits_ = 0;
        prime_numbers_for_hash = { 2, 3 };
        m = 0;
        k = 0;
    }

    void new_filter(int m_, int k_) {
        m = m_;
        k = k_;
        size_bits_ = m;
        resize_(size_bits_);
        new_prime_numbers(k);
    }

    void new_prime_numbers(size_t n_count) {
        if (n_count > prime_numbers_for_hash.size()) {
            for (size_t i = prime_numbers_for_hash[prime_numbers_for_hash.size() - 1] + 2; n_count > prime_numbers_for_hash.size(); i += 2) {
                bool prm = true;
                for (size_t j = 0; j < prime_numbers_for_hash.size() && prime_numbers_for_hash[j] < (sqrt(i) + 2); ++j) {
                    if (i % prime_numbers_for_hash[j] == 0) {
                        prm = false;
                        break;
                    }
                }
                if (prm) {
                    prime_numbers_for_hash.push_back(i);
                }
            }
        }
        else {
            return;
        }
    }

    void resize_(size_t new_size_bits) {
        the_data.resize(ceil(new_size_bits / 8), 0);
        size_bits_ = new_size_bits;
    }

    bool set_bit(size_t x) {
        if (x >= size_bits_) {
            return false;
        }
        else {
            int byte = x / 8;
            x -= byte * 8;
            the_data[byte] = the_data[byte] | (1 << x);
        }
    }

    std::pair<bool, bool> get_bit(size_t x) {
        if (x >= size_bits_) {
            return { false, false };
        }
        else {
            int byte = x / 8;
            x -= byte * 8;
            if ((the_data[byte] & (1 << x)) >> x == 1) {
                return { true, true };
            }
            else {
                return{ true, false };
            }
        }
    }

    void print_(std::ostream& the_out) {
        for (size_t i = 0; i < m; ++i) {
            the_out << get_bit(i).second;
        }
    }

    unsigned long long hash_func_i(long long i, unsigned long long x) {
        return (((i + 1) * x + prime_numbers_for_hash[i]) % M_Mersen) % size_bits_;
    }

    void add_(unsigned long long x) {
        for (size_t i = 0; i < k; ++i) {
            set_bit(hash_func_i(i, x));
        }
    }

    bool search_(unsigned long long x) {
        for (size_t i = 0; i < k; ++i) {
            if (!get_bit(hash_func_i(i, x)).second) {
                return false;
            }
        }
        return true;
    }
};


int main()
{
    std::string str_enter;
    bool is_prev_line_empty = false;

    bool is_set = false;

    FilterBloom the_filter;
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
            if (this_line[0] == "set" && this_line.size() == 3) {
                if (is_set) {
                    std::cout << "error" << std::endl;
                }
                else {
                    long long n = std::stoull(this_line[1]);
                    double P = std::stod(this_line[2]);

                    if (P > 0 && P < 1 && n >= 1) {
                        the_filter.m = round(abs(n * log2(P) / log(2)));
                        the_filter.k = round(-log2(P));

                        if (the_filter.k < 1) {
                            std::cout << "error" << std::endl;
                        }
                        else {
                            is_set = true;
                            the_filter.new_filter(the_filter.m, the_filter.k);
                            std::cout << abs(the_filter.m) << " " << the_filter.k << std::endl;
                        }
                    }
                    else {
                        std::cout << "error" << std::endl;
                    }
                }
            }
            else if (this_line[0] == "add" && this_line.size() == 2 && is_set) {
                the_filter.add_(std::stoull(this_line[1]));
            }
            else if (this_line[0] == "search" && this_line.size() == 2 && is_set) {
                auto ret = the_filter.search_(std::stoull(this_line[1]));
                if (ret) {
                    std::cout << "1" << std::endl;
                }
                else {
                    std::cout << "0" << std::endl;
                }
            }
            else if (str_enter == "print" && is_set) {
                the_filter.print_(std::cout);
                std::cout << std::endl;
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
    }
    return 0;
}
