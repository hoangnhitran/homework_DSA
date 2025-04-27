#include <iostream>
using namespace std;
int minLength (int a[], int n, int target) {
    int min_length = n;
    int left = 0;
    int sum = 0;
    for (int right = 0; right < n; right++) {
        sum += a[right];
        while (sum > target) {
            sum -= a[left];
            left++;
        }
        if (sum == target) {
            if (min_length > right - left + 1) {
                min_length = right - left + 1;
            }
        }
    }
    if (min_length != n) {
        return min_length;
    }
    else {
        return 0;
    }
}
int main() {
    int n;
    cin >> n;
    int a[100];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int target;
    cin >> target;
    cout << minLength (a, n, target);
}