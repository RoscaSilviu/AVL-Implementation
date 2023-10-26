#pragma once
#include <iostream>
#include <vector>

struct Node {
    int key;
    int H;
    Node* parent;
    Node* left;
    Node* right;
    Node(int key) : key(key), H(1), parent(nullptr), left(nullptr), right(nullptr) {}
};

class AVL {
private:
    Node* root;

    Node* balance(Node* node);
    int height(Node* node);
    int balanceFactor(Node* node);
    void updateHeight(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* insertNode(Node* node, int key);
    Node* succesor(Node* x);
    Node* predecesor(Node* x);
    Node* deleteRepair(Node* node);
    Node* deleteNode(Node* root, int key);
    Node* rot_st(Node* nod);
    Node* rot_dr(Node* nod);
    void erase(Node* x);
    void preordine(Node* root);
    void inordine(Node* root);
    void postordine(Node* root);

public:
    AVL();
    Node* getRoot();
    void insert(int key);
    void del(int key);
    void print_tree(int opt);
    void niveluri();
    void construct(std::vector<int> constrVect);
    bool empty();
    Node* maxim(Node* current);
    Node* minim(Node* current);
    Node* find(int key);
    void clear();
};