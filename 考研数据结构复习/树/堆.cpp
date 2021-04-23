#include<iostream>
#include<vector>
using namespace std;

//用向量储存堆，从下标1开始
vector<int> heap;

//对heap数组在[low,high]范围内进行向下调整
void downAdjust(int low, int high) {
	int i = low, j = i * 2;  //i 代表要向下调整的结点、j 代表其左子结点
	while (j <= high) {
		//如果右子结点的值大于左子结点的值
		if (j + 1 <= high && heap[j + 1] > heap[j]) 
			j = j + 1; //j 设置为右子结点的下标
		//如果子大于父
		if (heap[j] > heap[i]) {
			swap(heap[j], heap[i]);
			i = j; //继续调整
			j = i * 2;
		}
		else
			break;
	}
}
//初始化堆
void initHeap(int n) {
	for (int i = n / 2; i >= 1; i++)
		downAdjust(i, n);
}

//删除堆顶元素
void deleteTop(int &n) {
	heap[1] = heap[n--];
	downAdjust(1, n);
}

//对heap在[low,high]范围上向上调整
void upAdjust(int low, int high) {
	int i = high, j = i / 2;
	while (j >= low) {
		if (heap[j] < heap[i]) {
			swap(heap[j], heap[i]);
			i = j;
			j = i / 2;
		}
		else
			break;
	}
}

//添加元素x
void insert(int  x, int &n){
	heap[n++]=x;
	upAdjust(1, n);
}