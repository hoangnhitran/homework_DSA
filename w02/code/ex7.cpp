#include <iostream>
using namespace std;
void sorting(int a[], int n) {
	for (int step = 1; step < n; step++) {
		int key = a[step];
		int j = step - 1;
		while (j >= 0 && key < a[j]) {
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = key;
	}
}
void triplet(int a[], int n) {
	sorting(a, n);
	for (int i = 1; i < n - 1; i++) {
        if (i > 1 && a[i] == a[i - 2]) {
            continue;
        }
        int left = i - 1;
        int right = i + 1;
        while (left >= 0 && right < n) {
            int sum = a[left] + a[right] + a[i];
            if (sum > 0) {
                left--;
            } else if (sum < 0) {
                right++;
            } else {
                cout << "[" << a[left] << ", " << a[i] << ", " << a[right] << "]";
                while (a[left] == a[left - 1]) {
                    left--;
                }
                while (a[right] == a[right + 1]) {
                    right++;
                }
                left--;
                right++;
            }
        }

    }
}
int main() {
	int n;
	cin >> n;
	int a[100];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
    cout << "[";
	triplet(a, n);
    cout << "]";
}