#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct NODE{
    int key;
    NODE* p_next;
};
struct Stack{
    NODE* top;
};
Stack* initializeStack() {
    Stack* st = new Stack;
    st->top = nullptr;
    return st;
}
NODE *createNode(int data)
{
    NODE* temp = new NODE;
    temp->key = data;
    temp->p_next = nullptr;
    return temp;
}
void push (Stack* s, int key) {
    NODE* temp = createNode(key);
    temp->p_next = s->top;
    s->top = temp;
}
int pop (Stack* s) {
    if (s->top == nullptr) {
        return -1;
    }
    NODE* temp = s->top;
    s->top = temp->p_next;
    int value = temp->key;
    delete temp;
    return value;
}
int size (Stack s) {
    NODE* p = s.top;
    int sz = 0;
    while (p != nullptr) {
        sz++;
        p = p->p_next;
    }
    return sz;
}
bool isEmpty (Stack* s) {
    return s->top == nullptr;
}
void display(Stack *s, ofstream &ofs) {
    NODE* p = s->top;
    if (isEmpty(s)) {
        ofs << "EMPTY" << endl;
        return;
    }
    int arr[100];
    int n = 0;
    while (p != nullptr) {
        arr[n] = p->key;
        n++;
        p = p->p_next;
    }
    for (int i = n - 1; i >= 0; i--) {
        ofs << arr[i] << " ";
    }
    ofs << endl;
    return;
}
void freeStack(Stack* s)
{
    NODE *current = s->top;
    while (current)
    {
        NODE *next = current->p_next;
        delete current;
        current = next;
    }
    delete s;
}
int main() {
    Stack* st = nullptr;
    ifstream ifs ("input.txt");
    if (!ifs.is_open()) {
        cout << "Can not open the input file.";
        return 1;
    }
    ofstream ofs ("output.txt", ios:: app);
    if (!ofs.is_open()) {
        cout << "Can not create an output file.";
        return 1;
    }
    char operation[100];
    while (ifs.getline (operation, 100)) {
        char* token = strtok (operation, " ");
        if (strcmp(token, "init") == 0) {
            st = initializeStack();
            display(st, ofs);
        }
        else if (strcmp(token, "push") == 0){
            token = strtok(NULL, " ");
            push(st, atoi(token));
            display(st, ofs);
        }
        else if (strcmp(token, "pop") == 0) {
            pop(st);
            display(st, ofs);
        }
    }
    ifs.close();
    ofs.close();
    freeStack(st);
}