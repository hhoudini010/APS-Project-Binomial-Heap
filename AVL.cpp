#include<stdio.h> 
#include<stdlib.h> 
#include <time.h> 
#include <iostream>
#include <vector>
using namespace std;

# define ll long long int


struct Node 
{ 
	ll key; 
	struct Node *left; 
	struct Node *right; 
	ll height; 
}; 

struct Node *root = NULL;
struct Node* root1 = NULL;
struct Node* root2 = NULL;
vector<ll> nodes;


ll max(ll a, ll b) 
{ 
	return (a > b)? a : b; 
} 

ll height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 


struct Node* newNode(ll key) 
{ 
	struct Node* node = (struct Node*) 
						malloc(sizeof(struct Node)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially added at leaf 
	return(node); 
} 


struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

	
	x->right = y; 
	y->left = T2; 

	
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	
	return x; 
} 


struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

	
	y->left = x; 
	x->right = T2; 

	
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	
	return y; 
} 


ll getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

struct Node* insert(struct Node* node, ll key) 
{ 
	
	if (node == NULL) 
		return(newNode(key)); 

	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 
	else 
		return node; 

	
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	
	ll balance = getBalance(node); 

	 

 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 


	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	return node; 
} 



struct Node * minValueNode(struct Node* node) 
{ 
	struct Node* current = node; 

	/* loop down to find the leftmost leaf */
	while (current->left != NULL) 
		current = current->left; 

	return current; 
} 

ll getMin(struct Node* node)
{
	if(node == NULL)
		return -1;
	while(node->left)
		node = node->left;
	return node->key;
}

 
struct Node* deleteNode(struct Node* root, ll key) 
{ 
	 

	if (root == NULL) 
		return root; 

	 
	if ( key < root->key ) 
		root->left = deleteNode(root->left, key); 

	 
	else if( key > root->key ) 
		root->right = deleteNode(root->right, key); 

	
	else
	{ 
		 
		if( (root->left == NULL) || (root->right == NULL) ) 
		{ 
			struct Node *temp = root->left ? root->left : 
											root->right; 

			
			if (temp == NULL) 
			{ 
				temp = root; 
				root = NULL; 
			} 
			else 
			*root = *temp; 
							 
			free(temp); 
		} 
		else
		{ 
			 
			struct Node* temp = minValueNode(root->right); 

			 
			root->key = temp->key; 

			
			root->right = deleteNode(root->right, temp->key); 
		} 
	} 

	 
	if (root == NULL) 
	return root; 

	
	root->height = 1 + max(height(root->left), 
						height(root->right)); 

	 
	ll balance = getBalance(root); 

	 

	
	if (balance > 1 && getBalance(root->left) >= 0) 
		return rightRotate(root); 

	
	if (balance > 1 && getBalance(root->left) < 0) 
	{ 
		root->left = leftRotate(root->left); 
		return rightRotate(root); 
	} 

	
	if (balance < -1 && getBalance(root->right) <= 0) 
		return leftRotate(root); 

	
	if (balance < -1 && getBalance(root->right) > 0) 
	{ 
		root->right = rightRotate(root->right); 
		return leftRotate(root); 
	} 

	return root; 
} 


void InOrder(struct Node *root) 
{ 
	if(root != NULL) 
	{  
		InOrder(root->left);
		cout<<root->key<<" "; 
		InOrder(root->right); 
	} 
}
void InOrder_helper(struct Node *root) 
{ 
	if(root != NULL) 
	{  
		InOrder_helper(root->left);
		nodes.push_back(root->key);
		InOrder_helper(root->right); 
	} 
}

void merge(struct Node* root,struct Node* root1)
{
	InOrder_helper(root);
	InOrder_helper(root1);
} 

ll search(struct Node* root, ll value)
{
	if(root == NULL)
		return 0;
	else
	{
		struct Node* current = root;
		while(current)
		{
			if(current->key == value)
			{
				return 1;
			}
			else if(current->key > value)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		return 0;
	}
}


int main() 
{  
	int option;

    while(1)
    {
    	cout<<"\nMENU";
    	cout<<"\n1.Insert";
    	cout<<"\n2.Display";
    	cout<<"\n3.Delete";
    	cout<<"\n4.GetMin";
    	cout<<"\n5.Extract Min";
    	cout<<"\n6.Merge";
    	cout<<"\n7.Exit";
    	cout<<"\n Enter a number to perform an operation in an AVL Tree : ";
    	cin>>option;
    	
    	if(option == 1)
    	{
    		int n;
    		cout<<"\nEnter the number of nodes to be entered in the first AVL Tree : ";
    		cin>>n;
    		ll node_value;
    		for(int i=0;i<n;i++)
    		{
    			cout<<"\nEnter the node's value : ";
    			cin>>node_value;
    			root = insert(root,node_value);
    		}
    	}

    	else if(option == 2)
    	{
    		cout<<"\nInOrder Display of the first AVL Tree is : ";
    		InOrder(root);
    	}

    	else if(option == 3)
    	{
    		ll element;
    		cout<<"\nEnter the element to be deleted : ";
    		cin>>element;
    		int result = search(root,element);
    		if(result == 0)
    		{
    			cout<<"\nElement entered not present in the first AVL Tree.";
    		}
    		else
    		{
    			root = deleteNode(root,element);
    			cout<<"\nElement Deleted successfully..";
    		}
    	}

    	else if(option == 4)
    	{
    		cout<<"\n Minimum value node in the tree is : "<< getMin(root);
    	}

    	else if(option == 5)
    	{
    		ll min_value = getMin(root);

		    root = deleteNode(root,min_value);
		    cout<<"\n InOrder Traversal AVL Tree after Extract Min : ";
		    InOrder(root);
    	}
    	else if(option == 6)
    	{
    		int number_of_nodes;
    		cout<<"\nEnter number of nodes in the second AVL Tree : ";
    		cin>>number_of_nodes;

    		ll node_value1;
    		for(int i =0;i<number_of_nodes;i++)
    		{
    			cout<<"\nEnter Node's value : ";
    			cin>>node_value1;
    			root1 = insert(root1,node_value1);
    		}
    		cout<<"\nInorder Traversal of the second AVL Tree is : ";
    		InOrder(root1);

    		// cout<<"\nRoot : ";
    		// InOrder(root);
    		// cout<<"\nRoot1 :";
    		// InOrder(root1);
		    merge(root,root1);
			for(int i =0;i<nodes.size();i++)
				root2 = insert(root2,nodes[i]);

			root = root2;

			cout<<"\nThe newly formed Merged Tree is : ";
			InOrder(root);
			root1 = NULL;
			root2 = NULL;
			nodes.clear();
    	}
    	else if(option == 7)
    	{
    		break;
    	}
    	else
    	{
    		cout<<"\nInvalid Option..";
    	}

    }
	return 0; 
}