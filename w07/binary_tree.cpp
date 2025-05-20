#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
};
NODE *createNode(int data) {
    NODE *temp = new NODE;
    temp->key = data;
    temp->p_left = nullptr;
    temp->p_right = nullptr;
    return temp;
}
vector<int> NLR(NODE *pRoot) {
    if (pRoot == nullptr)
        return {};
    vector<int> res;
    res.push_back(pRoot->key);
    vector<int> left = NLR(pRoot->p_left);
    res.insert(res.end(), left.begin(), left.end());
    vector<int> right = NLR(pRoot->p_right);
    res.insert(res.end(), right.begin(), right.end());
    return res;
}
vector<int> LNR(NODE *pRoot) {
    if (pRoot == nullptr)
        return {};
    vector<int> res;
    vector<int> left = LNR(pRoot->p_left);
    res.insert(res.end(), left.begin(), left.end());
    res.push_back(pRoot->key);
    vector<int> right = LNR(pRoot->p_right);
    res.insert(res.end(), right.begin(), right.end());
    return res;
}
vector<int> LRN(NODE *pRoot) {
    if (pRoot == nullptr)
        return {};
    vector<int> res;
    vector<int> left = LRN(pRoot->p_left);
    res.insert(res.end(), left.begin(), left.end());
    vector<int> right = LRN(pRoot->p_right);
    res.insert(res.end(), right.begin(), right.end());
    res.push_back(pRoot->key);
    return res;
}
vector<vector<int>> LevelOrder(NODE *pRoot) {
    if (pRoot == nullptr)
        return {};
    queue<NODE*> q;
    q.push(pRoot);
    vector<vector<int>> res;
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        for (int i = 0; i < levelSize; i++) {
            NODE* curr = q.front();
            q.pop();
            currentLevel.push_back(curr->key);
            if (curr->p_left != nullptr)
                q.push(curr->p_left);
            if (curr->p_right != nullptr)
                q.push(curr->p_right);
        }
        res.push_back(currentLevel);
    }
    return res;
}
int countNode(NODE *pRoot) {
    if (pRoot == nullptr) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}
int sumNode(NODE *pRoot) {
    if (pRoot == nullptr) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}
int heightNode(NODE *pRoot, int value) {
    if (pRoot == nullptr) return -1;
    queue<NODE*> q;
    q.push(pRoot);
    int level = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            NODE* curr = q.front();
            q.pop();
            if (curr->key == value)
                return level + 1;
            if (curr->p_left != nullptr)
                q.push(curr->p_left);
            if (curr->p_right != nullptr)
                q.push(curr->p_right);
        }
        level++;
    }
    return -1;
}
int Level(NODE *pRoot, NODE *p) {
    if (pRoot == nullptr || p == nullptr) return -1;
    queue<NODE*> q;
    q.push(pRoot);
    int level = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            NODE* curr = q.front();
            q.pop();
            if (curr == p)
                return level;
            if (curr->p_left != nullptr)
                q.push(curr->p_left);
            if (curr->p_right != nullptr)
                q.push(curr->p_right);
        }
        level++;
    }
    return -1;
}
int countLeaf(NODE *pRoot) {
    if (pRoot == nullptr) return 0;
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}