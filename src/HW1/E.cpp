#include <iostream>
#include <string>


int even_string(int str_len, std::string str) {
    int chars_count[26] = {};
    for(int i = 0; i < str_len; i++) {
        if ( i % 2 == 0)
            chars_count[str[i] - '0' - 49]++;
    }
    int even_max_letter_count = chars_count[0];
    for(int i = 1; i < 26; i++) {
        if(chars_count[i] > even_max_letter_count) {
            even_max_letter_count = chars_count[i];
        }
    }
    std::fill_n(chars_count, 26, 0);
    for(int i = 0; i < str_len; i++) {
        if ( i % 2 != 0)
            chars_count[str[i] - '0' - 49]++;
    }
    int odd_max_letter_count = chars_count[0];
    for(int i = 1; i < 26; i++) {
        if(chars_count[i] > odd_max_letter_count) {
            odd_max_letter_count = chars_count[i];
        }
    }
    return ((str_len / 2) - even_max_letter_count) + ((str_len / 2) - odd_max_letter_count);
}


int main(){
    std::ios::sync_with_stdio(false);  // Magic Dani line
    int t; // Number of test cases
    std::cin >> t;
    for(int i = 0; i < t; i++) {
        int n;
        std::cin >> n; // Length of current test case's string
        std::string curr_str;
        std::cin >> curr_str;
        // can improve run time against memory by counting letters count when getting the input.
        int min_switches = n;
        if(n % 2 == 0)
            min_switches = even_string(n, curr_str);
        else {
            for(int j = 0; j < n; j++) {
                std::string no_j_str = curr_str.substr(0, j) + curr_str.substr(j + 1);
                min_switches = std::min(min_switches, 1 + even_string(n - 1, no_j_str));
            }
        }
        std::cout << min_switches << std::endl;
    }
}
