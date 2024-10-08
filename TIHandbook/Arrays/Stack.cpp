#include <algorithm>
#include <iterator>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
public:
  bool isValid_Parenthesis(string s) {
    stack<char> st;
    unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
    for (char c : s) {
      if (pairs.find(c) != pairs.end()) {
        if (st.empty() || st.top() != pairs[c]) {
          return false;
        }
        st.pop();
      } else {
        st.push(c);
      }
    }
    return st.empty();
  }

  int evalRPN(vector<string> &tokens) {
    int eval = 0;
    auto it = tokens.begin();
    stack<int> st;
    while (it != tokens.end()) {
      if (*it == "+" || *it == "-" || *it == "*" || *it == "/") {
        int b = st.top();
        st.pop();
        int a = st.top();
        st.pop();
        if (*it == "+") {
          st.push(a + b);
        } else if (*it == "-") {
          st.push(a - b);
        } else if (*it == "*") {
          st.push(a * b);
        } else if (*it == "/") {
          st.push(a / b);
        }
      } else {
        st.push(stoi(*it));
      }
      it++;
    }
    return eval;
  }

private:
  void dfs_generateParenthesis(int open, int close, string s, int n,
                               vector<string> &res) {
    if (open == close == n) {
      res.push_back(s);
      return;
    }
    if (open < n) {
      dfs_generateParenthesis(open + 1, close, s + "(", n, res);
    }
    if (close < n) {
      dfs_generateParenthesis(open, close + 1, s + ")", n, res);
    }
  }

public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    dfs_generateParenthesis(0, 0, "", n, res);
    return res;
  }

  vector<int> dailyTemperatures(vector<int> &temperatures) {
    stack<int> lowTi;
    // for (int i = 0; i < temperatures.size(); i++) {
    //   while (!lowTi.empty() && temperatures[i] > temperatures[lowTi.top()]) {
    //     temperatures[lowTi.top()] = i - lowTi.top();
    //     lowTi.pop();
    //   }
    //   lowTi.push(i);
    // }
    // while (!lowTi.empty()) {
    //   temperatures[lowTi.top()] = 0;
    //   lowTi.pop();
    // }

    for (auto it = temperatures.begin(); it != temperatures.end(); it++) {
      while (!lowTi.empty() && *it > temperatures[lowTi.top()]) {
        temperatures[lowTi.top()] =
            distance(temperatures.begin(), it) - lowTi.top();
        lowTi.pop();
      }
      lowTi.push(distance(temperatures.begin(), it));
    }
    while (!lowTi.empty()) {
      temperatures[lowTi.top()] = 0;
      lowTi.pop();
    }

    return temperatures;
  }

  int carFleet(int target, vector<int> &position, vector<int> &speed) {
    struct Car {
      int pos;
      float time;
      bool operator>(const Car &c) const { return pos > c.pos; }
      // bool operator<(const Car &c) const { return pos < c.pos; }
      // bool operator==(const Car &c) const { return pos == c.pos; }
    };
    vector<Car> cars;
    for (int i = 0; i < position.size(); i++) {
      cars.push_back(
          {position[i], (float)(target - position[i]) / (float)speed[i]});
    }
    sort(cars.begin(), cars.end(), greater<Car>());
    stack<float> fleet;
    for (auto car : cars) {
      while (!fleet.empty() && car.time >= fleet.top())
        fleet.pop();
      fleet.push(car.time);
    }
    return fleet.size();
  }
  int calculate(string s) {
    s += '+';
    stack<int> stk;
    long long int ans = 0, curr = 0;
    char sign = '+';

    for (int i = 0; i < s.size(); i++) {
      if (isdigit(s[i]))
        curr = curr * 10 + (s[i] - '0');
      else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
        if (sign == '+' || sign == '-') {
          stk.push(curr * -(sign - ','));
        } else if (sign == '*' || sign == '/') {
          int val = ((sign - '*') ? stk.top() / curr : stk.top() * curr);
          stk.pop();
          stk.push(val);
        }
        curr = 0;
        sign = s[i];
      }
    }
    while (stk.size()) {
      ans += stk.top();
      stk.pop();
    }
    return ans;
  }
};

#include <stdexcept>
#include <vector>

class MinStack {
public:
  MinStack() {}

  void push(int val) {
    values.push_back(val);
    // Update the mi vector
    if (mi.empty() || val <= getMin()) {
      mi.push_back(values.size() - 1);
    }
  }

  void pop() {
    if (values.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    if (values.back() == getMin()) {
      mi.pop_back();
    }
    values.pop_back();
  }

  int top() {
    if (values.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return values.back();
  }

  int getMin() {
    if (mi.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return values[mi.back()];
  }

private:
  std::vector<int> values;
  std::vector<int> mi;
};
