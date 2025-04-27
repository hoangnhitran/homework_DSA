#include "function.h"
int getMax (int a[], int n) {
    int mx = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > mx) {
            mx = a[i];
        }
    }
    return mx;
}
int getMin(int a[], int n) {
    int mn = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] < mn) {
            mn = a[i];
        }
    }
    return mn;
}
void swap (int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
void bubbleSort(int a[], int n) {
    for (int step = 0; step < n - 1; step++) {
        bool swapped = false;
        for (int i = 0; i < n - step - 1; i++) {
            if (a[i] > a[i + 1]) {
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
void countingSort(int a[], int n) {
    int mx = getMax(a, n);
    int mn = getMin(a, n);
    int size = mx - mn + 1;
    int count[100000];
    for (int i = 0; i < size; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[a[i] - mn]++;
    }
    // Sửa lỗi: bắt đầu vòng lặp từ i = 1 thay vì i = 0
    for (int i = 1; i < size; i++) {
        count[i] += count[i - 1];
    }
    int output[100000]; // cần lưu tạm vào 1 mảng khác để không thay đổi giá trị của các phần tử trên mảng a khi chưa sử dụng
    // Sắp xếp lại mảng theo thứ tự đúng
    for (int i = n - 1; i >= 0; i--) { // duyệt mảng từ cuối để đảm bảo tính ổn định của thuật toán, tức nếu 2 số bằng nhau, số ở sau sẽ vẫn ở sau.
        output[count[a[i] - mn] - 1] = a[i];
        count[a[i] - mn]--;
    }
    // Sao chép mảng đã sắp xếp vào mảng gốc
    for (int i = 0; i < n; i++) {
        a[i] = output[i];
    }
}
void heapify (int a[], int n, int i) { // build max heap từ nút cha hiện tại truyền vào và đệ quy để build lại các max heap các nút phía dưới
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && a[left] > a[largest]) {
        largest = left;
    }
    if (right < n && a[right] > a[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap (a[i], a[largest]);
        heapify(a, n, largest);
    }
}
void heapSort (int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) { // duyệt cây từ nút cha nhỏ nhất bên phải cùng đến nút gốc
        heapify(a, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]); // move the largest element to the end
        heapify(a, i, 0); // heapify the reduced heap
    }
}
void insertionSort(int a[], int n) {
    for (int step = 1; step < n; step++) {
        int key = a[step];
        int j = step - 1;
        while (j >= 0 && key < a[j]) {
            a[j + 1] = a[j]; // dich chuyen cac phan tu phia sau de chua cho cho phan tu chen vao truoc
            --j;
        }
        a[j + 1] = key; //chen key vao sau phan tu nho hon no dau tien
    }
}
void merge (int a[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[100000], M[100000];
    for (int i = 0; i < n1; i++) {
        L[i] = a[p + i];
    }
    for (int i = 0; i < n2; i++) {
        M[i] = a[q + 1 + i];
    }
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = M[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = M[j];
        j++;
        k++;
    }
}
void mergeDivide (int a[], int p, int r) {
    if (p >= r) {
        return;
    }
    int q = (p + r)/2;
    mergeDivide (a, p, q);
    mergeDivide (a, q + 1, r);
    merge(a, p, q, r);
}
void mergeSort (int a[], int n) {
    int p = 0;
    int r = n - 1;
    mergeDivide (a, p, r);
}
int divide(int a[], int left, int right) {
    int pivotValue = a[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (a[i] < pivotValue) {
            i++;
        }
        while (a[j] > pivotValue) {
            j--;
        }
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    return i;
}

void quick(int a[], int left, int right) {
    if (left < right) {
        int pivot = divide(a, left, right);
        quick(a, left, pivot - 1);
        quick(a, pivot, right);
    }
}

void quickSort(int a[], int n) {
    quick(a, 0, n - 1);
}
void countingSort (int a[], int n, int ex) {
    int count[19] = {0};
    for (int i = 0; i < n; i++) {
      count[(a[i]/ex) % 10 + 9]++;
    }
    for (int i = 1; i <= 19; i++) {
      count[i]+= count[i - 1];
    }
    int res[100000];
    for (int i = n - 1; i >= 0; i--) {
      res[count[(a[i]/ex) % 10 + 9] - 1] = a[i];
      count[(a[i]/ex) % 10 + 9]--;
    }
    for (int i = 0; i < n; i++) {
      a[i] = res[i];
    }
}
void radixSort (int a[], int n) {
    int mx = getMax(a, n);
    for (int ex = 1; mx / ex > 0; ex *= 10) {
      countingSort(a, n, ex);
    }
}
void selectionSort(int a[], int n) {
    for (int step = 0; step < n - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < n; i++) {
            if (a[i] < a[min_idx]) {
                min_idx = i;
            }
        }
        swap(a[min_idx], a[step]);
    }
}
void shellSort (int arr[], int n) {
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
                arr[j] = arr[j - interval];
            }
            arr[j] = temp;
        }
    }
}
void shakerSort (int a[], int n) {
    int left = 0; 
    int right = n - 1;
    while (left < right) {
        bool swapped = false;
        for (int i = left; i < right; i++) {
            if (a[i] > a[i + 1]) {
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                swapped = true;
            }
        }
        right--;
        if (!swapped) {
            return;
        }
        swapped = false;
        for (int i = right; i > left; i--) {
            if (a[i] < a[i - 1]) {
                int temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            return;
        }
        left++;
    }
}
void flashSort (int a[], int n) {
    int minVal = getMin (a, n);
    int maxVal = getMax (a, n);
    if (minVal == maxVal) {
        return;
    }
    int m = 0.43 * n;
    int L[100];
    for (int i = 0; i < m; i++) {
        L[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int pos = (m - 1) * (a[i] - minVal) / (maxVal - minVal);
        L[pos]++;
    }
    for (int i = 1; i < m; i++) {
        L[i] += L[i - 1];
    }
    int move = 0;
    int i = 0;
    while (move < n - 1) {
        int k = (m - 1) * (a[i] - minVal) / (maxVal - minVal);
        while (i >= L[k]) { // neu phan tu da o sau vung class -> bo qua
            i++;
            k = (m - 1) * (a[i] - minVal) / (maxVal - minVal); 
        }
        int evicted = a[i]; // phan tu bi da ra
        while (i != L[k]) {
            k = (m - 1) * (evicted - minVal) / (maxVal - minVal);
            int pos = L[k] - 1;
            swap (a[pos], evicted);
            L[k]--;
            move++;
        }
    }
    insertionSort (a, n);
}