/*
二分查找法，数组中无重复元素
*/
int binarySearch1(int a[], int left, int right, int x) {
	int mid;
	while (left < right) {
		mid = left + right;
		if (a[mid] == x) return mid;
		else if (a[mid] > x) right = mid - 1;
		else if (a[mid] < x) left = mid + 1;
	}
	return -1;
}

/*
二分查找法，数组中存在相同元素 返回一个区间
*/

vector<int> binarySearch2(int a[], int left, int right, int x) {
	/*获取lower_bound 即第一个大于等于x值的下标*/
	int l = left, r = right;
	int mid,lower,upper;
	while (l < r) {   //l==r时意味着找到唯一位置
		mid = (r + l) / 2;
		if (a[mid] >= x) r = mid;
		else l = mid + 1;
	}
	lower = l;
	l = left;
	r = right;

	while (l<r) {  //l=r时意味着找到唯一位置
		mid = (r + l) / 2;
		if (a[mid] > x) r = mid;
		else l = mid + 1;
	}
	upper = l;
	return { lower,upper };
}
