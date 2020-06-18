// Algorytmi_Laba_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <queue> 
#include <string>
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
	int val;
	string name = "";
	COLOR color;
	Node *left, *right, *parent;
	Node(int val, string name) : val(val), name(name) {
		parent = left = right = NULL;

		// Node is created during insertion 
		// Node is red at insertion 
		color = RED;
	}

	// returns pointer to uncle 
	Node *uncle() {
		// If no parent or grandparent, then no uncle 
		if (parent == NULL or parent->parent == NULL)
			return NULL;

		if (parent->isOnLeft())
			// uncle on right 
			return parent->parent->right;
		else
			// uncle on left 
			return parent->parent->left;
	}

	// check if node is left child of parent 
	bool isOnLeft() { return this == parent->left; }

	// returns pointer to sibling 
	Node *sibling() {
		// sibling null if no parent 
		if (parent == NULL)
			return NULL;

		if (isOnLeft())
			return parent->right;

		return parent->left;
	}

	// moves node down and moves given node in its place 
	void moveDown(Node *nParent) {
		if (parent != NULL) {
			if (isOnLeft()) {
				parent->left = nParent;
			}
			else {
				parent->right = nParent;
			}
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool hasRedChild() {
		return (left != NULL and left->color == RED) or
			(right != NULL and right->color == RED);
	}
};

class RBTree {
	Node *root;

	// left rotates the given node 
	void leftRotate(Node *x) {
		// new parent will be node's right child 
		Node *nParent = x->right;

		// update root if current node is root 
		if (x == root)
			root = nParent;

		x->moveDown(nParent);

		// connect x with new parent's left element 
		x->right = nParent->left;
		// connect new parent's left element with node 
		// if it is not null 
		if (nParent->left != NULL)
			nParent->left->parent = x;

		// connect new parent with x 
		nParent->left = x;
	}

	void rightRotate(Node *x) {
		// new parent will be node's left child 
		Node *nParent = x->left;

		// update root if current node is root 
		if (x == root)
			root = nParent;

		x->moveDown(nParent);

		// connect x with new parent's right element 
		x->left = nParent->right;
		// connect new parent's right element with node 
		// if it is not null 
		if (nParent->right != NULL)
			nParent->right->parent = x;

		// connect new parent with x 
		nParent->right = x;
	}

	void swapColors(Node *x1, Node *x2) {
		COLOR temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapValues(Node *u, Node *v) {
		int temp;
		temp = u->val;
		u->val = v->val;
		v->val = temp;
		string temp_string;
		temp_string = u->name;
		u->name = v->name;
		v->name = temp_string;
	}

	// fix red red at given node 
	void fixRedRed(Node *x) {
		// if x is root color it black and return 
		if (x == root) {
			x->color = BLACK;
			return;
		}

		// initialize parent, grandparent, uncle 
		Node *parent = x->parent, *grandparent = parent->parent,
			*uncle = x->uncle();

		if (parent->color != BLACK) {
			if (uncle != NULL && uncle->color == RED) {
				// uncle red, perform recoloring and recurse 
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			}
			else {
				// Else perform LR, LL, RL, RR 
				if (parent->isOnLeft()) {
					if (x->isOnLeft()) {
						// for left right 
						swapColors(parent, grandparent);
					}
					else {
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					// for left left and left right 
					rightRotate(grandparent);
				}
				else {
					if (x->isOnLeft()) {
						// for right left 
						rightRotate(parent);
						swapColors(x, grandparent);
					}
					else {
						swapColors(parent, grandparent);
					}

					// for right right and right left 
					leftRotate(grandparent);
				}
			}
		}
	}

	// find node that do not have a left child 
	// in the subtree of the given node 
	Node *successor(Node *x) {
		Node *temp = x;

		while (temp->left != NULL)
			temp = temp->left;

		return temp;
	}

	// find node that replaces a deleted node in BST 
	Node *BSTreplace(Node *x) {
		// when node have 2 children 
		if (x->left != NULL and x->right != NULL)
			return successor(x->right);

		// when leaf 
		if (x->left == NULL and x->right == NULL)
			return NULL;

		// when single child 
		if (x->left != NULL)
			return x->left;
		else
			return x->right;
	}

	// deletes the given node 
	void fixDoubleBlack(Node *x) {
		if (x == root)
			// Reached root 
			return;

		Node *sibling = x->sibling(), *parent = x->parent;
		if (sibling == NULL) {
			// No sibiling, double black pushed up 
			fixDoubleBlack(parent);
		}
		else {
			if (sibling->color == RED) {
				// Sibling red 
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) {
					// left case 
					rightRotate(parent);
				}
				else {
					// right case 
					leftRotate(parent);
				}
				fixDoubleBlack(x);
			}
			else {
				// Sibling black 
				if (sibling->hasRedChild()) {
					// at least 1 red children 
					if (sibling->left != NULL and sibling->left->color == RED) {
						if (sibling->isOnLeft()) {
							// left left 
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						}
						else {
							// right left 
							sibling->left->color = parent->color;
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else {
						if (sibling->isOnLeft()) {
							// left right 
							sibling->right->color = parent->color;
							leftRotate(sibling);
							rightRotate(parent);
						}
						else {
							// right right 
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							leftRotate(parent);
						}
					}
					parent->color = BLACK;
				}
				else {
					// 2 black children 
					sibling->color = RED;
					if (parent->color == BLACK)
						fixDoubleBlack(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}

	// prints level order for given node 
	void levelOrder(Node *x) {
		if (x == NULL)
			// return if node is null 
			return;

		// queue for level order 
		queue<Node *> q;
		Node *curr;

		// push x 
		q.push(x);

		while (!q.empty()) {
			// while q is not empty 
			// dequeue 
			curr = q.front();
			q.pop();

			// print node value 
			if (curr->color == 0)
			{
				cout << "Red ";
			}
			else
			{
				cout << "Black ";
			}
			cout << "node " << "population: " << curr->val << " " << "City name: " << curr->name << " " << endl;
			if (curr->left != NULL) 
			{
				if (curr->left->color == 0)
				{
					cout << "Red ";
				}
				else
				{
					cout << "Black ";
				}
				cout << "left " << "population: " << curr->left->val << " " << "City name: " << curr->left->name << " " << endl;
			}
			if (curr->right != NULL)
			{
				if (curr->right->color == 0)
				{
					cout << "Red ";
				}
				else
				{
					cout << "Black ";
				}
				cout << "right " << "population: " << curr->right->val << " " << "City name: " << curr->right->name << endl;
			}
			if (curr->left == NULL)
			{
				cout << "Black " << "left " << "NULL"<< endl;
			}
			if (curr->right == NULL)
			{
				cout << "Black " << "right "<< "NULL"<< endl;
			}
			cout << endl;
			// push children to queue 
			if (curr->left != NULL)
				q.push(curr->left);
			if (curr->right != NULL)
				q.push(curr->right);
		}
	}
public:
	// constructor 
	// initialize root 
	RBTree() { root = NULL; }

	Node *getRoot() { return root; }

	// searches for given value 
	// if found returns the node (used for delete) 
	// else returns the last node while traversing (used in insert) 
	Node *search(string city_name) 
	{
		Node *temp = root;
		while (temp != NULL) 
		{
			if (city_name < temp->name) 
			{
				if (temp->left == NULL)
					break;
				else
					temp = temp->left;
			}
			else if (city_name == temp->name) 
			{
				break;
			}
			else 
			{
				if (temp->right == NULL)
					break;
				else
					temp = temp->right;
			}
		}
		return temp;
	}
	Node *search_city(string city_name)
	{
		Node *temp = root;
		while (temp != NULL)
		{
			if (city_name < temp->name)
			{
				if (temp->left == NULL)
					break;
				else
					temp = temp->left;
			}
			else if (city_name == temp->name)
			{
				break;
			}
			else
			{
				if (temp->right == NULL)
					break;
				else
					temp = temp->right;
			}
		}
		if (temp->name == city_name)
		{
			return temp;
		}
		else
		{
			temp->name = "City not found";
			temp->val = 0;
			return temp;
		}
	}
	
	// inserts the given value to tree 
	void insert(int n, string insert_name) {
		Node *newNode = new Node(n,insert_name);
		if (root == NULL) {
			// when root is null 
			// simply insert value at root 
			newNode->color = BLACK;
			root = newNode;
		}
		else {
			Node *temp = search(insert_name);

			if (temp->name == insert_name) {
				// return if value already exists 
				return;
			}

			// if value is not found, search returns the node 
			// where the value is to be inserted 

			// connect new node to correct node 
			newNode->parent = temp;

			if (insert_name < temp->name)
				temp->left = newNode;
			else
				temp->right = newNode;

			// fix red red voilaton if exists 
			fixRedRed(newNode);
		}
	}

	// utility function that deletes the node with given value 

	// prints level order of the tree 
	void printLevelOrder() {
		cout << "Level order: " << endl;
		if (root == NULL)
			cout << "Tree is empty" << endl;
		else
			levelOrder(root);
		cout << endl;
	}
};
void fromFile(RBTree first_tree, RBTree second_tree)
{
	ifstream file;
	file.open("input.txt");
	int num = 0;
	string name = "";
	while (name != "eof")
	{
		file >> num;
		file >> name;
		first_tree.insert(num, name);
	}
	while (name != "eof")
	{
		file >> num;
		file >> name;
		second_tree.insert(num, name);
	}

}
int main() {
	RBTree first_tree, second_tree;

	/*first_tree.insert(7,"NewYork");
	first_tree.insert(3, "LosAngeles");
	first_tree.insert(18, "Chicago");
	first_tree.insert(10, "Houston");
	first_tree.insert(22, "Phoenix");

	second_tree.insert(8, "Philadelphia");
	second_tree.insert(11, "SanAntonio");
	second_tree.insert(26, "SanDiego");
    second_tree.insert(2, "SanJose");
	second_tree.insert(6, "Austin");
	second_tree.insert(14, "Jacksonville");
	second_tree.insert(30, "FortWorth");
	second_tree.insert(15, "Columbus");
	second_tree.insert(14, "SanFrancisco");
*/
	//fromFile(first_tree, second_tree);
	ifstream file;
	file.open("input.txt");
	int num = 0;
	string name = "";
	while (name != "eof")
	{
		file >> num;
		file >> name;
		if (name != "eof")
		{
			first_tree.insert(num, name);
		}
	}
	num = 0;
	name = "";
	while (name != "eof")
	{
		file >> num;
		file >> name;
		if (name != "eof")
		{
			second_tree.insert(num, name);
		}
	}
	cout << "First tree:" << endl;
	first_tree.printLevelOrder();
	cout << "Second tree:" << endl;
	second_tree.printLevelOrder();
	string city_name;
	cin >> city_name;
	Node *resultNode = first_tree.search_city(city_name);
	if (resultNode -> name == "City not found")
	{ 
		Node *resultNode = second_tree.search_city(city_name);
		cout << "Result of the search:" << resultNode->val << " " << resultNode->name << " " << endl;
	}
	else 
	{
		cout << "Result of the search:" << resultNode->val << " " << resultNode->name << " " << endl;
	}
	return 0;
}