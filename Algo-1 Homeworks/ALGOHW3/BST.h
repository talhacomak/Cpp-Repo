#include <iostream>

using namespace std; 

struct node
{
	int size;
	int ordinal;
	bool color;
	node *left, *right, *parent;
};

struct RBTree{
	node *root;
	int red;
public:
	RBTree(){ 
		root = NULL; 
		red = 0;
	}
	void red_count(){
		red_count(root);
	}
	void red_count(node *root)
	{ 
	    if (root == NULL) 
	        return; 
	  
	    red_count(root->left); 
	    if(root->color) red++;
	    red_count(root->right); 
	}
	int get_red(){
		red_count();
		return red;
	}
	void insert(int size, int ordinal){
		node *newnode = new node;
		newnode->size = size;
		newnode->ordinal = ordinal;
		newnode->color = 1;
		newnode->left = newnode->right = newnode->parent = NULL;
		insert(root, newnode); 
	}
	void insert(node* root, node* newnode){
		node* root_pt = root;
		node* temp = NULL;
		if(root!=NULL){
			while(root_pt!=NULL){
				temp=root_pt;
				if(root_pt->size < newnode->size)
				    root_pt=root_pt->right;
				else
				    root_pt=root_pt->left;
			}
			newnode->parent=temp;
			if(temp->size < newnode->size)
			    temp->right=newnode;
			else
			    temp->left=newnode;
		}
		else{
		    root=newnode;
		    newnode->parent=NULL;
		}
		insert_fixup(root, newnode);
	}
	
	void insert_fixup(node* root, node* newnode){
		if(root==newnode)
		{
		   newnode->color=0;
		   return;
		}
		while(newnode->parent != NULL && newnode->parent->color == 1){
			if(newnode->parent == newnode->parent->parent->left){
				node* y = newnode->parent->parent->right;
				if(y != NULL && y->color == 1){
					newnode->parent->color = 0;
					y->color = 0;
					newnode->parent->parent->color = 1;
					newnode = newnode->parent->parent;
				}
				else{
					if(newnode == newnode->parent->right){
						newnode = newnode->parent;
						left_rotate(root, newnode);
					}
					newnode->parent->color = 0;
					newnode->parent->parent->color = 1;
					right_rotate(root, newnode->parent->parent);
				}
			}
			else{
				node* y = newnode->parent->parent->left;
				if(y != NULL && y->color == 1){
					newnode->parent->color = 0;
					y->color = 0;
					newnode->parent->parent->color = 1;
					newnode = newnode->parent->parent;
				}
				else{
					if(newnode == newnode->parent->right){
						newnode = newnode->parent;
						right_rotate(root, newnode);
					}
					newnode->color = 0;
					newnode->parent->parent->color = 1;
					left_rotate(root, newnode->parent->parent);
				}
			}
		}
	}
	
	void left_rotate(node* root, node* toRotate){
		if(toRotate->right == NULL) return;
		node* temp = toRotate->right;
		if(temp->left != NULL){
			toRotate->right = temp->left;
			temp->left->parent = toRotate;
		}
		else toRotate->right = NULL;
		
		if(toRotate->parent != NULL) temp->parent = toRotate->parent;
		if(toRotate->parent == NULL) root = temp;
		else {
			if(toRotate->parent->left == toRotate) toRotate->parent->left = temp;
			else toRotate->parent->right = temp;
		}
		temp->left = toRotate;
		toRotate->parent = temp;
	}
	
	void right_rotate(node* root, node* toRotate){
		if(toRotate->left == NULL) return;
		node* temp = toRotate->left;
		if(temp->right != NULL){
			toRotate->left = temp->right;
			temp->right->parent = toRotate;
		}
		else toRotate->left = NULL;
		
		if(toRotate->parent != NULL) temp->parent = toRotate->parent;
		if(toRotate->parent == NULL) root = temp;
		else {
			if(toRotate->parent->left == toRotate) toRotate->parent->left = temp;
			else toRotate->parent->right = temp;
		}
		temp->right = toRotate;
		toRotate->parent = temp;
	}
	
};
