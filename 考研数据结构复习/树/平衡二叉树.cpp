#include<iostream>
using namespace std;
struct node {
	int v, height;
	node *lchild, * rchild;
};
//�½�һ�����
node* newNode(int v) {
	node* Node = new node;
	Node->v = v;
	Node->height = 1;
	Node->lchild = Node->rchild = NULL;
	return Node;
}
//���root���������ĵ�ǰ�߶�
int getHeight(node* root) {
	if (root == NULL) return 0;
	return root->height;
}
//��ȡ����ƽ������
int getBalanceFactor(node* root) {
	return getHeight(root->lchild) - getHeight(root->rchild);
}
//���½��ĸ߶�
void updateHeight(node* root) {
	root->height = max(getHeight(root->lchild), getHeight(root->rchild));
}

//����
bool search(node* root, int x) {
	if (root == NULL) return false;
	if (x == root->v) return true;
	else if (x < root->v) search(root->lchild, x);
	else search(root->rchild, x);
}

//����
void L(node* root) {
	node* temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}
//����
void R(node* root) {
	node* temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

//����ڵ�
void insert(node*& root, int v) {
	if (root == NULL) {
		root = newNode(v);
		return;
	}
	//�����ֵ�ȵ�ǰ����ֵС
	if (v < root->v) {
		insert(root->lchild, v);
		updateHeight(root);
		if (getBalanceFactor(root) == 2) {
			if (getBalanceFactor(root->lchild) == 1) R(root);//LL��
			else if (getBalanceFactor(root->lchild) == -1) { //LR��
				L(root->lchild);
				R(root);
			}
		}
	}
	else {
		insert(root->rchild, v);
		updateHeight(root);
		if (getBalanceFactor(root) == 2) {
			if (getBalanceFactor(root->rchild) == 1) L(root);//RR��
			else if (getBalanceFactor(root->rchild) == -1) { //RL��
				L(root->rchild);
				R(root);
			}
		}
	}
}

//AVL���Ľ���
node* Create(int data[], int n) {
	node* root = NULL;
	for (int i = 0; i < n; i++) {
		insert(root, data[i]);
	}
	return root;
}