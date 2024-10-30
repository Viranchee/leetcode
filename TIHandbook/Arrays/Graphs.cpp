#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
  // int numIslands(vector<vector<char>> &grid) {
  //   vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  //   function<void(int, int)> dfs;
  //   dfs = [&](int i, int j) {
  //     if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() ||
  //         grid[i][j] == '0') {
  //       return;
  //     }
  //     grid[i][j] = '0';
  //     for (auto d : directions) {
  //       dfs(i + d.first, j + d.second);
  //     }
  //   };
  //   int count = 0;
  //   for (int i = 0; i < grid.size(); i++) {
  //     for (int j = 0; j < grid[0].size(); j++) {
  //       if (grid[i][j] == '1') {
  //         count++;
  //         dfs(i, j);
  //       }
  //     }
  //   }
  //   return count;
  // }

  // int maxAreaOfIsland(vector<vector<int>> &grid) {
  //   vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  //   function<int(int, int)> dfs;
  //   dfs = [&](int i, int j) {
  //     if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() ||
  //         grid[i][j] == 0) {
  //       return 0;
  //     }
  //     grid[i][j] = 0;
  //     int area = 1;
  //     for (auto d : directions) {
  //       area += dfs(i + d.first, j + d.second);
  //     }
  //     return area;
  //   };
  //   int maxArea = 0;
  //   for (int i = 0; i < grid.size(); i++) {
  //     for (int j = 0; j < grid[0].size(); j++) {
  //       if (grid[i][j] == 1) {
  //         maxArea = max(maxArea, dfs(i, j));
  //       }
  //     }
  //   }

  //   return maxArea;
  // };
};

// /*
// Definition for a Node.
// class Node {
// public:
//   int val;
//   vector<Node *> neighbors;
//   Node() {
//     val = 0;
//     neighbors = vector<Node *>();
//   }
//   Node(int _val) {
//     val = _val;
//     neighbors = vector<Node *>();
//   }
//   Node(int _val, vector<Node *> _neighbors) {
//     val = _val;
//     neighbors = _neighbors;
//   }
// };
// // */

// class Graph {
// public:
//   Node *cloneGraph(Node *node) {
//     if (!node) {
//       return nullptr;
//     }
//     unordered_map<Node *, Node *> visited;
//     function<Node *(Node *)> dfs;
//     dfs = [&](Node *n) {
//       if (visited.find(n) != visited.end()) {
//         return visited[n];
//       }
//       Node *clone = new Node(n->val);
//       visited[n] = clone;
//       for (auto neighbor : n->neighbors) {
//         clone->neighbors.push_back(dfs(neighbor));
//       }
//       return clone;
//     };
//     return dfs(node);
//   }

//   void islandsAndTreasure(vector<vector<int>> &grid) {
//     // Make pair<int, int> a type
//     struct Coordinate {
//       int x, y;
//     };
//     vector<Coordinate> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//     vector<Coordinate> treasures;

//     // Find all treasures:
//     for (int i = 0; i < grid.size(); i++) {
//       for (int j = 0; j < grid[0].size(); j++) {
//         if (grid[i][j] == 2) {
//           treasures.push_back({i, j});
//         }
//       }
//     }
//     // Insert all treasures into visited:
//     unordered_set<Coordinate> visited;
//     for (auto t : treasures) {
//       visited.insert(t);
//     }
//     // Go from all treasures to all islands:
//     function<int(Coordinate)> dfs;
//     dfs = [&treasures, &dfs, &grid, &visited](Coordinate c) { return 0; };
//   }

//   int orangesRotting(vector<vector<int>> &grid) {
//     struct Coordinate {
//       int x, y;
//     };
//     vector<Coordinate> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//     queue<Coordinate> q;
//     int fresh = 0;
//     for (int i = 0; i < grid.size(); i++) {
//       for (int j = 0; j < grid[0].size(); j++) {
//         if (grid[i][j] == 2) {
//           q.push({i, j});
//         } else if (grid[i][j] == 1) {
//           fresh++;
//         }
//       }
//     }
//     int minutes = 0;
//     while (!q.empty() && fresh > 0) {
//       int size = q.size();
//       for (int i = 0; i < size; i++) {
//         Coordinate c = q.front();
//         q.pop();
//         for (auto d : directions) {
//           int x = c.x + d.x;
//           int y = c.y + d.y;
//           if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() ||
//               grid[x][y] != 1) {
//             continue;
//           }
//           grid[x][y] = 2;
//           fresh--;
//           q.push({x, y});
//         }
//       }
//       minutes++;
//     }

//     return fresh == 0 ? minutes : -1;
//   }

