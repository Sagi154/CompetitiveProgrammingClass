#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);  // Magic Dani line
    std::cin.tie(nullptr);  // Even more magic
    int N; // Number of cards
    std::cin >> N;
    int prev_A = 0, prev_B = 0;
    long long prev_A_flips = 1; // Number of possible flips of previous cards when A_i-1 is faced up
    long long prev_B_flips = 1; // Number of possible flips of previous cards when B_i-1 is faced up
    int curr_A, curr_B;
    std::cin >> prev_A;
    std::cin >> prev_B;
    for(int i = 1; i < N; i++) {
        long long curr_A_flips = 0; // Number of flips of previous cards when B is faced up
        long long curr_B_flips = 0; // Number of flips of previous cards when B is faced up (has been flipped)
        std::cin >> curr_A;
        std::cin >> curr_B;
        if(curr_A == prev_A && prev_A == prev_B && prev_B == curr_B) { // No possible combinations for this i
            std::cout << 0;
            return 0;
        }
        if (curr_A != prev_A) // A_i faced up compatible with A_i-1 faced up
            curr_A_flips += prev_A_flips;
        if (curr_A != prev_B) // A_i faced up compatible with B_i-1 faced up
            curr_A_flips += prev_B_flips;
        if (curr_B != prev_A) // B_i faced up compatible with A_i-1 faced up
            curr_B_flips += prev_A_flips;
        if (curr_B != prev_B) // B_i faced up compatible with B_i-1 faced up
            curr_B_flips += prev_B_flips;
        prev_A = curr_A;
        prev_A_flips = curr_A_flips % 998244353;
        prev_B = curr_B;
        prev_B_flips = curr_B_flips % 998244353;
    }
    std::cout << (prev_A_flips + prev_B_flips) % 998244353 << std::endl; // Total possible ways to flip is the sum of the two faces of the last card
}