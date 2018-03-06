#include <iostream>
#include <queue>
using namespace std;

class SplayTree
{
public:
	struct Node
	{
		int data;
		Node *right, *left;
	};
	SplayTree()
	{
		root = NULL;
	}
	Node *rightRotate(Node *);
	Node *leftRotate(Node *);
	Node *splay(Node *, int);
	void insert(int);
	void deleteNode(int);
	void print();
private:
	Node *root;
};

int main()
{
	SplayTree st;
	st.insert(3);
	st.insert(4);
	st.insert(8);
	st.insert(1);
	st.insert(9);
	st.insert(5);
	st.deleteNode(9);
	st.insert(9);
	st.print();
	return 0;
}

SplayTree::Node *SplayTree::rightRotate(Node *node)
{
	Node *temp = node->left;
	node->left = temp->right;
	temp->right = node;
	return temp;
}

SplayTree::Node *SplayTree::leftRotate(Node *node)
{
	Node *temp = node->right;
	node->right = temp->left;
	temp->left = node;
	return temp;
}

SplayTree::Node *SplayTree::splay(Node *node, int data)
{
	if (node == NULL || node->data == data)
	{
		return node;
	}

	if (node->data > data)
	{
		if (node->left == NULL)
		{
			return node;
		}
		if (node->left->data > data)
		{
			node->left->left = splay(node->left->left, data);

			node = rightRotate(node);
		}
		else if (node ->left->data < data)
		{
			node->left->right = splay(node->left->right, data);
			if (node->left->right)
			{
				node->left = leftRotate(node->left);
			}
		}
		if (node->left)
		{
			return rightRotate(node);
		}
		return node;
	}
	else
	{
		if (node->right == NULL)
		{
			return node;
		}
		if (node->right->data > data)
		{
			node->right->left = splay(node->right->left, data);
			if (node->right->left)
			{
				node->right = rightRotate(node->right);
			}
		}
		else if (node->right->data < data)
		{
			node->right->right = splay(node->right->right, data);
		
			node = leftRotate(node);
			
		}
		if (node->right)
		{
			return leftRotate(node);
		}
		return node;
	}
}

void SplayTree::insert(int data)
{
	if (root == NULL)
	{
		Node *ins = new Node;
		ins->data = data;
		ins->left = NULL;
		ins->right = NULL;
		root = ins;
		return;
	}

	root = splay(root, data);

	if (root->data == data)
	{
		return;
	}

	Node *ins = new Node;
	ins->data = data;

	if (root->data > data)
	{
		ins->right = root;
		ins->left = root->left;
		root->left = NULL;
	}
	else
	{
		ins->left = root;
		ins->right = root->right;
		root->right = NULL;
	}
	root = ins;
}

void SplayTree::deleteNode(int data)
{
	if (!root)
	{
		return;
	}
	Node *temp = new Node;
	root = splay(root, data);

	if (root->data != data)
	{
		return;
	}

	if (!root->left)
	{
		temp = root;
		root = root->right;
	}
	else
	{
		temp = root;
		root = splay(root->left, data);
		root->right = temp->right;
	}
	delete temp;
}

void SplayTree::print()
{
	queue<Node*> tree;

	tree.push(root);
	tree.push(NULL);
	Node *node;

	while (true)
	{
		node = tree.front();
		tree.pop();
		if (!node)
		{
			cout << endl;
			if (tree.empty())
			{
				break;
			}
			tree.push(NULL);
			continue;
		}
		cout << node->data << " ";

		if (node->left)
		{
			tree.push(node->left);
		}
		if (node->right)
		{
			tree.push(node->right);
		}
	}

}