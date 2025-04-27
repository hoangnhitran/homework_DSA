#include <iostream>
using namespace std;
int minOfRotatedArrangedArray(int a[], int n) {
	int low = 0, high = n - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (a[mid] > a[low]) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return a[low];
}
int main() {
	int n;
	cin >> n;
	int a[100];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << minOfRotatedArrangedArray(a, n);
}

