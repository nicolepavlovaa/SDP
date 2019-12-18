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

template <class T>
bool isEmpty(node<T> * root)
{
	return NULL == root;
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

void mirror(node<int>* root)
{
	if (root == NULL) return;
	node<int>* temp; 
	mirror(root->left);
	mirror(root->right);
	temp = root->left;
	root->left = root->right;
	root->right = temp;
}
void printPaths(node<int>* root, queue<int> path, int len)
{
	if (root == NULL) return;
	path.push(root->data);
	if (isLeaf(root))
	{
		while (!path.empty())
		{
			cout << path.front() << " ";
			path.pop();
		}
		cout << endl;
	}
	printPaths(root->left, path, len + 1);
	printPaths(root->right, path, len + 1);

}
void printRootToLeafPath(node<int>* root)
{
	queue<int> path;
	printPaths(root, path, 0);
}
void oddPositionOddLevel(node<int>* root)
{
	if (root == NULL) return;

	queue<node<int>*> q;
	q.push(root);
	bool evenRow = true;
	while (!q.empty())
	{
		int size = q.size();
		bool evenPos = true;

		while (size != 0)
		{
			if (!evenPos && !evenRow) cout << q.front() << " ";
			if (q.front()->left != NULL) q.push(q.front()->left);
			if (q.front()->right != NULL) q.push(q.front()->right);
			
			q.pop();
			size--;
			evenPos = !evenPos;
		}
		evenRow = !evenRow;
	}
}
node<int>* concatenate(node<int>* first, node<int>* second)
{
	if (first == NULL) return second;
	if (second == NULL) return first;

	node<int>* lastF = first->left;
	node<int>* lastS = second->left;

	lastF->right = second;
	second->left = lastF;
	lastS->right = first;
	first->left = lastS;

	return first;
}
node<int>* treeToCDLL(node<int>* root)
{
	if (root == NULL) return NULL;
	node<int>* leftsub = treeToCDLL(root->left);
	node<int>* rightsub = treeToCDLL(root->right);

	root->left = root->right = root;

	return concatenate(concatenate(leftsub, root), rightsub);
}

node<int>* treeToDLL(node<int>* root)
{
	if (root == NULL) return NULL;
	if (isLeaf(root)) return root;
	if (root->left == NULL)
	{
		node<int>* rightStart = treeToDLL(root->right);
		root->right = rightStart;
		rightStart->left = root;

		return root;
	}
	if (root->right == NULL)
	{
		node<int>* leftStart = treeToDLL(root->left);
		node<int>* leftEnd = findLastElement(leftStart);
		leftEnd->right = root;
		root->left = leftEnd;

		return leftStart;
	}
	node<int>* leftStart = treeToDLL(root->left);
	node<int>* leftEnd = findLastElement(leftStart);
	node<int>* rightStart = treeToDLL(root->right);
	leftEnd->right = root;
	root->left = leftEnd;
	root->right = rightStart;
	rightStart->left = root;

	return leftStart;
}
void printList(node<int> * l) {
	if (NULL == l) {
		cout << endl;
		return;
	}
	cout << l->data << " ";
	printList(l->right);
}
void printCList(node<int>* root)
{
	cout << "Circular Linked List is :\n";
	node<int>* itr = root;
	do
	{
		cout << itr->data << " ";
		itr = itr->right;
	} while (root!= itr);
	cout << endl;
}
void inOrder(node<int>* root)
{
	stack<node<int>*> s;
	node<int>* curr = root;

	while (curr != NULL || !s.empty())
	{
		while (curr!= NULL)
		{
			s.push(curr);
			curr = curr->left;
		}
		curr = s.top();
		s.pop();

		cout << curr->data << " ";
		curr = curr->right;
	}
}
int main()
{
	printRootToLeafPath(createSample());
	cout << endl;
	node<int>* start = treeToDLL(createSample());
	node<int>* start2 = treeToCDLL(createSample());
	printList(start);
	cout << endl;
	printCList(start2);
	system("pause");
	return 0;
}