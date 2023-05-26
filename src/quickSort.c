#include <stdio.h>

void quickSort(int arr[], int label1[], int label2[], int label3[], int left, int right)
{
    int i = left, j = right;
    int temp, pivot = arr[(left + right) / 2];
    int tmpLabel1;
    int tmpLabel2;
    int tmpLabel3;
 
    while (i <= j) {
        while (arr[i] > pivot)
            i++;
        while (arr[j] < pivot)
            j--;

        if (i <= j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            tmpLabel1 = label1[i];
            label1[i] = label1[j];
            label1[j] = tmpLabel1;

            tmpLabel2 = label2[i];
            label2[i] = label2[j];
            label2[j] = tmpLabel2;

            tmpLabel3 = label3[i];
            label3[i] = label3[j];
            label3[j] = tmpLabel3;

            i++;
            j--;
        }
    }
 
    if (left < j)
        quickSort(arr, label1, label2, label3, left, j);
    if (i < right)
        quickSort(arr, label1, label2, label3, i, right);
}
