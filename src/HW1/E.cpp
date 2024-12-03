#include <iostream>
#include <string>
#include <map>

/***
 * Algorithm: For an even length string, we need to count the maximum appearance of a letter in even positions and odd positions,
 * and then we just need to change the rest of letters in even positions and odd positions to be the same as the letter with
 * the max count in even/odd positions respectively.
 * For an odd length string, we need to figure out which index shall we delete to get an even length string and turning it to
 * an alternating string by doing the minimal number of switches.
 * So every index, we count the number of appearances for every letter in even and odd positions after the "deletion" of said index.
 * We note in our calculation that indices following that "deleted" index turn from even to odd and vice versa.
 * Time complexity: O(t*n)
 * Memory complexity: O(t*n)
 */


int even_string(int str_len, std::string str) {
    std::map<char, int> letters_count_even;
    std::map<char, int> letters_count_odd;
    for(int i = 0; i < str_len; i++) { // Count appearances for every letter on odd and even positions
        if ( i % 2 == 0)
            letters_count_even[str[i]]++;
        else
            letters_count_odd[str[i]]++;
    }
    int even_max_letter_count = 0;
    for (const auto& pair: letters_count_even) // Count maximum count of letter in even positions
        even_max_letter_count = std::max(even_max_letter_count, pair.second);
    int odd_max_letter_count = 0;
    for (const auto& pair: letters_count_odd) // Count maximum count of letter in odd positions
        odd_max_letter_count = std::max(odd_max_letter_count, pair.second);
    return ((str_len / 2) - even_max_letter_count) + ((str_len / 2) - odd_max_letter_count);
}

int odd_string(int str_len, std::string str) {
    std::map<char, int> total_letters_count_even;
    std::map<char, int> total_letters_count_odd;
    for(int i = 0; i < str_len; i++) { // Count appearances for every letter on odd and even positions
        if ( i % 2 == 0)
            total_letters_count_even[str[i]]++;
        else
            total_letters_count_odd[str[i]]++;
    }
    std::map<char, int> letters_count_even; // Count appearances again
    std::map<char, int> letters_count_odd;
    int min_switches = str_len;
    // Temp variables for after deletion of given index:
    std::map<char, int> per_index_count_even; // count appearances in even positions for each letter
    std::map<char, int> per_index_count_odd; // count appearances in odd positions for each letter
    int per_index_max_even_count = 0; // Max count of letter appearance in even pos
    int per_index_max_odd_count = 0; // Max count of letter appearance in even pos
    int per_index_temp_switches = 0; // Number of switches needed to turn the given string to an alternating one
    for(int i = 0; i < str_len; i++) {
        for(char j = 'a'; j <= 'z'; j++) { // Get actual count for all letters after deletion of str[i]
            per_index_count_even[j] = letters_count_even[j] + (total_letters_count_odd[j] - letters_count_odd[j] - ((j == str[i]) && (i % 2 == 1)));
            per_index_count_odd[j] = letters_count_odd[j] + (total_letters_count_even[j] - letters_count_even[j] - ((j == str[i]) && (i % 2 == 0)));
        }
        for (const auto& pair: per_index_count_even) // Count maximum count of letter in even positions
            per_index_max_even_count = std::max(per_index_max_even_count, pair.second);
        for (const auto& pair: per_index_count_odd) // Count maximum count of letter in odd positions
            per_index_max_odd_count = std::max(per_index_max_odd_count, pair.second);
        per_index_temp_switches = ((str_len - 1) / 2 - per_index_max_even_count) + ((str_len -1) / 2 - per_index_max_odd_count);
        min_switches = std::min(min_switches, per_index_temp_switches);
        // Clear all counting variables for current index
        per_index_count_even.clear();
        per_index_count_odd.clear();
        per_index_max_even_count = 0;
        per_index_max_odd_count = 0;
        per_index_temp_switches = 0;
        if ( i % 2 == 0) // Update letters count
            letters_count_even[str[i]]++;
        else
            letters_count_odd[str[i]]++;
    }
    return min_switches + 1;
}

int main(){
    std::ios::sync_with_stdio(false);  // Magic Dani line
    std::cin.tie(nullptr);  // Even more magic
    int t; // Number of test cases
    std::cin >> t;
    for(int i = 0; i < t; i++) {
        int n;
        std::cin >> n; // Length of current test case's string
        std::string curr_str;
        std::cin >> curr_str;
        int min_switches = n;
        if(n % 2 == 0)
            min_switches = even_string(n, curr_str);
        else {
            min_switches = odd_string(n, curr_str);
        }
        std::cout << min_switches << std::endl;
    }
}
