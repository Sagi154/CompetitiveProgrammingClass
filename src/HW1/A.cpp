#include <limits>
#include <algorithm>
#include <iostream>

int maximise_score_per_testcase (const int testcase_size, const int *A) {
    int optimal_score = std::numeric_limits<int>::max(); // Initial optimal score set to "infinity"
    int future_left_neighbour_dif = 0; // |A[i] - A[i+1]| = |A[j] - A[j-1]| when j = i+1
    for(int i = 0; i < testcase_size; i++) {
        // Check both neighbours (if such exists) and the maximum possible outcome
        int temp_score = future_left_neighbour_dif;
        if(i < testcase_size - 1) { // Right neighbour
            future_left_neighbour_dif = std::abs(A[i] - A[i+1]); // Saves this calculation for i+1
            temp_score = std::max(temp_score, future_left_neighbour_dif);
        }
        optimal_score = std::min(temp_score, optimal_score); // Updating the optimal score
    }
    return optimal_score;
}

int main3() {
    std::ios::sync_with_stdio(false);  // Magic Dani line
    int T; // Number of test cases
    std::cin >> T;
    for(int i = 0; i < T; i++) {
        int N; // The length of the current array
        std::cin >> N;
        int* curr_testcase = new int[N];
        for(int j = 0; j < N; j++) { // Receiving the current array as input and saving it
            std::cin >> curr_testcase[j];
        }
        std::cout << maximise_score_per_testcase(N, curr_testcase) << std::endl; // Calculating optimal score
        delete[] curr_testcase;
    }
    return 0;
}