//   vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
//     vector<vector<int>> res;
//     vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//     function<void(int, int, vector<vector<int>> &)> dfs;
//     dfs = [&](int i, int j, vector<vector<int>> &ocean) {
//       ocean[i][j] = 1;
//       for (auto d : directions) {
//         int x = i + d.first;
//         int y = j + d.second;
//         if (x < 0 || x >= heights.size() || y < 0 || y >= heights[0].size()
//         ||
//             ocean[x][y] == 1 || heights[x][y] < heights[i][j]) {
//           continue;
//         }
//         dfs(x, y, ocean);
//       }
//     };
//     vector<vector<int>> pacific(heights.size(),
//                                 vector<int>(heights[0].size(), 0));
//     vector<vector<int>> atlantic(heights.size(),
//                                  vector<int>(heights[0].size(), 0));
//     for (int i = 0; i < heights.size(); i++) {
//       dfs(i, 0, pacific);
//       dfs(i, heights[0].size() - 1, atlantic);
//     }
//     for (int j = 0; j < heights[0].size(); j++) {
//       dfs(0, j, pacific);
//       dfs(heights.size() - 1, j, atlantic);
//     }
//     for (int i = 0; i < heights.size(); i++) {
//       for (int j = 0; j < heights[0].size(); j++) {
//         if (pacific[i][j] == 1 && atlantic[i][j] == 1) {
//           res.push_back({i, j});
//         }
//       }
//     }

//     return res;
//   }

//   void solve(vector<vector<char>> &board) {
//     vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//     function<void(int, int)> dfs;
//     dfs = [&](int i, int j) {
//       if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
//           board[i][j] != 'O') {
//         return;
//       }
//       board[i][j] = '*';
//       for (auto d : directions) {
//         dfs(i + d.first, j + d.second);
//       }
//     };
//     // Capture all 'O's on the border and DFS on them:
//     for (int i = 0; i < board.size(); i++) {
//       dfs(i, 0);
//       dfs(i, board[0].size() - 1);
//     }
//     for (int j = 0; j < board[0].size(); j++) {
//       dfs(0, j);
//       dfs(board.size() - 1, j);
//     }
//     // Surrounded O's are now X's, and *'s are O's:
//     for (int i = 0; i < board.size(); i++) {
//       for (int j = 0; j < board[0].size(); j++) {
//         if (board[i][j] == 'O') {
//           board[i][j] = 'X';
//         } else if (board[i][j] == '*') {
//           board[i][j] = 'O';
//         }
//       }
//     }
//   }

//   bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
//     vector<vector<int>> graph(numCourses, vector<int>());
//     vector<int> indegree(numCourses, 0);
//     for_each(prerequisites.begin(), prerequisites.end(), [&](auto p) {
//       graph[p[1]].push_back(p[0]);
//       indegree[p[0]]++;
//     });

//     queue<int> q;
//     for_each(indegree.begin(), indegree.end(), [&q](int i) {
//       if (i == 0)
//         q.push(i);
//     });
//     int count = 0;
//     while (!q.empty()) {
//       int course = q.front();
//       q.pop();
//       count++;
//       for (auto c : graph[course]) {
//         if (--indegree[c] == 0)
//           q.push(c);
//       }
//     }
//     return count == numCourses;
//   }

//   vector<int> findRedundantConnection(vector<vector<int>> &edges) {
//     vector<int> res;
//     vector<int> parent(edges.size() + 1);
//     iota(parent.begin(), parent.end(), 0);

//     function<int(int)> find;
//     find = [&](int i) {
//       if (parent[i] != i) {
//         parent[i] = find(parent[i]);
//       }
//       return parent[i];
//     };
//     for (auto edge : edges) {
//       int u = find(edge[0]);
//       int v = find(edge[1]);
//       if (u == v) {
//         res = edge;
//       } else {
//         parent[u] = v;
//       }
//     }
//     return res;
//   }

//   vector<int> findOrder(int n, vector<vector<int>> &prerequisites) {
//     vector<vector<int>> graph(n, vector<int>());
//     vector<int> indegree(n, 0);
//     for (auto p : prerequisites) {
//       graph[p[1]].push_back(p[0]);
//       indegree[p[0]]++;
//     }
//     queue<int> q;
//     for (int i = 0; i < n; i++) {
//       if (indegree[i] == 0)
//         q.push(i);
//     }

//     vector<int> res;
//     while (!q.empty()) {
//       int course = q.front();
//       q.pop();
//       res.push_back(course);
//       for (auto c : graph[course]) {
//         if (--indegree[c] == 0) {
//           q.push(c);
//         }
//       }
//     }
//     return res.size() == n ? res : vector<int>();
//   }
// };