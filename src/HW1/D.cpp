#include <iostream>

/***
 * Algorithm: for any given array we follow this observation - for any numbers a_i and a_j chosen,
 * if a_i + a_j is odd, we lose -1 (let's call it a penalty) from the sum of a_i and a_j when we
 * perform the operation in the question. So the final number will be the sum of array minus the penalties.
 * We get such penalty when one (and only one) of the chosen numbers is odd.
 * Player 1 wants to maximize the final number, so he'll want to minimize the penalties.
 * Player 2 will want to maximize the penalties.
 * So if the players play optimally, Player 1 will want to choose 2 odd numbers and player 2
 * will want to choose only one odd number.
 * So for every trio of odd numbers we get 1 penalty, and if the odd number mod 3 is 1 we get
 * another penalty (in addition to the number of trios)
 * Time complexity: O(t*n)
 * Memory complexity: O(n)
 */

int main123213() {
  std::ios::sync_with_stdio(false);  // Magic Dani line
  std::cin.tie(nullptr);  // Even more magic
  int t; // Number of test cases
  std::cin >> t;
  while (t--){
    int n; // Size of array
    std::cin >> n;
    int arr[n]; // Array of integers
    for (int i = 0; i < n; i++) {
      std::cin >> arr[i];
    }
    long long odd_count = arr[0] % 2; // Counts how many odd numbers in the array
    long long curr_sum = arr[0]; // Sum of array
    std::cout << arr[0] << " ";
    for (int i = 1; i < n; i++) { // "For each k = 1,2,...,n, answer...
      curr_sum += arr[i];
      if (arr[i] % 2 != 0) // Counts odd numbers in the array
        odd_count++;
      std::cout << curr_sum - (int(odd_count / 3) + int(odd_count % 3 == 1)) << " ";
      // Calculation of observation mentioned above
    }
    std::cout << std::endl;
  }
  return 0;
}
