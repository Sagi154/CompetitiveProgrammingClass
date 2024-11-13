#include <iostream>
#include <algorithm>

/***
 * This algorithm sorts the ranges by their left side, and then it runs over
 * all the ranges twice, once for checking which ranges are contained in other ranges,
 * and once for checking which ranges contain other ranges.
 * For a given [a,b], since the ranges are sorted we can know if there exists some other range
 * that may contain it or if it's contained in another range
 * (depending on how we go through the sorted ranges) , and by saving previously
 * seen b values (max or min depending on what we're currently looking for)
 * we can find out if [a,b] is contained/contains another range.
 * Time complexity : O(nlogn)
 * Memory complexity : O(n)
 */

struct Point{
  int a;
  int b;
  int index;
  };

int main(){
  std::ios::sync_with_stdio(false);  // Magic Dani line
  int n; // Number of ranges
  std::cin >> n;
  struct Point* points = new struct Point[n];
  for(int i = 0; i < n; i++){ // Saving all ranges to an array
    std::cin >> points[i].a >> points[i].b;
    points[i].index = i;
    }
  // Sorting the ranges so left side are in ascending order
  std::sort(points, points + n, [](struct Point &p1, struct Point &p2) {
    if (p1.a != p2.a){
      return p1.a < p2.a;
      } else {
        return p1.b > p2.b;
      }
      });
  int* contained = new int[n];
  contained[0] = 0; // Range with minimum 'a' can't possibly be contained in another range
  int r_max = points[0].b;
  for(int i = 1; i < n; i++) {  // Looking for ranges that are contained in some other range
    if(points[i].b <= r_max) {
      // Range [points[i].a, points[i].b] is contained in some other range
      contained[points[i].index] = 1;
    } else { // Not contained in another range, new r_max
      contained[points[i].index] = 0;
      r_max = points[i].b;
    }
  }
  int* contains = new int[n];
  contains[points[n-1].index] = 0; // Range with maximum 'a' can't possibly contain another range
  int r_min = points[n-1].b;
  for(int i = n-2; i > -1; i--) {   // Looking for ranges that contain some other range
    if(points[i].b >= r_min) {
      // Range [points[i].a, points[i].b] contains some other range
      contains[points[i].index] = 1;
    } else { // Doesn't contain another range, new r_min
      contains[points[i].index] = 0;
      r_min = points[i].b;
    }
  }
  std::cout << contains[0];
  for(int i = 1; i < n; i++) { // Printing first output line
    std::cout << " " << contains[i];
  }
  std::cout << std::endl;
  std::cout << contained[0];
  for(int i = 1; i < n; i++) { // Printing second output line
    std::cout << " " << contained[i];
  }
  }


