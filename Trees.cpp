#include <iostream>
#include<algorithm> 
#include <queue>
#include <vector>
#include <stack>
using namespace std;

template <class T>
struct node {
	T data;
	node<T> * left;
	node<T> * right;
};
node<int> * createTree3() {
	node<int> * r1 = new node<int>();
	r1->data = 6;
	r1->left = NULL;
	r1->right = NULL;

	node<int> * root = new node<int>();
	root->data = 5;
	root->left = NULL;
	root->right = r1;

	return root;
}
node<int> * createTree() {
	node<int> * l11 = new node<int>();
	l11->data = 2;
	l11->left = NULL;
	l11->right = NULL;

	node<int> * l12 = new node<int>();
	l12->data = 4;
	l12->left = NULL;
	l12->right = NULL;

	node<int> * l1 = new node<int>();
	l1->data = 3;
	l1->left = l11;
	l1->right = l12;

	node<int> * r11 = new node<int>();
	r11->data = 6;
	r11->left = NULL;
	r11->right = NULL;

	node<int> * r12 = new node<int>();
	r12->data = 8;
	r12->left = NULL;
	r12->right = NULL;

	node<int> * r1 = new node<int>();
	r1->data = 7;
	r1->left = r11;
	r1->right = r12;

	node<int> * root = new node<int>();
	root->data = 5;
	root->left = l1;
	root->right = r1;

	return root;
}

node<int> * createTree2() {
	node<int> * l122 = new node<int>();
	l122->data = 10;
	l122->left = NULL;
	l122->right = NULL;

	node<int> * l12 = new node<int>();
	l12->data = 5;
	l12->left = NULL;
	l12->right = l122;

	node<int> * l1 = new node<int>();
	l1->data = 3;
	l1->left = NULL;
	l1->right = l12;

	node<int> * r1 = new node<int>();
	r1->data = 10;
	r1->left = NULL;
	r1->right = NULL;

	node<int> * root = new node<int>();
	root->data = 2;
	root->left = l1;
	root->right = r1;

	return root;
}

bool isLeaf(node<int>* n)
{
	if (n->left == NULL && n->right == NULL) return true;
	return false;
}

int height(node<int>* root)
{
	if (isLeaf(root)) return 1;
	return 1 + max(height(root->left), height(root->right));
}

int sum(node<int>* root)
{
	if (isLeaf(root)) return root->data;
	return root->data + sum(root->left) + sum(root->right);
}

int multSum(node<int>* root1, node<int>* root2)
{
	if (root1 == NULL || root2 == NULL) return 0;
	if (root1->left == NULL || root1->right == NULL)
	{
		node<int>* newnode = new node<int>();
		newnode->data = root1->data;
		if (root1->left == NULL && root2->left!=NULL) root1->left = newnode;
		if (root1->right == NULL && root2->right!=NULL) root1->right = newnode;
	}
	if (root2->left == NULL || root2->right == NULL)
	{
		node<int>* newnode = new node<int>();
		newnode->data = root2->data;
		if (root2->left == NULL && root1->left != NULL) root2->left = newnode;
		if (root2->right == NULL && root1->right != NULL) root2->right = newnode;
	}
	return ((root1->data*root2->data) + multSum(root1->left, root2->left) + multSum(root1->right, root2->right));
}

template <class T>
bool isEmpty(node<T> * root) 
{
	return NULL == root;
}

int mult(node<int> * tree1, node<int> * tree2, int lastTree1 = 0, int lastTree2 = 0) 
{
	if (isEmpty(tree1) && isEmpty(tree2)) return 0;
	if (!isEmpty(tree1)) lastTree1 = tree1->data;
	if (!isEmpty(tree2)) lastTree2 = tree2->data;
	int sum = lastTree1 * lastTree2;
	if (isEmpty(tree1))
	{
		return sum + mult(tree1, tree2->left, lastTree1, lastTree2) 
			+ mult(tree1, tree2->right, lastTree1, lastTree2);
	}
	else if (isEmpty(tree2))
	{
		return sum + mult(tree1->left, tree2, lastTree1, lastTree2) 
			+ mult(tree1->right, tree2, lastTree1, lastTree2);
	}
	else
	{
		return sum + mult(tree1->left, tree2->left, lastTree1, lastTree2) 
			+ mult(tree1->right, tree2->right, lastTree1, lastTree2);
	}
	//return sum;
}

node<int>* findElement(node<int>* root, int element)
{
	if (root == NULL) return NULL;

	if (root->data == element) return root;

	node<int>* leftSubRes = findElement(root->left, element);
	node<int>* rightSubRes = findElement(root->right, element);

	if (leftSubRes != NULL) return leftSubRes;
	if (rightSubRes != NULL) return rightSubRes;

	return NULL;
}
int sumOfLeaves(node<int>* root)
{
	if (isLeaf(root)) return root->data;
	return sumOfLeaves(root->left) + sumOfLeaves(root->right);
}
int sumLeafs(node<int> * tree) {
	if (NULL == tree) {
		return 0;
	}

	if (NULL == tree->left && NULL == tree->right) {
		return tree->data;
	}

	return sumLeafs(tree->left) + sumLeafs(tree->right);
}

