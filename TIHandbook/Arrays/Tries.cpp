// Solve using Unique Pointers

#include <cstddef>
#include <memory>
#include <string>

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
    if (node->children[26] == nullptr)
      node->children[26] = make_unique<Node>();
  }

  bool search(string word) {}

  bool startsWith(string prefix) { return }
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
class WordDictionary {
private:
public:
  WordDictionary() {}

  void addWord(string word) {}

  bool search(string word) {}
};
