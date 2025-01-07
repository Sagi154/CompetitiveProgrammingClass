#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**
 * @brief Converts the input string to a new string with special characters inserted.
 *
 * This function helps handle even-length palindromes by adding '#' between characters
 * and at the boundaries. '@' and '$' are used as sentinels to avoid boundary checks.
 *
 * Example:
 * Input: "abba"
 * Output: "@#a#b#b#a#$"
 *
 * @param s The original input string.
 * @return string The transformed string.
 */
string convertToNewString(const string &s) {
    string newString = "@"; // Start with a sentinel character.
    for (char c : s) {
        newString += "#" + string(1, c); // Add '#' and the character.
    }
    newString += "#$"; // End with a sentinel character.
    return newString;
}

/**
 * @brief Finds the longest palindromic substring using Manacher's Algorithm.
 *
 * Manacher's Algorithm is an efficient way to find the longest palindromic substring
 * in \(O(n)\) time by utilizing a transformed string and avoiding redundant checks.
 *
 * @param s The original input string.
 * @return string The longest palindromic substring.
 */
string longestPalindromeSubstring(const string &s) {
    // Transform the input string.
    string Q = convertToNewString(s);
    int n = Q.size();
    vector<int> P(n, 0); // Array to store the radius of the palindrome centered at each position.
    int center = 0, right = 0; // Current center and right limit of the palindrome.

    // Loop through the transformed string.
    for (int i = 1; i < n - 1; i++) {
        // Find the mirror position of 'i' with respect to the center.
        int mirror = 2 * center - i;

        // If within the current palindrome, set the initial radius.
        if (i < right) {
            P[i] = min(right - i, P[mirror]);
        }

        // Try to expand the palindrome centered at 'i'.
        while (Q[i + 1 + P[i]] == Q[i - 1 - P[i]]) {
            P[i]++;
        }

        // Update the center and right boundary if the palindrome expands beyond 'right'.
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }

    // Find the maximum radius and its center index.
    int maxPalindrome = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (P[i] > maxPalindrome) {
            maxPalindrome = P[i];
            centerIndex = i;
        }
    }

    // Extract the longest palindromic substring from the original string.
    int start = (centerIndex - 1 - maxPalindrome) / 2; // Convert index back to the original string.
    return s.substr(start, maxPalindrome);
}

// Example usage:
int main() {
    string input = "babad";
    cout << "Longest Palindromic Substring: " << longestPalindromeSubstring(input) << endl;
    return 0;
}