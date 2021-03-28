/*Talha Çomak
 150160726
*/
#include <iostream>
#include <vector>
#include <climits>
#include "hw3.h"

using namespace std;

struct node {
	int size;
	int ordinal;
};

struct Node {
	int size;
	int ordinal;
	int order_num; // sýra numarasý
	bool color;  // black = 0, red = 1;
	Node* left, * right, * parent;
	Node* sibling(Node* x) {
		if (x->parent == NULL)
			return NULL;

		if (x->parent->left)
			return x->parent->right;

		return x->parent->left;
	}
	bool hasRedChild() {
		return (left != NULL && left->color == 1) || (right != NULL && right->color == 1);
	}
};

void swapValues(Node* u, Node* v) {
	int size, ordinal;
	size = u->size;
	ordinal = u->ordinal;
	u->size = v->size;
	u->ordinal = v->ordinal;
	v->size = size;
	v->ordinal = ordinal;
}

class RBTree
{
	Node* root;
	int red;
	int order;
	Node* result_node;
public:
	RBTree() {
		root = NULL;
		result_node = NULL;
		red = 0;
		order = 0;
	}
	node result() {
		order = 0;
		return { result_node->size, result_node->ordinal };
	}
	void delete_node() {
		deleteNode(result_node);
	}
	void red_count() {
		red_count(root);
	}
	void red_count(Node* root)
	{
		if (root == NULL)
			return;

		red_count(root->left);
		if (root->color) red++;
		red_count(root->right);
	}
	void inorder() {
		inorder(root);
	}
	void inorder(Node* root)
	{
		if (root == NULL)
			return;
		inorder(root->left);
		cout << root->size << " " << root->ordinal << " " << root->color << " ";
		inorder(root->right);
	}
	void inorder_find(int given_order) {
		inorder_find(root, given_order);
	}
	void inorder_find(Node* root, int given_order)
	{
		if (root == NULL)
			return;

		inorder_find(root->left, given_order);
		order++;
		if (order == given_order) {
			result_node = root;
			return;
		}
		if (order > given_order) return;
		inorder_find(root->right, given_order);
	}
	int get_red() {
		red_count();
		return red;
	}
	node leftmostNode() {
		Node* x = root;
		if (root == NULL) return { -1453, -1 };
		while (x->left != NULL) {
			x = x->left;
		}
		result_node = x;
		return { x->size, x->ordinal };
	}


	void insert(int size, int ordinal) {
		Node* temp = new Node;
		temp->size = size;
		temp->ordinal = ordinal;
		temp->color = 1;
		temp->order_num = 0;
		temp->left = temp->right = temp->parent = NULL;
		this->root = insert(root, temp);
		rotateOrRecolor(temp);
	}

	Node* insert(Node* root, Node* temp) {
		if (root == NULL)
			return temp;
		if (temp->size < root->size){
			root->left = insert(root->left, temp);
			root->left->parent = root;
		}
		else if (temp->size >= root->size){
			root->right = insert(root->right, temp);
			root->right->parent = root;
		}
		return root;
	}
	Node* replace(Node* temp) {
		if (temp->left == NULL && temp->right == NULL)
			return NULL;
		if (temp->left != NULL && temp->right != NULL) {
			while (temp->left != NULL)
				temp = temp->left;
			return temp;
		}
		if (temp->left != NULL)
			return temp->left;
		else
			return temp->right;
	}


	void fixDoubleBlack(Node* x) {
		if (x == root) return;
		Node* sibling = x->sibling(x), * parent = x->parent;
		if (sibling == NULL) {
			fixDoubleBlack(parent);
		}
		else {
			if (sibling->color) {
				parent->color = 1;
				sibling->color = 0;
				if (sibling == sibling->parent->left) {
					rotateRight(parent);
				}
				else {
					rotateLeft(parent);
				}
				fixDoubleBlack(x);
			}
			else {
				if (sibling->hasRedChild()) {
					if (sibling->left != NULL && sibling->left->color == 1) {
						if (sibling == sibling->parent->left) {
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rotateRight(parent);
						}
						else {
							sibling->left->color = parent->color;
							rotateRight(sibling);
							rotateLeft(parent);
						}
					}
					else {
						if (sibling == sibling->parent->left) {
							sibling->right->color = parent->color;
							rotateLeft(sibling);
							rotateRight(parent);
						}
						else {
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							rotateLeft(parent);
						}
					}
					parent->color = 0;
				}
				else {
					sibling->color = 1;
					if (parent->color == 0)
						fixDoubleBlack(parent);
					else
						parent->color = 0;
				}
			}
		}
	}

