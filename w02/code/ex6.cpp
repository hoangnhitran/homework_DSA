#include <iostream>
using namespace std;
bool twoSum (int a[], int n, int target) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int sum = a[left] + a[right];
        if (sum > target) {
            right--;
        } else if (sum < target) {
            left++;
        } else {
            return true;
        }
    }
    return false;
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
    if (twoSum (a, n, target)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}