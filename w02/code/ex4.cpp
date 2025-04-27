#include <iostream>
using namespace std;

int getMax (int a[], int n) {
    int mx = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > mx) {
            mx = a[i];
        }
    }
    return mx;
}
int getDayAtMaxWeight (int a[], int n, int mx) {
    int days = 0;
    int i = 0;
    while (i < n) {
        int temp = a[i];
        int j = i + 1;
        while (j < n && temp) {
            if (temp + a[j] <= mx) {
                temp += a[j];
                j++;
            }
            else {
                break;
            }
        }
        i = j;
        days++;
    }
    return days;
}
int sumWeight (int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}
int minWeight (int a[], int n, int days) {
    int low = getMax (a, n);
    int high = sumWeight(a, n);
    int res;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (getDayAtMaxWeight(a, n, mid) == days) {
            res = mid;
            high = mid - 1;
        }
        if (getDayAtMaxWeight(a, n, mid) < days) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return res;
}
int main() {
    int n;
    cin >> n;
    int a[100];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int days;
    cin >> days;
    cout << minWeight(a, n, days);
}