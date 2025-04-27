#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct NODE{
    int key;
    NODE* p_next;
};
struct Queue{
    NODE* head;
    NODE* tail;
};
Queue* initializeQueue() {
    Queue* q = new Queue;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}
NODE *createNode(int data)
{
    NODE* temp = new NODE;
    temp->key = data;
    temp->p_next = nullptr;
    return temp;
}
void enqueue (Queue* q, int key) {
    NODE* temp = createNode(key);
    if (q->head == nullptr) {
        q->head = q->tail = temp;
        return;
    }
    q->tail->p_next = temp;
    q->tail = temp;
    return;
}
int dequeue (Queue* q) {
    if (q->head == nullptr) {
        return -1;
    }
    NODE* temp = q->head;
    q->head = temp->p_next;
    if (q->head == nullptr) {
        q->tail = nullptr;
    }
    int value = temp->key;
    delete temp;
    return value;
}
int size (Queue* q) {
    NODE* p = q->head;
    int sz = 0;
    while (p != nullptr) {
        sz++;
        p = p->p_next;
    }
    return sz;
}
bool isEmpty (Queue* s) {
    return s->head == nullptr;
}
void display(Queue *s, ofstream &ofs) {
    NODE* p = s->head;
    if (isEmpty(s)) {
        ofs << "EMPTY" << endl;
        return;
    }
    while (p != nullptr) {
        ofs << p->key << " ";
        p = p->p_next;
    }
    ofs << endl;
    return;
}
void freeQueue(Queue* q)
{
    NODE *current = q->head;
    while (current)
    {
        NODE *next = current->p_next;
        delete current;
        current = next;
    }
    delete q;
}
int main() {
    Queue* st = nullptr;
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
            st = initializeQueue();
            display(st, ofs);
        }
        else if (strcmp(token, "enqueue") == 0){
            token = strtok(NULL, " ");
            enqueue(st, atoi(token));
            display(st, ofs);
        }
        else if (strcmp(token, "dequeue") == 0) {
            dequeue(st);
            display(st, ofs);
        }
    }
    ifs.close();
    ofs.close();
    freeQueue(st);
}