#include <bits/stdc++.h>

//快速排序
int divide(int A[], int L, int R){
    int mid = A[L];
    while(L < R){
        while(A[R] >= mid && L < R)
            R--;
        A[L] = A[R];
        while(A[L] <= mid && L < R)
            L++;
        A[R] = A[L];
    }
    A[L] = mid;
    return L;
}

void Qsort(int A[], int L, int R){
    if(L >= R)
    return;
    int M = divide(A, L, R);
    Qsort(A, L, M-1);
    Qsort(A, M+1, R);
}
//堆排序(大根堆)
//顶点调整
void HeapAdjust(int A[], int k, int len){
    A[0] = A[k];
    for(int i = 2*k; i <= len; i *= 2){
        if(i < len && A[i+1] > A[i])
            i++;
        if(A[0] >= A[i])
            break;
        else{
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

//建堆
void BuildMaxHeap(int A[], int len){
    for(int i = len/2; i > 0; i--){
        HeapAdjust(A, i, len);
    }
}

//堆排序
void HeapSort(int A[], int len){
    BuildMaxHeap(A, len);
    for(int i = len; i > 1; i--){
        swap(A[i], A[1]);
        HeapAdjust(A, 1, i-1);
    }
}

//堆的删除
void DeleteHeap(int A[], int k, int len){
    A[1] = A[len];
    HeapAdjust(A, 1, len-1);
}

//堆的插入同下
//将一个堆插入另一个堆中，实现合并两个大根堆(自下向上调整，假设其中一个已为大根堆)，实质上就是堆的插入
void HeapInsert(int *heap, int n, int num){
    int i, j;
    heap[n+1] = num;    //将另一个堆中的数插入到，大根堆堆尾
    i = n + 1;
    j = (n + 1)/2;  //指向其父节点
    while(j > 0){   //父节点非空
        if(heap[j] >= num){
            break;      //如果父节点的值大于等于num,则跳出
        }
        heap[i] = heap[j];  //如果父节点的值小于num，将父节点的值赋给其孩子节点
        i = j;      
        j = i/2;    //继续向上
    }
    heap[i] = num;
    return;
}


//归并排序

//冒泡排序
void BubbleSort(int A[], int n){
    for(int i = 0; i < n-1; i++){
        bool flag = false;
        for(int j = n-1; j > i; j--){
            if(A[j-1] > A[j]){
                int temp = A[j-1];
                A[j-1] = A[j];
                A[j] = temp;
            }
            flag = true;
        }
        if(flag == false)
            return;
    }
}