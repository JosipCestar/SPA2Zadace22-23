#include <iostream>
#include <math.h>
using namespace std;

struct Node
{
	int key;
	Node *left, *right, *parent;
};

class BST
{
	Node *root;

	Node* insert(int key, Node *node)
	{
		if (node == NULL)
		{
			node = new Node;
			node->key = key;
			node->left = node->right = node->parent = NULL;
		} else if (key > node->key)
		{
			node->right = insert(key, node->right);
			node->right->parent = node;
		} else
		{
			node->left = insert(key, node->left);
			node->left->parent = node;
		}
		return node;

	}

	void inorder(Node *node)
	{
		if (node == NULL)
			return;
		inorder(node->left);
		cout << node->key << ' ';
		inorder(node->right);
	}

	Node* search(int key, Node *node)
	{
		if (node == NULL || key == node->key)
			return node;
		if (key > node->key)
			return search(key, node->right);
		return search(key, node->left);
	}

	Node* find_min(Node *node)
	{
		if (node == NULL)
			return NULL;
		if (node->left == NULL)
			return node;
		return find_min(node->left);
	}

	Node* find_max(Node *node)
	{
		if (node == NULL)
			return NULL;
		if (node->right == NULL)
			return node;
		return find_min(node->right);
	}

	Node* successor(Node *node)
	{
		if (node->right != NULL)
			return find_min(node->right);

		Node *parent = node->parent;
		while (parent != NULL && node == parent->right) {
			node = parent;
			parent = node->parent;
		}

		return parent;
	}

	Node* predecessor(Node *node)
	{
		if (node->left != NULL)
			return find_max(node->left);

		Node *parent = node->parent;
		while (parent != NULL && node == parent->left) {
			node = parent;
			parent = node->parent;
		}

		return parent;
	}

public:
	BST() : root(NULL) {}

	void print()
	{
		inorder(root);
	}

	void insert(int key)
	{
		root = insert(key, root);
	}

	bool search(int key)
	{
		return search(key, root);
	}

	int find_min()
	{
		Node *node = find_min(root);
		if (node != NULL)
			return node->key;
		return -1;
	}

	int find_max()
	{
		Node *node = find_max(root);
		if (node != NULL)
			return node->key;
		return -1;
	}

	int successor(int key)
	{
		Node *node = search(key, root);
		if (node == NULL)
			return -1;
		node = successor(node);
		if (node == NULL)
			return -1;
		return node->key;
	}

	int predecessor(int key)
	{
		Node *node = search(key, root);
		if (node == NULL)
			return -1;
		node = predecessor(node);
		if (node == NULL)
			return -1;
		return node->key;
	}

    bool nodesEqual(Node* node1, Node* node2) {
        if (node1 == NULL && node2 == NULL) {
            return true;
        }
        if (node1 == NULL || node2 == NULL) {
            return false;
        }
        return nodesEqual(node1->left, node2->left) && nodesEqual(node1->right, node2->right);
    }

    bool structurallyEqual(BST T1, BST T2) {
        return nodesEqual(T1.root, T2.root);
    }

    void nthPower(Node* node, int n) {
        if (node == NULL) {
            return;
        }
        node->key = pow(node->key, n);
        nthPower(node->left, n);
        nthPower(node->right, n);
    }

    BST nthPowerBST(BST T, int n) {
        nthPower(T.root, n);
        return T;
    }
    void zbrajnajenodoe(Node* node1, Node* node2) {
        if (node1 == NULL || node2 == NULL) {
            return;
        };
        zbrajnajenodoe(node1->left, node2->left);
        node1->key += node2->key;
        zbrajnajenodoe(node1->right, node2->right);

    }
    BST BSTadd(BST T1, BST T2) {

        if (structurallyEqual(T1,T2)) {
            BST T;
            zbrajnajenodoe(T1.root, T2.root);
            return T;
        }

    }
};

int main()
{
    BST bst,bst2,bst3;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(4);
    bst.insert(9);

    bst2.insert(10);
    bst2.insert(5);
    bst2.insert(14);
    bst2.insert(2);
    bst2.insert(8);
    bst2.insert(16);



    bst2.print();
    cout << endl;
    bst.print();
    cout << endl;
    if(bst.structurallyEqual(bst,bst2))
    {
        cout << "true" << endl;
    };
    bst.BSTadd(bst,bst2);
    bst.print();
    cout << endl;
    bst.nthPowerBST(bst,2);
    bst.print();

    };
