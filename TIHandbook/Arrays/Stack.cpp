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

  vector<string> generateParenthesis(int n) { return {}; }
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
