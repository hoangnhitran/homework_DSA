#include <iostream>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;
struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};
NODE* createNode(int data) {
    NODE* temp = new NODE;
    temp->key = data;
    temp->p_left = nullptr;
    temp->p_right = nullptr;
    temp->height = 0;
    return temp;
}
int getHeight (NODE* root) {
    if (root == nullptr) {
        return -1;
    }
    return root->height;
}
int getBalance (NODE* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->p_left) - getHeight(node->p_right);
}
void selfUpdate(NODE* root) {
    root->height = 1 + max(getHeight(root->p_left), getHeight(root->p_right));
}
void rightRotate(NODE*& root) {
    NODE* newRoot = root->p_left;
    NODE* sub = newRoot->p_right;
    newRoot->p_right = root;
    root->p_left = sub;
    selfUpdate(root);
    selfUpdate(newRoot);
    root = newRoot;
}
void leftRotate(NODE*& root) {
    NODE* newRoot = root->p_right;
    NODE* sub = newRoot->p_left;
    newRoot->p_left = root;
    root->p_right = sub;
    selfUpdate(root);
    selfUpdate(newRoot);
    root = newRoot;
}
void Insert(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    selfUpdate(pRoot);
    int balance = getBalance(pRoot);
    if (balance > 1) {
        if (x < pRoot->p_left->key) {
            rightRotate(pRoot);
        }
        else if (x > pRoot->p_left->key) {
            leftRotate(pRoot->p_left);
            rightRotate(pRoot);
        }
    }
    if (balance < -1) {
        if (x > pRoot->p_right->key) {
            leftRotate(pRoot);
        }
        else if (x < pRoot->p_right->key) {
            rightRotate(pRoot->p_right);
            leftRotate(pRoot);
        }
    }
}
void Remove(NODE* &pRoot, int x) {
    if (pRoot == nullptr) return;
    if (x < pRoot->key) {
        Remove(pRoot->p_left, x);
    } else if (x > pRoot->key) {
        Remove(pRoot->p_right, x);
    } else {
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
            NODE* tmp = (pRoot->p_left != nullptr) ? pRoot->p_left : pRoot->p_right;
            delete pRoot;
            pRoot = tmp;
        } else {
            NODE* curr = pRoot->p_right;
            while (curr->p_left != nullptr)
                curr = curr->p_left;
            pRoot->key = curr->key;
            Remove(pRoot->p_right, curr->key);
        }
    }
    if (pRoot == nullptr) return;
    selfUpdate(pRoot);
    int balance = getBalance(pRoot);
    if (balance > 1) {
        if (getBalance(pRoot->p_left) >= 0) {
            rightRotate(pRoot);
        } else {
            leftRotate(pRoot->p_left);
            rightRotate(pRoot);
        }
    }
    if (balance < -1) {
        if (getBalance(pRoot->p_right) <= 0) {
            leftRotate(pRoot);
        } else {
            rightRotate(pRoot->p_right);
            leftRotate(pRoot);
        }
    }
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
bool isAVL (NODE* pRoot) {
    if (pRoot == nullptr) {
        return true;
    }
    if (!isBST(pRoot)) {
        return false;
    }
    int balance = getBalance(pRoot);
    if (balance > 1 || balance < -1) {
        return false;
    }
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
