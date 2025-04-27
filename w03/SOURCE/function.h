#ifndef _FUNC_
#define _FUNC_
#include <iostream>
using namespace std;
int getMax (int a[], int n, int &count);
int getMin(int a[], int n, int &count);
void swap (int &a, int &b);
void bubbleSort(int a[], int n);
void countingSort(int a[], int n);
void heapify (int a[], int n, int i);
void heapSort (int a[], int n);
void insertionSort(int a[], int n);
void merge (int a[], int p, int q, int r);
void mergeDivdide (int a[], int p, int r);
void mergeSort (int a[], int n);
int divide (int a[], int left, int right);
void quickSort (int a[], int n);
void quick (int a[], int left, int right);
void countingSort (int a[], int n, int ex);
void radixSort (int a[], int n);
void selectionSort(int a[], int n);
void shellSort (int arr[], int n);
void shakerSort (int a[], int n);
void flashSort (int a[], int n);
#endif