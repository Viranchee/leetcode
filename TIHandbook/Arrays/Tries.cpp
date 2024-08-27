// Solve using Unique Pointers

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

struct Node {
  unique_ptr<Node> children[26];
  bool isTerminal;
};

class Trie {
private:
  unique_ptr<Node> root = make_unique<Node>();
  Node *searchPrefix(string word) {
    Node *node = root.get();
    if (word == "") {
      return node->children[26].get();
    }
    for (char c : word) {
      int index = c - 'a';
      if (node->children[index] == nullptr)
        return nullptr;
      else
        node = node->children[index].get();
    }
    return node;
  }

public:
  Trie() {}

  void insert(string word) {
    auto node = root.get();
    for (char c : word) {
      int index = c - 'a';
      if (node->children[index] == nullptr) {
        node->children[index] = make_unique<Node>();
      }
      node = node->children[index].get();
    }
  }

  bool search(string word) {
    Node *node = searchPrefix(word);
    return node != nullptr && node->isTerminal;
  }

  bool startsWith(string prefix) { return searchPrefix(prefix) != nullptr; }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
// Use STL and Algorithms

class WordDictionary {
private:
  Trie trie;

public:
  WordDictionary() {}

  void addWord(string word) { trie.insert(word); }

  bool search(string word) { return trie.search(word); }
};
