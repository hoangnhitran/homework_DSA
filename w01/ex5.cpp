#include <iostream>
using namespace std;
bool isAscending (int arr[], int n){
    //base case
    if(n == 1 || n == 0) {
    return true;
    }
    if (arr[0] > arr[1]) {
        return false;
    }
    return isAscending (arr + 1, n - 1);
}
bool isDescending (int arr[], int n) {
    //base case
    if(n == 1 || n == 0) {
        return true;
        }
        if (arr[0] < arr[1]) {
            return false;
        }
        return isDescending (arr + 1, n - 1);
}
int main() {
    int n;
    cout << "Enter number of elements in the array: ";
    cin >> n;
    int a[100];
    cout << "Enter the array: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (isAscending(a, n) || isDescending(a, n)) {
        cout << "The array is sorted.";
    } else {
        cout << "The array is NOT sorted.";
    }
}