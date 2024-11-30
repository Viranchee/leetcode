// https://leetracer.com/screener

/*
Scale: 1, 2, 3, 4 < Lowest to Highest >
Understadning: 4
Working solution proposed: 4
Opitmized solution proposed: 3.9
Implementation: 3.5
Time taken: 1
Test Cases/Edge cases: 3.5
Dry Run: 4
Behavioral Score: 4
*/

/*
4 	Merge Intervals 	M 	4.71 	Vid / Code
5 	Longest Substring Without Repeating Characters
12 	3Sum 	M 	2.72 	Vid / Code

*/

#include <stdio.h>
#include <stdlib.h>
// 0 <= s.length <= 5 * 10^4
// "010..."
// "abcabcbb" a-z ONLY
//         r
//         l
// asdfghjklzxcvbnm,.
//                  l.              r
// ""
// early return
// "aaaaaaaaaa"
//             lr

// max: 3 ->

// your code goes here
// Longest Substring Without Repeating Characters
int longestSubstringWithoutRepeatingChars(char *arr) {
  if (arr[0] == 0)
    return 0;
  int visited[26] = {
      0,
  }; // 32 bits int32
  int longest = 1;
  int l = 0, r = 0;
  while (arr[r + 1] != 0) {
    while (arr[r + 1] != 0 && visited[arr[r + 1] - 'a'] == 0)
      visited[arr[++r] - 'a'] = 1;
    // now Left pointer
    if (l == r) {
      visited[arr[l++] - 'a'] = 0;
    } else {
      visited[arr[l++] - 'a'] = 0;
    }
    int length = r - l + 1;
    if (length > longest)
      longest = length;
  }
  return longest;
}

int main() {
  char substr[] = "a";
  int longest = longestSubstringWithoutRepeatingChars(substr);
  printf("Longest substr is %d", longest);

  return 0;
}

// linkedin.com/in/viranchee
// discord: viranchee

// https://www.linkedin.com/in/heeill395519173/