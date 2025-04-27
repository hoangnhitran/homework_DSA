#include <iostream>
using namespace std;
int linearSearchWithSentinal(int a[], int n, int k) {
	a[n] = k;
	int i = 0;
	while (a[i] != k) {
		i++;
	}
	if (i == n) {
		return -1;
	}
	else {
		return i;
	}
}
int main() {
	int n;
	cin >> n;
	int a[100];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int k;
	cin >> k;
	cout << linearSearchWithSentinal(a, n, k);
}