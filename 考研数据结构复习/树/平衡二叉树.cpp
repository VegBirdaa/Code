#include<iostream>
using namespace std;
struct node {
	int v, height;
	node *lchild, * rchild;
};
//新建一个结点
node* newNode(int v) {
	node* Node = new node;
	Node->v = v;
	Node->height = 1;
	Node->lchild = Node->rchild = NULL;
	return Node;
}
//获得root所在子树的当前高度
int getHeight(node* root) {
	if (root == NULL) return 0;
	return root->height;
}
//获取结点的平衡因子
int getBalanceFactor(node* root) {
	return getHeight(root->lchild) - getHeight(root->rchild);
}
//更新结点的高度
void updateHeight(node* root) {
	root->height = max(getHeight(root->lchild), getHeight(root->rchild));
}

//查找
bool search(node* root, int x) {
	if (root == NULL) return false;
	if (x == root->v) return true;
	else if (x < root->v) search(root->lchild, x);
	else search(root->rchild, x);
}

//左旋
void L(node* root) {
	node* temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}
//右旋
void R(node* root) {
	node* temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

//插入节点
void insert(node*& root, int v) {
	if (root == NULL) {
		root = newNode(v);
		return;
	}
	//插入的值比当前结点的值小
	if (v < root->v) {
		insert(root->lchild, v);
		updateHeight(root);
		if (getBalanceFactor(root) == 2) {
			if (getBalanceFactor(root->lchild) == 1) R(root);//LL型
			else if (getBalanceFactor(root->lchild) == -1) { //LR型
				L(root->lchild);
				R(root);
			}
		}
	}
	else {
		insert(root->rchild, v);
		updateHeight(root);
		if (getBalanceFactor(root) == 2) {
			if (getBalanceFactor(root->rchild) == 1) L(root);//RR型
			else if (getBalanceFactor(root->rchild) == -1) { //RL型
				L(root->rchild);
				R(root);
			}
		}
	}
}

//AVL树的建立
node* Create(int data[], int n) {
	node* root = NULL;
	for (int i = 0; i < n; i++) {
		insert(root, data[i]);
	}
	return root;
}