int sumProduct(node<int>* root, int counter=1)
{
	if (isLeaf(root)) return root->data * counter;
	return sumProduct(root->left, counter+1) + sumProduct(root->right, counter+1);
}
int sumLeafsByHeight(node<int> * tree, int height = 1) {
	if (NULL == tree) {
		return 0;
	}

	if (NULL == tree->left && NULL == tree->right) {
		return tree->data * height;
	}

	return sumLeafsByHeight(tree->left, height + 1)
		+ sumLeafsByHeight(tree->right, height + 1);
}

void printSumByLevel(node<int>* root)
{
	if (root == NULL)
	{
		cout << "Tree is empty!" << endl;
		return;
	}
	queue<node<int>*> q;
	q.push(root);
	while (!q.empty())
	{
		int size = size = q.size();
		int sum = 0;
		while (size != 0)
		{
			if(q.front()->left!=NULL) q.push(q.front()->left);
			if (q.front()->left != NULL) q.push(q.front()->right);
			sum = sum + q.front()->data;
			q.pop();
			size--;
		}
		cout << sum << endl;
	}
}
node<int>* convertToList(node<int>* root)
{
	return nullptr;
}
node<int>* findLastElement(node<int> * l) {
	if (NULL == l) {
		return NULL;
	}
	if (NULL == l->right) {
		return l;
	}
	return findLastElement(l->right);
}
node<int>* treeToList(node<int> * root) 
{
	if (root == NULL) return NULL;
	if (isLeaf(root)) return NULL;

	if (root->left == NULL)
	{
		node<int>* rightStart = treeToList(root->right);
		root->right = rightStart;
		rightStart->left = root;
		return root;
	}
	if (root->right == NULL)
	{
		node<int>* leftStart = treeToList(root->left);
		node<int>* leftEnd = findLastElement(leftStart);
		leftEnd->right = root;
		root->left = leftEnd;
		return leftStart;
	}
	node<int>* leftStart = treeToList(root->left);
	node<int>* rightStart = treeToList(root->right);
	node<int>* leftEnd = findLastElement(leftStart);

	leftEnd->right = root;
	root->left = leftEnd;
	root->right = rightStart;
	rightStart->left = root;

	return leftStart;
}
void print(node<int>* root)
{
	if (root == NULL) return;
	stack<node<int>*> s;
	vector<node<int>*> visited;
	s.push(root);
	while (!s.empty())
	{
		node<int>* le;
		node<int>* re;
		
		vector<node<int>*>::iterator it;
		it = find(visited.begin(), visited.end(), le);
		if (le != NULL && it == visited.end())
		{
			s.push(le);
		}
		else
		{
			cout << s.top() << endl;
			visited.push_back(s.top());
			s.pop();

			vector<node<int>*>::iterator it;
			it = find(visited.begin(), visited.end(), re);
			if (re != NULL && it == visited.end())
			{
				s.push(re);
			}
		}
	}

}

node<int>* createTree(
	int data,
	node<int>* left = NULL,
	node<int>* right = NULL) {

	node<int>* root = new node<int>;
	root->data = data;
	root->left = left;
	root->right = right;
	return root;
}
node<int>* createSample() {
	return
		createTree(5,
			createTree(4,
				createTree(1,
					NULL,
					NULL),
				NULL),
			createTree(8,
				createTree(6,
					NULL,
					createTree(7)),
				createTree(9,
					NULL,
					NULL)));
}
void printList(node<int> * l) {
	if (NULL == l) {
		cout << endl;
		return;
	}
	cout << l->data << " ";
	printList(l->right);
}
int main()
{
	cout << height(createTree()) << endl;
	cout << sum(createTree()) << endl;
	cout << multSum(createTree(), createTree2()) << endl;
	cout << mult(createTree(), createTree2()) << endl << endl;
	cout << findElement(createTree(), 8)->data << endl;
	cout << findElement(createTree(), 2)->data << endl;
	cout << findElement(createTree(), 3)->data << endl;
	cout << findElement(createTree(), 4)->data << endl;
	cout << findElement(createTree(), 100) << endl;
	cout << findElement(createTree(), 6)->data << endl;
	cout << sumOfLeaves(createTree()) << endl;
	cout << sumLeafs(createTree()) << endl;
	cout << sumProduct(createTree()) << endl;
	cout << sumLeafsByHeight(createTree()) << endl << endl;
	printSumByLevel(createTree());
	cout << endl;
	node<int>* start = treeToList(createSample());
	printList(start);
	system("pause");
	return 0;
}
