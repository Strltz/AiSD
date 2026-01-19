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

class TheBeatles {
public:
    std::vector<int8_t> the_data;
    size_t size_data_bits;

    TheBeatles() {
        the_data = { };
        size_data_bits = 0;
    }

    void resize_(size_t new_size_bits) {
        if (new_size_bits > size_data_bits) {
            size_data_bits = new_size_bits;
            the_data.resize(((new_size_bits + 7) / 8), 0);
        }
    }

    std::string set_bit(size_t t) {
        if (t >= size_data_bits) {
            return "error";
        }
        else {
            the_data[t / 8] = the_data[t / 8] | (1 << (t - (t / 8) * 8));
        }
        return "";
    }

    std::pair<std::string, bool> get_bit(size_t t) {
        if (t >= the_data.size() * 8) {
            return { "error", false };
        }
        else {
            bool for_ret = ((the_data[t / 8] & (1 << (t - (t / 8) * 8))) >> (t - (t / 8) * 8) == 1);
            //bool for_ret = the_data[t / 8] / int(pow(2, t % 8)) % 2 == 1;
            if (for_ret) {
                return { "", true };
            }
            else {
                return { "", false };
            }
        }
    }

    void print_(std::ostream& the_out) {
        for (size_t i = 0; i < size_data_bits; ++i) {
            the_out << get_bit(i).second;
        }
    }
};

class PrimeNumbers {
public:
    std::vector<unsigned long long> prime_numbers;

    PrimeNumbers() {
        prime_numbers = { 2, 3 };
    }

    void new_numbers(size_t n_count) {
        if (n_count > prime_numbers.size()) {
            for (size_t i = prime_numbers[prime_numbers.size() - 1] + 2; n_count > prime_numbers.size(); i += 2) {
                bool prm = true;
                for (size_t j = 0; j < prime_numbers.size() && j < prime_numbers[j]; ++j) {
                    if (i % prime_numbers[j] == 0) {
                        prm = false;
                        break;
                    }
                }
                if (prm) {
                    prime_numbers.push_back(i);
                }
            }
        }
        else {
            return;
        }
    }


};

class FilterBloom {
public:
    std::vector<int8_t> the_data;
    int size_bits_;
    std::vector<unsigned long long> prime_numbers = { 2, 3 };
    PrimeNumbers primes_for_hash;
    long long m;
    long long k;

    FilterBloom() {
        m = 0;
        k = 0;
    }

    unsigned long long hash_func_i(long long i, unsigned long long x) {
        return (((i + 1) * x + primes_for_hash.prime_numbers[i]) % M_Mersen) % m;
    }

    void add_(unsigned long long x) {
        for (size_t i = 0; i < k; ++i) {
            bits_.set_bit(hash_func_i(i, x));
        }
    }

    std::pair<bool, std::string> search_(unsigned long long x) {
        for (size_t i = 0; i < k; ++i) {
            if (!bits_.get_bit(hash_func_i(i, x)).second) {
                if (bits_.get_bit(hash_func_i(i, x)).first == "") {
                    return { false, "" };
                }
                else {
                    return { false, "error" };
                }
            }
        }
        return { true, "" };
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
                        the_filter.m = round(-n * log2(P) / log(2));
                        the_filter.k = round(-log2(P));

                        if (the_filter.k < 1) {
                            std::cout << "error" << std::endl;
                        }
                        else {
                            the_filter.bits_.resize_(abs(the_filter.m));
                            the_filter.primes_for_hash.new_numbers(the_filter.k);
                            is_set = true;
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
                std::pair<bool, std::string> ret = the_filter.search_(std::stoull(this_line[1]));
                if (ret.second == "") {
                    if (ret.first) {
                        std::cout << "1" << std::endl;
                    }
                    else {
                        std::cout << "0" << std::endl;
                    }
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
            else if (str_enter == "print" && is_set) {
                the_filter.bits_.print_(std::cout);
                std::cout << std::endl;
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
    }
    return 0;
}
