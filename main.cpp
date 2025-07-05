#include <iostream>
#include <string>
using namespace std;

struct TreapNode {
    string key;
    int priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(const string& k, int p)
        : key(k), priority(p), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    TreapNode* root;

    TreapNode* rotateRight(TreapNode* y) {
        TreapNode* x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }

    TreapNode* rotateLeft(TreapNode* x) {
        TreapNode* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    TreapNode* insertRec(TreapNode* node, const string& key, int priority) {
        if (!node)
            return new TreapNode(key, priority);

        if (key < node->key) {
            node->left = insertRec(node->left, key, priority);
            if (node->left->priority > node->priority)
                node = rotateRight(node);
        } else if (key > node->key) {
            node->right = insertRec(node->right, key, priority);
            if (node->right->priority > node->priority)
                node = rotateLeft(node);
        }
        return node;
    }

    TreapNode* deleteRec(TreapNode* node, const string& key) {
        if (!node)
            return nullptr;

        if (key < node->key) {
            node->left = deleteRec(node->left, key);
        } else if (key > node->key) {
            node->right = deleteRec(node->right, key);
        } else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            if (!node->left) {
                TreapNode* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                TreapNode* temp = node->left;
                delete node;
                return temp;
            }
            if (node->left->priority > node->right->priority) {
                node = rotateRight(node);
                node->right = deleteRec(node->right, key);
            } else {
                node = rotateLeft(node);
                node->left = deleteRec(node->left, key);
            }
        }
        return node;
    }

    TreapNode* searchRec(TreapNode* node, const string& key) {
        if (!node || node->key == key)
            return node;

        if (key < node->key)
            return searchRec(node->left, key);
        return searchRec(node->right, key);
    }

    void destroyTree(TreapNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    Treap() : root(nullptr) {}

    ~Treap() {
        destroyTree(root);
    }

    void insert(const string& key, int priority) {
        root = insertRec(root, key, priority);
    }

    void deleteKey(const string& key) {
        root = deleteRec(root, key);
    }

    bool search(const string& key) {
        return searchRec(root, key) != nullptr;
    }
};
