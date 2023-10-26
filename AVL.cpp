#include "AVL.h"
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

AVL::AVL() : root(nullptr)
{
}

Node* AVL::getRoot()
{
	return root;
}

int AVL::height(Node* node)
{
	if (node == nullptr)
		return 0;
	return node->H;
}

int AVL::balanceFactor(Node* node)
{
	if (node == nullptr)
		return 0;
	return height(node->left) - height(node->right);
}

void AVL::updateHeight(Node* node)
{
	if (node == nullptr)
		return;
	node->H = std::max(height(node->left), height(node->right)) + 1;
}

Node* AVL::rotateLeft(Node* node)
{
	Node* newRoot = node->right;
	node->right = newRoot->left;
	newRoot->left = node;

	updateHeight(node);
	updateHeight(newRoot);

	return newRoot;
}

Node* AVL::rotateRight(Node* node)
{
	Node* newRoot = node->left;
	node->left = newRoot->right;
	newRoot->right = node;

	updateHeight(node);
	updateHeight(newRoot);

	return newRoot;
}

Node* AVL::insertNode(Node* node, int key) {
	if (node == nullptr)
		return new Node(key);

	if (key < node->key) {
		node->left = insertNode(node->left, key);
	}
	else if (key > node->key) {
		node->right = insertNode(node->right, key);
	}
	else {
		return node;
	}

	updateHeight(node);
	return balance(node);
}

Node* AVL::balance(Node* node) {
	int balance = balanceFactor(node);

	if (balance > 1) {
		if (balanceFactor(node->left) >= 0) {
			return rotateRight(node);
		}
		else {
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
	}
	else if (balance < -1) {
		if (balanceFactor(node->right) <= 0) {
			return rotateLeft(node);
		}
		else {
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
	}

	return node;
}
void AVL::insert(int key) {

		root = insertNode(root, key);
}

Node* AVL::deleteNode(Node* root, int key) {
	if (root == nullptr)
		return nullptr;

	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else {
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			return nullptr;
		}
		else if (root->left == nullptr) {
			Node* temp = root->right;
			temp->parent = root->parent;
			delete root;
			return temp;
		}
		else if (root->right == nullptr) {
			Node* temp = root->left;
			temp->parent = root->parent;
			delete root;
			return temp;
		}
		else {
			Node* minNode = succesor(root->right);
			root->key = minNode->key;
			root->right = deleteNode(root->right, minNode->key);
		}
	}

	return balance(root);
}

Node* AVL::deleteRepair(Node* node) {
	if (node == nullptr)
		return nullptr;

	updateHeight(node);
	int bf = balanceFactor(node);

	if (bf > 1) {
		if (balanceFactor(node->left) >= 0)
			return rotateRight(node);
		else {
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
	}

	if (bf < -1) {
		if (balanceFactor(node->right) <= 0)
			return rotateLeft(node);
		else {
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
	}

	return node;
}

void AVL::del(int key) {

	root = deleteNode(root, key);
}


void AVL::construct(std::vector<int> constrVect)
{
	for (int i = 0; i < constrVect.size(); i++)
		insert(constrVect[i]);
}
Node* AVL::maxim(Node* current)
{
	while (current->right != nullptr)
		current = current->right;

	return current;
}

Node* AVL::minim(Node* current)
{
	while (current->left != nullptr)
		current = current->left;

	return current;
}

Node* AVL::succesor(Node* x)
{
	Node* current = root;
	if (current->right != nullptr)
		current = minim(x->right);
	else {
		current = x->parent;
		while (current != nullptr && x == current->right) {
			x = current;
			current = current->parent;
		}
	}
	return current;
}

Node* AVL::predecesor(Node* x)
{
	Node* current = root;
	if (current->left != nullptr)
		current = maxim(x->left);
	else {
		current = x->parent;
		while (current != nullptr && x == current->left) {
			x = current;
			current = current->parent;
		}
	}
	return current;
}

Node* AVL::find(int key)
{
	Node* current = root;
	while (current != nullptr && current->key != key) {
		if (key < current->key)
			current = current->left;
		else
			current = current->right;
	}
	return current;
}

void AVL::preordine(Node* root) {
	if (root == nullptr) return;
	std::cout << root->key << " (" << root->H << ") ";
	preordine(root->left);
	preordine(root->right);
}
void AVL::inordine(Node* root) {
	if (root == nullptr) return;
	inordine(root->left);
	std::cout << root->key << " (" << root->H << ") ";
	inordine(root->right);
}
void AVL::postordine(Node* root) {
	if (root == nullptr) return;
	postordine(root->left);
	postordine(root->right);
	std::cout << root->key << " (" << root->H << ") ";
}

void AVL::niveluri() {
	if (root == nullptr) {
		return;
	}

	std::queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* current = q.front();
		q.pop();

		std::cout << current->key << " (" << current->H << ") ";

		if (current->left != nullptr) {
			q.push(current->left);
		}

		if (current->right != nullptr) {
			q.push(current->right);
		}
	}
}
void AVL::print_tree(int opt)
{
	switch (opt) {
	case 1:
		preordine(root);
		break;
	case 2:
		inordine(root);
		break;
	case 3:
		postordine(root);
		break;
	case 4:
		niveluri();
		break;
	default:
		std::cout << "Cazul nu exista\n";
		break;
	}
}

bool AVL::empty() {
	if (root == nullptr)
		return true;
	return false;
}

void AVL::clear()
{
	erase(root);
	root = nullptr;
}

void AVL::erase(Node* x)
{
	if (x == nullptr)
		return;

	erase(x->left);
	erase(x->right);
	delete x;
}
