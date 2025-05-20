#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;
struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;

    NODE(int key = 0, NODE *left = nullptr, NODE *right = nullptr)
        : key(key), p_left(left), p_right(right) {}
};
NODE* Search (NODE* pRoot, int x) {
    if (pRoot == nullptr) {
        return nullptr;
    }
    NODE* curr = pRoot;
    if (x < curr->key) {
        return Search(curr->p_left, x);
    } else if (x > curr->key) {
        return Search(curr->p_right, x);
    }
    return curr;
}
void Insert (NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = new NODE(x);
        return;
    }
    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
}
void Remove (NODE* &pRoot, int x) {
    if (pRoot == nullptr)
        return;
    if (pRoot->key == x) {
        if (pRoot->p_left == nullptr) {
            NODE *tmp = pRoot->p_right;
            delete pRoot;
            pRoot = tmp;
        } else if (pRoot->p_right == nullptr) {
            NODE *tmp = pRoot->p_left;
            delete pRoot;
            pRoot = tmp;
        } else {
            NODE *curr = pRoot->p_right;
            while (curr->p_left != nullptr)
                curr = curr->p_left;
            pRoot->key = curr->key;
            Remove(pRoot->p_right, curr->key);
        }
    } else if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else
        Remove(pRoot->p_right, x);
}
NODE* createTree (int a[], int n) {
    NODE *root = nullptr;
    for (int i = 0; i < n; i++)
        Insert(root, a[i]);
    return root;
}
void removeTree(NODE* &pRoot) {
    while (pRoot != nullptr)
        Remove(pRoot, pRoot->key);
}
int maxDepth(NODE* root) {
    if (root == nullptr) {
        return 0;
    }
    stack<pair<NODE*, int>> stack;
    stack.push(pair(root, 1));
    int ans = 0;
    while (!stack.empty()) {
        auto [node, depth] = stack.top();
        stack.pop();
        ans = max(ans, depth);
        if (node->p_left != nullptr) {
            stack.push(pair(node->p_left, depth + 1));
        }
        if (node->p_right != nullptr) {
            stack.push(pair(node->p_right, depth + 1));
        }
    }    
    return ans;
}
int Height(NODE *pRoot, int value) {
    NODE* p = Search(pRoot, value);
    return maxDepth(p);
}
int countLess (NODE* pRoot, int x) {
    if (pRoot == nullptr) {
        return 0;
    }
    if (x <= pRoot->key) {
        return countLess(pRoot->p_left, x);
    }
    return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
}
int countGreater(NODE* pRoot, int x) {
    if (pRoot == nullptr) {
        return 0;
    }
    if (x >= pRoot->key) {
        return countGreater(pRoot->p_right, x);
    }
    return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
}
bool dfs(NODE* node, int small, int large) {
    if (node == nullptr) {
        return true;
    }
    if (node->key <= small || node->key >= large) {
        return false;
    }
    bool left = dfs(node->p_left, small, node->key);
    bool right = dfs(node->p_right, node->key, large);
    return left && right;
}
bool isBST (NODE* pRoot) {
    return dfs(pRoot, INT_MIN, INT_MAX);
}
bool isFullTree(NODE* root) {
    if (root == nullptr) {
        return true;
    }
    if (root->p_left == nullptr && root->p_right == nullptr) {
        return true;
    }
    if (root->p_left != nullptr && root->p_right != nullptr) {
        return isFullTree(root->p_left) && isFullTree(root->p_right);
    }
    return false;
}
bool isFullBST (NODE* pRoot) {
    return isBST(pRoot) && isFullTree(pRoot);
}