	void deleteNode(Node* v) {
		Node* u = replace(v);
		Node* parent = v->parent;

		if (u == NULL) {
			if (v == root) {
				root = NULL;
			}
			else {
				if ((u != NULL && u->color) || v->color) {
					if (v->parent->left != NULL) v->parent->left->color = 1;
				}
				else fixDoubleBlack(v);

				if (v == v->parent->left) {
					parent->left = NULL;
				}
				else {
					parent->right = NULL;
				}
			}
			delete v;
			return;
		}
		if (v->left == NULL || v->right == NULL) {
			if (v == root) {
				v->size = u->size;
				v->ordinal = u->ordinal;
				v->left = v->right = NULL;
				delete u;
			}
			else {
				if (v == v->parent->left) {
					parent->left = u;
				}
				else {
					parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (u->color) u->color = 0;
				else fixDoubleBlack(u);
			}
			return;
		}
		swapValues(u, v);
		deleteNode(u);
	}

	void rotateOrRecolor(Node*& temp) {
		Node* pp = NULL;
		Node* gp = NULL;
		while (temp != root && temp->color && temp->parent != NULL)
		{
			if (temp->parent->color == 0) break;
			pp = temp->parent;
			gp = temp->parent->parent;

			if (pp != gp->left){
				if (gp->left != NULL && gp->left->color) {
					gp->color = 1;
					pp->color = 0;
					gp->left->color = 0;
					temp = gp;
				}
				else {
					if (temp == pp->left) {
						rotateRight(pp);
						temp = pp;
						pp = temp->parent;
					}
					rotateLeft( gp);
					swap(pp->color, gp->color);
					temp = pp;
				}
			}
			else {
				if (gp->right != NULL && gp->right->color) {
					gp->color = 1;
					pp->color = 0;
					gp->right->color = 0;
					temp = gp;
				}
				else {
					if (temp == pp->right) {
						rotateLeft(pp);
						temp = pp;
						pp = temp->parent;
					}
					rotateRight(gp);
					swap(pp->color, gp->color);
					temp = pp;
				}
			}
		}
		root->color = 0;
	}

	void rotateLeft(Node*& toRotate) {
		Node* temp = toRotate->right;
		toRotate->right = temp->left;
		if (toRotate->right != NULL)
			toRotate->right->parent = toRotate;
		temp->parent = toRotate->parent;
		if (toRotate->parent == NULL)
			root = temp;
		else if (toRotate == toRotate->parent->left)
			toRotate->parent->left = temp;
		else
			toRotate->parent->right = temp;
		temp->left = toRotate;
		toRotate->parent = temp;
	}

	void rotateRight(Node* toRotate) {
		Node* temp = toRotate->left;
		toRotate->left = temp->right;
		if (toRotate->left != NULL)
			toRotate->left->parent = toRotate;
		temp->parent = toRotate->parent;
		if (toRotate->parent == NULL)
			root = temp;
		else if (toRotate == toRotate->parent->left)
			toRotate->parent->left = temp;
		else toRotate->parent->right = temp;
		temp->right = toRotate;
		toRotate->parent = temp;
	}

};



HW3_Result hw3(int eastWarehousePackageCount, int eastWarehousePackageSizes[], int eastWarehousePackageOrdinals[],
	int westWarehousePackageCount, int westWarehousePackageSizes[], int westWarehousePackageOrdinals[]) {
	int i = 0;
	RBTree east;
	RBTree west;
	for (; i < eastWarehousePackageCount && i < westWarehousePackageCount; i++) {
		east.insert(eastWarehousePackageSizes[i], eastWarehousePackageOrdinals[i]);
		west.insert(westWarehousePackageSizes[i], westWarehousePackageOrdinals[i]);
	}
	int higher = eastWarehousePackageCount > westWarehousePackageCount ? eastWarehousePackageCount : westWarehousePackageCount;
	if (higher == eastWarehousePackageCount) {
		for (; i < higher; i++) {
			east.insert(eastWarehousePackageSizes[i], eastWarehousePackageOrdinals[i]);
		}
	}
	else {
		for (; i < higher; i++) {
			west.insert(westWarehousePackageSizes[i], westWarehousePackageOrdinals[i]);
		}
	}

	node onepack = east.leftmostNode();
	vector <node> package;
	package.push_back(onepack);
	east.delete_node();
	eastWarehousePackageCount--;
	onepack = east.leftmostNode();
	while (onepack.size == package[0].size) {
		if (onepack.size == -1453) break;
		east.delete_node();
		package.push_back(onepack);
		onepack = east.leftmostNode();
		eastWarehousePackageCount--;
	}

	int low_ordinal = INT_MAX;
	int k = package.size();
	for (i = 0; i < k; i++) {
		if (package[i].ordinal < low_ordinal) low_ordinal = package[i].ordinal;
	}
	while (westWarehousePackageCount != 0 && eastWarehousePackageCount != 0) {
		//WESTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
		vector <node> tempPack;
		if (low_ordinal <= westWarehousePackageCount) {
			west.inorder_find(low_ordinal);
			onepack = west.result();
			tempPack.push_back(onepack);
			west.delete_node();
			westWarehousePackageCount--;
			k = package.size();
			for (i = 0; i < k; i++) {
				if (package.size() == INT_MAX) break;
				westWarehousePackageCount++;
				west.insert(package[i].size, package[i].ordinal);
			}
			package.clear();
			package.push_back({ tempPack[0].size, tempPack[0].ordinal });
			tempPack.clear();
		}
		else {
			package.clear();
			onepack = west.leftmostNode();
			package.push_back(onepack);
			west.delete_node();
			westWarehousePackageCount--;
			onepack = west.leftmostNode();
			while (onepack.size == package[0].size) {
				if (onepack.size == -1453) break;
				package.push_back(onepack);
				westWarehousePackageCount--;
				west.delete_node();
				onepack = west.leftmostNode();
			}
		}
		low_ordinal = INT_MAX;
		k = package.size();
		for (i = 0; i < k; i++) {
			if (package[i].ordinal < low_ordinal) low_ordinal = package[i].ordinal;
		}

		if (westWarehousePackageCount == 0 || eastWarehousePackageCount == 0) break;

		//EASTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
		if (low_ordinal <= eastWarehousePackageCount) {
			east.inorder_find(low_ordinal);
			onepack = east.result();
			tempPack.push_back(onepack);
			east.delete_node();
			eastWarehousePackageCount--;
			k = package.size();
			for (i = 0; i < k; i++) {
				if (package.size() == INT_MAX) break;
				eastWarehousePackageCount++;
				east.insert(package[i].size, package[i].ordinal);
			}
			package.clear();
			package.push_back({ tempPack[0].size, tempPack[0].ordinal });
			tempPack.clear();
		}
		else {
			package.clear();
			onepack = east.leftmostNode();
			package.push_back(onepack);
			east.delete_node();
			eastWarehousePackageCount--;
			onepack = east.leftmostNode();
			while (onepack.size == package[0].size) {
				if (onepack.size == -1453) break;
				package.push_back(onepack);
				eastWarehousePackageCount--;
				east.delete_node();
				onepack = east.leftmostNode();
			}
		}
		low_ordinal = INT_MAX;
		k = package.size();
		for (i = 0; i < k; i++) {
			if (package[i].ordinal < low_ordinal) low_ordinal = package[i].ordinal;
		}
	}
	int red;
	int count;
	if (eastWarehousePackageCount == 0) {
		k = package.size();
		for (i = 0; i < k; i++) {
			westWarehousePackageCount++;
			west.insert(package[i].size, package[i].ordinal);
		}
		package.clear();
		count = westWarehousePackageCount;
		red = west.get_red();
	}
	else {
		k = package.size();
		for (i = 0; i < k; i++) {
			eastWarehousePackageCount++;
			east.insert(package[i].size, package[i].ordinal);
		}
		package.clear();
		count = eastWarehousePackageCount;
		red = east.get_red();
	}

	return { count, red, count - red };
}
