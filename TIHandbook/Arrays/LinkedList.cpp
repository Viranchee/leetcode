#include <algorithm>
#include <deque>
#include <iterator>
#include <list>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *reverseList(ListNode *head) {
    ListNode *curr = head, *prev = nullptr;
    while (curr) {
      ListNode *next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    return prev;
  }

  ListNode *mergeTwoListsSorted(ListNode *list1, ListNode *list2) {
    ListNode dummy(0);
    ListNode *tail = &dummy;

    auto append = [&tail](ListNode *node) {
      tail->next = node;
      tail = tail->next;
      return tail->next;
    };
    while (list1 && list2) {
      if (list1->val < list2->val)
        list1 = append(list1);
      else
        list2 = append(list2);
    }
    tail->next = list1 ? list1 : list2;
    return dummy.next;
  }

  void reorderList(ListNode *head) {
    if (!head)
      return;
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    ListNode *l1 = head, *l2 = slow->next;
    slow->next = nullptr;
    l2 = reverseList(l2);
    // shuffle merge
  }

  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode dummy(0, head);
    ListNode *slow = &dummy, *fast = &dummy;
    for (int i = 0; i < n; i++)
      fast = fast->next;
    while (fast->next) {
      slow = slow->next;
      fast = fast->next;
    }
    ListNode *toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;
    return dummy.next;
  }

  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode dummy(0);
    ListNode *tail = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
      int total = carry;
      if (l1) {
        total += l1->val;
        l1 = l1->next;
      }
      if (l2) {
        total += l2->val;
        l2 = l2->next;
      }
      carry = total / 10;
      tail->next = new ListNode(total % 10);
      tail = tail->next;
    }
    return dummy.next;
  }

  bool hasCycle(ListNode *head) {
    unordered_set<ListNode *> visited;
    while (head) {
      if (visited.find(head) != visited.end())
        return true;
      visited.insert(head);
      head = head->next;
    }
    return false;
  }

  int findDuplicate(vector<int> &nums) {
    // O 1 memory
    int slow = nums[0], fast = nums[0];
    do {
      slow = nums[slow];
      fast = nums[nums[fast]];
    } while (slow != fast);
    int slow2 = nums[0];
    while (slow != slow2) {
      slow = nums[slow];
      slow2 = nums[slow2];
    }
    return slow;
  }
};

// Definition for a Node.
class Node {
public:
  int val;
  Node *next;
  Node *random;

  Node(int _val) {
    val = _val;
    next = NULL;
    random = NULL;
  }
};

class Solutio2 {
public:
  Node *copyRandomList(Node *head) {
    if (!head)
      return nullptr;
    unordered_map<Node *, Node *> copies;
    Node *curr = head;
    while (curr) {
      copies[curr] = new Node(curr->val);
      curr = curr->next;
    }
    curr = head;
    while (curr) {
      copies[curr]->next = copies[curr->next];
      copies[curr]->random = copies[curr->random];
      curr = curr->next;
    }
    return copies[head];
  }
};

class LRUCache {
  struct KV {
    int key, value;
  };
  list<KV> cache;
  unordered_map<int, list<KV>::iterator> map;
  int size;

public:
  LRUCache(int capacity) : size(capacity) {}
  int get(int key) {
    if (map.find(key) == map.end())
      return -1;
    auto it = map[key];
    cache.splice(cache.begin(), cache, it);
    return it->value;
  }

  int put(int key, int value) {
    if (map.find(key) != map.end()) {
      auto it = map[key];
      // it->value = value;
      // cache.splice(cache.begin(), cache, it);
      cache.erase(it);
    }
    if (cache.size() == size) {
      auto last = cache.back();
      map.erase(last.key);
      cache.pop_back();
    }
    cache.push_front({key, value});
    map[key] = cache.begin();
    return value;
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */